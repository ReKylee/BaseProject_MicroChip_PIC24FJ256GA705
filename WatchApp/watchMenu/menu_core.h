#ifndef MENU_CORE_H
#define MENU_CORE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t count;
    void (*draw_item)(uint8_t idx, bool selected);
    void (*draw_center)(uint8_t idx);
    uint8_t (*get_selection)(void);
    void (*set_selection)(uint8_t idx);
    uint8_t *last_selection;   // for partial redraw
    uint8_t *last_sel;         // for hysteresis
    uint16_t *last_raw;
} MenuRadial_t;

void MenuCore_DrawRadialFull(const MenuRadial_t* menu);
void MenuCore_DrawRadialPartial(const MenuRadial_t* menu);
bool MenuCore_HandlePot(const MenuRadial_t* menu, uint16_t raw, uint16_t hysteresis);
void MenuCore_ResetState(const MenuRadial_t* menu);
bool MenuCore_HandleRange(uint16_t raw, uint8_t min, uint8_t max, uint16_t hysteresis,
                          uint16_t *last_raw, uint8_t *last_val, uint8_t *value);

#endif // MENU_CORE_H
