#include "menu_state.h"
#include "menu_core.h"
#include "../watchCore/timekeeper.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../watchInput/potentiometer.h"
#include <string.h>

static bool edit_field_init(uint8_t field) {
    if (s_edit_last_field != field) {
        s_edit_last_raw = s_pot_filtered;
        s_edit_last_field = field;
        s_edit_last_draw_val = 0xFF;
        s_edit_last_draw_field = 0xFF;
        MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_FIELD, .state = Watch_GetState()->menu_state});
        return true;
    }
    return false;
}

static bool edit_handle_range(const EditInputConfig_t* cfg, uint8_t field, bool pot_changed, uint16_t pot_delta) {
    if (!pot_changed) return false;
    uint16_t hys = (pot_delta > POT_FAST_THRESHOLD) ? 6 : 10;
    if (field == 0) {
        return MenuCore_HandleRange(s_pot_filtered, cfg->min0, cfg->max0, hys, &s_edit_last_raw, &s_edit_last_val, cfg->val0);
    }
    return MenuCore_HandleRange(s_pot_filtered, cfg->min1, cfg->max1, (uint16_t)(hys - 2), &s_edit_last_raw, &s_edit_last_val, cfg->val1);
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
            s_edit_last_draw_val = 0xFF;
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

static void commit_set_time(void) {
    WatchState_t* state = Watch_GetState();
    s_temp_time.second = 0;
    Timekeeper_SetTime(&s_temp_time);
    state->current_time = s_temp_time;
}

static void commit_set_date(void) {
    WatchState_t* state = Watch_GetState();
    Timekeeper_SetDate(&s_temp_date);
    state->current_date = s_temp_date;
}

static void commit_set_alarm(void) {
    WatchState_t* state = Watch_GetState();
    state->alarm.hour = s_temp_alarm.hour;
    state->alarm.minute = s_temp_alarm.minute;
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
    s_last_radial_selection = 0xFF;
    MenuState_OnChange(MENU_MAIN, false, 0);
    s_skip_next_partial = false;
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

    if (s_pot_last_raw == 0xFFFF) {
        s_pot_last_raw = pot_value;
    }
    pot_delta = (pot_value > s_pot_last_raw) ? (pot_value - s_pot_last_raw) : (s_pot_last_raw - pot_value);
    s_pot_last_raw = pot_value;
    if (pot_delta < POT_DEADBAND) {
        pot_changed = false;
    }

    if (s_pot_filtered == 0xFFFF) {
        s_pot_filtered = pot_value;
    } else {
        s_pot_filtered = (uint16_t)((s_pot_filtered * POT_SMOOTH_NUM + pot_value) / POT_SMOOTH_DEN);
    }

    if (state->menu_state == MENU_MAIN) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_main_menu_radial, s_pot_filtered, 24)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_main_menu_radial, s_pot_filtered, 24)) changed = true;
            }
        }
        if (changed) {
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_RADIAL_SELECT, .state = state->menu_state});
        }

        if (btn == BTN_S2_SHORT) {
            MenuState_t next_state = main_menu[s_radial_selection].next_state;
            if (next_state == MENU_SET_TIME || next_state == MENU_SET_DATE ||
                next_state == MENU_SET_ALARM || next_state == MENU_POMODORO) {
                state->menu_edit_field = 0;
            }
            MenuState_OnChange(next_state, true, pot_value);
            if (state->menu_state == MENU_SET_TIME) s_temp_time = state->current_time;
            if (state->menu_state == MENU_SET_DATE) s_temp_date = state->current_date;
            if (state->menu_state == MENU_SET_ALARM) {
                s_temp_alarm.hour = state->alarm.hour;
                s_temp_alarm.minute = state->alarm.minute;
                s_temp_alarm.second = 0;
            }
            if (state->menu_state == MENU_POMODORO) {
                s_temp_pomo_work = state->pomodoro.work_minutes;
                s_temp_pomo_break = state->pomodoro.short_break_minutes;
            }
            state->needs_full_redraw = true;
            changed = true;
        }
    } else if (state->menu_state == MENU_DISPLAY_MODE) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_display_menu_radial, s_pot_filtered, 20)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_display_menu_radial, s_pot_filtered, 20)) changed = true;
            }
        }
        if (changed) {
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_RADIAL_SELECT, .state = state->menu_state});
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            MenuState_OnChange(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_TIME_FORMAT) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_format_menu_radial, s_pot_filtered, 20)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_format_menu_radial, s_pot_filtered, 20)) changed = true;
            }
        }
        if (changed) {
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_RADIAL_SELECT, .state = state->menu_state});
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            MenuState_OnChange(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_ALARM_TOGGLE) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_alarm_toggle_radial, s_pot_filtered, 20)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_alarm_toggle_radial, s_pot_filtered, 20)) changed = true;
            }
        }
        if (changed) {
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_RADIAL_SELECT, .state = state->menu_state});
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            MenuState_OnChange(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_SET_TIME) {
        EditInputConfig_t cfg = {0, 23, 0, 59, &s_temp_time.hour, &s_temp_time.minute, commit_set_time};
        changed |= edit_field_init(state->menu_edit_field);
        s_edit_last_val = (state->menu_edit_field == 0) ? s_temp_time.hour : s_temp_time.minute;
        if (edit_handle_range(&cfg, state->menu_edit_field, pot_changed, pot_delta)) {
            changed = true;
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_VALUE, .state = state->menu_state});
        }
        if (edit_handle_buttons(&cfg, state->menu_edit_field, btn, pot_value)) changed = true;
    } else if (state->menu_state == MENU_SET_DATE) {
        EditInputConfig_t cfg = {1, 31, 1, 12, &s_temp_date.day, &s_temp_date.month, commit_set_date};
        changed |= edit_field_init(state->menu_edit_field);
        s_edit_last_val = (state->menu_edit_field == 0) ? s_temp_date.day : s_temp_date.month;
        if (edit_handle_range(&cfg, state->menu_edit_field, pot_changed, pot_delta)) {
            changed = true;
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_VALUE, .state = state->menu_state});
        }
        if (edit_handle_buttons(&cfg, state->menu_edit_field, btn, pot_value)) changed = true;
    } else if (state->menu_state == MENU_SET_ALARM) {
        EditInputConfig_t cfg = {0, 23, 0, 59, &s_temp_alarm.hour, &s_temp_alarm.minute, commit_set_alarm};
        changed |= edit_field_init(state->menu_edit_field);
        s_edit_last_val = (state->menu_edit_field == 0) ? s_temp_alarm.hour : s_temp_alarm.minute;
        if (edit_handle_range(&cfg, state->menu_edit_field, pot_changed, pot_delta)) {
            changed = true;
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_VALUE, .state = state->menu_state});
        }
        if (edit_handle_buttons(&cfg, state->menu_edit_field, btn, pot_value)) changed = true;
    } else if (state->menu_state == MENU_POMODORO) {
        EditInputConfig_t cfg = {1, 60, 1, 30, &s_temp_pomo_work, &s_temp_pomo_break, commit_pomodoro};
        changed |= edit_field_init(state->menu_edit_field);
        s_edit_last_val = (state->menu_edit_field == 0) ? s_temp_pomo_work : s_temp_pomo_break;
        if (edit_handle_range(&cfg, state->menu_edit_field, pot_changed, pot_delta)) {
            changed = true;
            MenuEvent_Push((MenuEvent_t){.type = MENU_EVT_EDIT_VALUE, .state = state->menu_state});
        }
        if (edit_handle_buttons(&cfg, state->menu_edit_field, btn, pot_value)) changed = true;
    }

    if (changed && !state->needs_full_redraw) state->needs_redraw = true;
}
