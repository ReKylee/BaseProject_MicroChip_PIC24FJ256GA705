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

    if (raw > 1023U) raw = 1023U;
    uint16_t count = (uint16_t)max - (uint16_t)min + 1U;
    uint16_t target_u16 = (uint16_t)((((uint32_t)raw * (uint32_t)count) + 512UL) >> 10);
    if (target_u16 >= count) {
        target_u16 = (uint16_t)(count - 1U);
    }
    uint8_t target = (uint8_t)((uint16_t)min + target_u16);

    if (*last_raw == 0xFFFF) {
        *last_raw = raw;
        *last_sel = target;
        return target;
    }

    uint16_t raw_diff = (raw >= *last_raw) ? (uint16_t)(raw - *last_raw) : (uint16_t)(*last_raw - raw);
    if (target == *last_sel || raw_diff < hysteresis) {
        *last_raw = raw;
        return *last_sel;
    }

    *last_sel = target;
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

    if (raw > 1023U) raw = 1023U;
    uint16_t count = (uint16_t)max - (uint16_t)min + 1U;
    uint16_t idx = (uint16_t)((((uint32_t)raw * (uint32_t)count) + 512UL) >> 10);
    if (idx >= count) {
        idx = (uint16_t)(count - 1U);
    }
    uint8_t mapped = (uint8_t)((uint16_t)min + idx);

    if (*last_raw == 0xFFFF) {
        *last_raw = raw;
        *last_val = *value;
        return false;
    }

    int16_t diff = (int16_t)raw - (int16_t)(*last_raw);
    if (diff < 0) diff = -diff;

    if (mapped != *value && (uint16_t)diff >= hysteresis) {
        *value = mapped;
        *last_val = mapped;
        *last_raw = raw;
        return true;
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
