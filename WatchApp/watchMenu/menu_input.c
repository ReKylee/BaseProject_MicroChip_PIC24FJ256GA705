/*
 * Menu input state machine and edit handling.
 */

#include "menu_state.h"
#include "menu_core.h"
#include "../shared/watch_settings_store.h"
#include "../watchCore/timekeeper.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../watchInput/potentiometer.h"
#include <string.h>

static bool edit_field_init(uint8_t field) {
    if (s_edit_last_field != field) {
        s_edit_last_raw = s_pot_filtered;
        s_edit_last_field = field;
        s_edit_last_draw_val = CACHE_INVALID_U8;
        s_edit_last_draw_field = CACHE_INVALID_U8;
        MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_FIELD, .state = Watch_GetState()->menu_state});
        return true;
    }
    return false;
}

static bool edit_handle_range(const EditInputConfig_t* cfg, uint8_t field, bool pot_changed, uint16_t pot_delta) {
    if (!pot_changed) return false;
    (void)pot_delta;
    uint8_t min = (field == 0) ? cfg->min0 : cfg->min1;
    uint8_t max = (field == 0) ? cfg->max0 : cfg->max1;
    uint8_t span = (uint8_t)(max - min);
    uint16_t hys;
    if (span >= 50) {
        hys = 10;   // minute-like fields
    } else if (span >= 20) {
        hys = 14;   // hour/day ranges
    } else {
        hys = 18;   // month/small ranges
    }
    if (field == 0) {
        return MenuCore_HandleRange(s_pot_filtered, cfg->min0, cfg->max0, hys, &s_edit_last_raw, &s_edit_last_val, cfg->val0);
    }
    return MenuCore_HandleRange(s_pot_filtered, cfg->min1, cfg->max1, hys, &s_edit_last_raw, &s_edit_last_val, cfg->val1);
}

static bool edit_handle_buttons(const EditInputConfig_t* cfg, uint8_t field, ButtonEvent_t btn, uint16_t pot_value) {
    WatchState_t* state = Watch_GetState();
    if (btn == BTN_S1_SHORT) {
        MenuState_OnChange(MENU_MAIN, true, pot_value);
        state->needs_full_redraw = true;
        return false;
    }
    if (btn == BTN_S2_SHORT) {
        if (field < 1) {
            state->menu_edit_field++;
            s_edit_last_draw_field = state->menu_edit_field;
            s_edit_last_draw_val = CACHE_INVALID_U8;
            s_edit_last_field = state->menu_edit_field;
            s_edit_last_raw = s_pot_filtered;
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_FIELD, .state = state->menu_state});
        } else {
            if (cfg->on_commit) cfg->on_commit();
            MenuState_OnChange(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        }
        return true;
    }
    return false;
}

static bool handle_simple_radial_state(MenuRadial_t* radial, ButtonEvent_t btn,
                                       uint16_t pot_value, bool pot_changed, uint16_t pot_delta) {
    WatchState_t* state = Watch_GetState();
    bool changed = false;

    if (pot_changed) {
        if (MenuCore_HandlePot(radial, s_pot_filtered, 20)) changed = true;
    }
    if (changed) {
        MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_RADIAL_SELECT, .state = state->menu_state});
    }
    if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
        (void)WatchSettingsStore_SaveState(state);
        MenuState_OnChange(MENU_MAIN, true, pot_value);
        state->needs_full_redraw = true;
    }
    return changed;
}

static void commit_set_time(void) {
    WatchState_t* state = Watch_GetState();
    Time_t requested = s_temp_time;
    requested.second = 0;
    if (!Timekeeper_SetTime(&requested)) {
        return;
    }
    Timekeeper_GetTime(&state->current_time);
    s_temp_time = state->current_time;
    (void)WatchSettingsStore_SaveState(state);
}

static bool clamp_temp_date(void) {
    bool changed = false;
    if (s_temp_date.month < 1) {
        s_temp_date.month = 1;
        changed = true;
    } else if (s_temp_date.month > 12) {
        s_temp_date.month = 12;
        changed = true;
    }

    uint8_t max_days = Timekeeper_GetDaysInMonth(s_temp_date.month);
    if (s_temp_date.day < 1) {
        s_temp_date.day = 1;
        changed = true;
    } else if (s_temp_date.day > max_days) {
        s_temp_date.day = max_days;
        changed = true;
    }
    return changed;
}

static void commit_set_date(void) {
    WatchState_t* state = Watch_GetState();
    if (s_temp_date.month < 1 || s_temp_date.month > 12) {
        return;
    }
    uint8_t max_days = Timekeeper_GetDaysInMonth(s_temp_date.month);
    if (s_temp_date.day < 1 || s_temp_date.day > max_days) {
        return;
    }
    Timekeeper_SetDate(&s_temp_date);
    state->current_date = s_temp_date;
    (void)WatchSettingsStore_SaveState(state);
}

static void commit_set_alarm(void) {
    WatchState_t* state = Watch_GetState();
    state->alarm.hour = s_temp_alarm.hour;
    state->alarm.minute = s_temp_alarm.minute;
    state->alarm.enabled = true;
    (void)WatchSettingsStore_SaveState(state);
}

