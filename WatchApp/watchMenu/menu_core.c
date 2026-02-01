#include "menu_core.h"

static uint8_t pot_select(uint16_t raw, uint8_t min, uint8_t max, uint16_t hysteresis,
                          uint16_t *last_raw, uint8_t *last_sel) {
    if (max <= min) {
        *last_sel = min;
        *last_raw = raw;
        return min;
    }

    uint8_t count = (uint8_t)(max - min + 1);
    uint16_t bin = (uint16_t)(1024 / count);
    uint8_t target = (uint8_t)(raw / bin);
    if (target >= count) target = (uint8_t)(count - 1);
    target = (uint8_t)(target + min);

    if (*last_raw == 0xFFFF) {
        *last_raw = raw;
        *last_sel = target;
        return target;
    }

    if (target == *last_sel) {
        *last_raw = raw;
        return *last_sel;
    }

    // If the pot moves far, allow a direct jump.
    uint8_t sel_idx = (uint8_t)(*last_sel - min);
    uint8_t tgt_idx = (uint8_t)(target - min);
    if ((tgt_idx > sel_idx && (tgt_idx - sel_idx) > 1) ||
        (sel_idx > tgt_idx && (sel_idx - tgt_idx) > 1)) {
        *last_sel = target;
        *last_raw = raw;
        return target;
    }

    // Hysteresis around the current bin boundaries.
    uint16_t lower = (uint16_t)(sel_idx * bin);
    uint16_t upper = (uint16_t)((sel_idx + 1) * bin - 1);

    if ((raw + hysteresis) < lower && *last_sel > min) {
        *last_sel = (uint8_t)(*last_sel - 1);
    } else if (raw > (uint16_t)(upper + hysteresis) && *last_sel < max) {
        *last_sel = (uint8_t)(*last_sel + 1);
    }

    *last_raw = raw;
    return *last_sel;
}

bool MenuCore_HandleRange(uint16_t raw, uint8_t min, uint8_t max, uint16_t hysteresis,
                          uint16_t *last_raw, uint8_t *last_val, uint8_t *value) {
    if (!last_raw || !last_val || !value) return false;
    uint8_t mapped = pot_select(raw, min, max, hysteresis, last_raw, last_val);
    if (mapped != *value) {
        *value = mapped;
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
    uint8_t sel = menu->get_selection();
    uint8_t next = pot_select(raw, 0, (uint8_t)(menu->count - 1), hysteresis, menu->last_raw, menu->last_sel);
    if (next != sel) {
        menu->set_selection(next);
        return true;
    }
    return false;
}
