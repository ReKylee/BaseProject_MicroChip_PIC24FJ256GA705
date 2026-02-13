/*
 * Shared radial menu behavior: draw, selection, and pot mapping.
 */

#include "menu_core.h"

static uint8_t pot_select(uint16_t raw, uint8_t min, uint8_t max, uint16_t hysteresis,
                          uint16_t *last_raw, uint8_t *last_sel) {
    if (max <= min) {
        *last_sel = min;
        *last_raw = raw;
        return min;
    }

    uint16_t count = (uint16_t)max - (uint16_t)min + 1U;
    uint16_t bin = (uint16_t)(1024U / count);
    if (bin == 0U) bin = 1U;
    uint16_t target_u16 = (uint16_t)(raw / bin);
    if (target_u16 >= count) target_u16 = (uint16_t)(count - 1U);
    uint8_t target = (uint8_t)(target_u16 + min);

    if (*last_raw == 0xFFFF) {
        *last_raw = raw;
        *last_sel = target;
        return target;
    }

    if (target == *last_sel) {
        *last_raw = raw;
        return *last_sel;
    }

    uint8_t sel_idx = (uint8_t)(*last_sel - min);
    uint16_t lower = (uint16_t)(sel_idx * bin);
    uint16_t upper = (uint16_t)((sel_idx + 1U) * bin - 1U);

    if ((raw + hysteresis) < lower && *last_sel > min) {
        *last_sel = (uint8_t)(*last_sel - 1U);
    } else if (raw > (uint16_t)(upper + hysteresis) && *last_sel < max) {
        *last_sel = (uint8_t)(*last_sel + 1U);
    }

    *last_raw = raw;
    return *last_sel;
}

bool MenuCore_HandleRange(uint16_t raw, uint8_t min, uint8_t max, uint16_t hysteresis,
                          uint16_t *last_raw, uint8_t *last_val, uint8_t *value) {
    if (!last_raw || !last_val || !value) return false;
    if (max <= min || hysteresis == 0U) {
        *value = min;
        *last_val = min;
        *last_raw = raw;
        return false;
    }

    if (*last_raw == 0xFFFF) {
        *last_raw = raw;
        *last_val = *value;
        return false;
    }

    int16_t delta = (int16_t)raw - (int16_t)(*last_raw);
    if (delta >= (int16_t)hysteresis) {
        uint8_t steps = (uint8_t)(delta / (int16_t)hysteresis);
        uint16_t next = (uint16_t)(*value + steps);
        if (next > max) next = max;
        *last_raw = (uint16_t)((int16_t)(*last_raw) + ((int16_t)steps * (int16_t)hysteresis));
        if ((uint8_t)next != *value) {
            *value = (uint8_t)next;
            *last_val = *value;
            return true;
        }
    } else if (delta <= -(int16_t)hysteresis) {
        uint8_t steps = (uint8_t)((-delta) / (int16_t)hysteresis);
        int16_t next = (int16_t)(*value) - (int16_t)steps;
        if (next < (int16_t)min) next = min;
        *last_raw = (uint16_t)((int16_t)(*last_raw) - ((int16_t)steps * (int16_t)hysteresis));
        if ((uint8_t)next != *value) {
            *value = (uint8_t)next;
            *last_val = *value;
            return true;
        }
    }

    return false;
}

void MenuCore_ResetState(const MenuRadial_t* menu) {
    if (!menu) return;
    if (menu->last_selection) *menu->last_selection = 0xFF;
    if (menu->last_sel) *menu->last_sel = 0;
    if (menu->last_raw) *menu->last_raw = 0xFFFF;
}

void MenuCore_DrawRadialFull(const MenuRadial_t* menu) {
    if (!menu || !menu->draw_item || !menu->get_selection) return;
    uint8_t sel = menu->get_selection();
    for (uint8_t i = 0; i < menu->count; i++) {
        menu->draw_item(i, i == sel);
    }
    if (menu->draw_center) {
        menu->draw_center(sel);
    }
    if (menu->last_selection) {
        *menu->last_selection = sel;
    }
}

void MenuCore_DrawRadialPartial(const MenuRadial_t* menu) {
    if (!menu || !menu->draw_item || !menu->get_selection || !menu->last_selection) return;
    uint8_t sel = menu->get_selection();
    if (sel == *menu->last_selection) return;

    if (*menu->last_selection != 0xFF) {
        menu->draw_item(*menu->last_selection, false);
    }
    menu->draw_item(sel, true);
    if (menu->draw_center) {
        menu->draw_center(sel);
    }
    *menu->last_selection = sel;
}

bool MenuCore_HandlePot(const MenuRadial_t* menu, uint16_t raw, uint16_t hysteresis) {
    if (!menu || !menu->get_selection || !menu->set_selection || !menu->last_raw || !menu->last_sel) return false;
    if (menu->count == 0) return false;
    uint8_t sel = menu->get_selection();
    uint8_t next = pot_select(raw, 0, (uint8_t)(menu->count - 1), hysteresis, menu->last_raw, menu->last_sel);
    if (next != sel) {
        menu->set_selection(next);
        return true;
    }
    return false;
}