static void commit_pomodoro(void) {
    WatchState_t* state = Watch_GetState();
    state->pomodoro.work_minutes = s_temp_pomo_work;
    state->pomodoro.short_break_minutes = s_temp_pomo_break;
    Pomodoro_Init();
}

void Menu_Init(void) {
    memset(&s_last_small_time, 0, sizeof(Time_t));
    s_last_small_time.second = 99;
    s_last_radial_selection = CACHE_INVALID_U8;
    MenuState_OnChange(MENU_MAIN, false, 0);
    MenuState_SetSkipNextPartial(false);
}

void Menu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_MENU;
    s_radial_selection = 0;
    state->menu_edit_field = 0;
    MenuState_OnChange(MENU_MAIN, false, 0);
    state->needs_full_redraw = true;
}

void Menu_Exit(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_WATCH;
    state->needs_full_redraw = true;
}

void Menu_HandleInput(ButtonEvent_t btn, uint16_t pot_value) {
    WatchState_t* state = Watch_GetState();
    bool changed = false;
    bool pot_changed = true;
    uint16_t pot_delta = 0;

    if (s_pot_last_raw == CACHE_INVALID_U16) {
        s_pot_last_raw = pot_value;
    }
    pot_delta = (pot_value > s_pot_last_raw) ? (pot_value - s_pot_last_raw) : (s_pot_last_raw - pot_value);
    s_pot_last_raw = pot_value;
    if (pot_delta < POT_DEADBAND) {
        pot_changed = false;
    }

    if (s_pot_filtered == CACHE_INVALID_U16) {
        s_pot_filtered = pot_value;
    } else {
        if (pot_delta >= POT_FAST_THRESHOLD) {
            s_pot_filtered = pot_value;
        } else {
            // With POT_SMOOTH_NUM=1 and POT_SMOOTH_DEN=2 this is a simple average.
            s_pot_filtered = (uint16_t)(((uint32_t)s_pot_filtered + (uint32_t)pot_value) >> 1);
        }
    }

    if (state->menu_state == MENU_MAIN) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_main_menu_radial, s_pot_filtered, 24)) changed = true;
        }
        if (changed) {
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_RADIAL_SELECT, .state = state->menu_state});
        }

        if (btn == BTN_S2_SHORT) {
            MenuState_t next_state = main_menu[s_radial_selection].next_state;
            bool next_is_edit = (next_state == MENU_SET_TIME || next_state == MENU_SET_DATE ||
                                 next_state == MENU_SET_ALARM || next_state == MENU_POMODORO);
            if (next_is_edit) {
                state->menu_edit_field = 0;
            }
            MenuState_OnChange(next_state, true, pot_value);
            MenuState_SeedEditBuffers(state->menu_state);
            if (next_is_edit) {
                // Seed edit hysteresis to current pot so first movement is not dropped.
                s_edit_last_raw = s_pot_filtered;
                s_edit_last_field = state->menu_edit_field;
            }
            state->needs_full_redraw = true;
            changed = true;
        }
    } else if (state->menu_state == MENU_DISPLAY_MODE) {
        if (handle_simple_radial_state(&s_display_menu_radial, btn, pot_value, pot_changed, pot_delta)) changed = true;
    } else if (state->menu_state == MENU_TIME_FORMAT) {
        if (handle_simple_radial_state(&s_format_menu_radial, btn, pot_value, pot_changed, pot_delta)) changed = true;
    } else if (state->menu_state == MENU_ALARM_TOGGLE) {
        if (handle_simple_radial_state(&s_alarm_toggle_radial, btn, pot_value, pot_changed, pot_delta)) changed = true;
    } else {
        EditInputConfig_t cfg;
        bool is_edit = true;
        switch (state->menu_state) {
            case MENU_SET_TIME:  cfg = (EditInputConfig_t){0, 23, 0, 59, &s_temp_time.hour, &s_temp_time.minute, commit_set_time}; break;
            case MENU_SET_DATE:  cfg = (EditInputConfig_t){1, 31, 1, 12, &s_temp_date.day, &s_temp_date.month, commit_set_date}; break;
            case MENU_SET_ALARM: cfg = (EditInputConfig_t){0, 23, 0, 59, &s_temp_alarm.hour, &s_temp_alarm.minute, commit_set_alarm}; break;
            case MENU_POMODORO:  cfg = (EditInputConfig_t){1, 60, 1, 30, &s_temp_pomo_work, &s_temp_pomo_break, commit_pomodoro}; break;
            default: is_edit = false; break;
        }
        if (is_edit) {
            changed |= edit_field_init(state->menu_edit_field);
            s_edit_last_val = (state->menu_edit_field == 0) ? *cfg.val0 : *cfg.val1;
            bool value_changed = edit_handle_range(&cfg, state->menu_edit_field, pot_changed, pot_delta);
            if (state->menu_state == MENU_SET_DATE && clamp_temp_date()) {
                value_changed = true;
            }
            if (value_changed) {
                changed = true;
                MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_VALUE, .state = state->menu_state});
            }
            if (edit_handle_buttons(&cfg, state->menu_edit_field, btn, pot_value)) changed = true;
        }
    }

    if (changed && !state->needs_full_redraw) state->needs_redraw = true;
}
