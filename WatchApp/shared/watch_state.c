/*
 * Implementation of central state management
 */

#include "watch_state.h"
#include "fast_math.h"
#include "watch_settings_store.h"
#include "../../flash_generated/flash.h"
#include <string.h>

// ============================================================================
// PRIVATE DATA
// ============================================================================

static WatchState_t g_watch_state;

#define SETTINGS_STORE_MAGIC 0x53575443UL /* "SWTC" */
#define SETTINGS_STORE_VERSION 1U
#define SETTINGS_STORE_FLASH_ADDRESS 0x2A000UL

typedef struct __attribute__((packed)) {
    uint32_t magic;
    uint16_t version;
    uint16_t payload_size;
    WatchSettingsSnapshot_t payload;
    uint16_t crc16;
} SettingsRecord_t;

/* CRC-16/CCITT-FALSE over serialized settings record bytes. */
static uint16_t settings_crc16(const uint8_t* data, uint16_t len) {
    uint16_t crc = 0xFFFFU;
    uint16_t i;
    for (i = 0; i < len; i++) {
        crc ^= ((uint16_t)data[i] << 8);
        for (uint8_t b = 0; b < 8; b++) {
            if ((crc & 0x8000U) != 0U) {
                crc = (uint16_t)((crc << 1) ^ 0x1021U);
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

/* Field-range validation for user-visible persisted settings. */
static bool settings_snapshot_is_valid(const WatchSettingsSnapshot_t* s) {
    if (!s) return false;
    if (s->hour > 23U || s->minute > 59U || s->second > 59U) return false;
    if (s->month < 1U || s->month > 12U) return false;
    if (s->day < 1U || s->day > 31U) return false;
    if (s->time_format >= (uint8_t)TIME_FORMAT_COUNT) return false;
    if (s->watch_face >= (uint8_t)FACE_COUNT_SELECTABLE) return false;
    if (s->alarm_hour > 23U || s->alarm_minute > 59U) return false;
    if (s->alarm_enabled > 1U) return false;
    return true;
}

/* Read raw record bytes from flash into a local typed structure. */
static void settings_read_record(SettingsRecord_t* out) {
    uint16_t words[(sizeof(SettingsRecord_t) + 1U) / 2U];
    uint16_t i;
    uint32_t addr = SETTINGS_STORE_FLASH_ADDRESS;
    for (i = 0; i < (uint16_t)(sizeof(words) / sizeof(words[0])); i++) {
        words[i] = FLASH_ReadWord16(addr);
        addr += 2U;
    }
    memset(out, 0, sizeof(*out));
    memcpy(out, words, sizeof(SettingsRecord_t));
}

/* Validate persisted record metadata, payload ranges, and CRC. */
static bool settings_record_is_valid(const SettingsRecord_t* rec) {
    if (!rec) return false;
    if (rec->magic != SETTINGS_STORE_MAGIC) return false;
    if (rec->version != SETTINGS_STORE_VERSION) return false;
    if (rec->payload_size != (uint16_t)sizeof(WatchSettingsSnapshot_t)) return false;
    if (!settings_snapshot_is_valid(&rec->payload)) return false;

    SettingsRecord_t temp = *rec;
    temp.crc16 = 0U;
    uint16_t crc = settings_crc16((const uint8_t*)&temp, (uint16_t)sizeof(SettingsRecord_t));
    return crc == rec->crc16;
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

WatchState_t* Watch_GetState(void) {
    return &g_watch_state;
}

void Watch_InitState(void) {
    memset(&g_watch_state, 0, sizeof(WatchState_t));
    
    g_watch_state.current_time.hour = 12;
    g_watch_state.current_time.minute = 0;
    g_watch_state.current_time.second = 0;
    
    g_watch_state.current_date.day = 1;
    g_watch_state.current_date.month = 1;
    
    g_watch_state.time_format = FORMAT_24H;
    
    g_watch_state.watch_face = FACE_DIGITAL;
    
    g_watch_state.display_mode = MODE_WATCH;
    g_watch_state.prev_display_mode = MODE_WATCH;
    
    g_watch_state.alarm.enabled = false;
    g_watch_state.alarm.triggered = false;
    
    g_watch_state.pomodoro.state = POMODORO_IDLE;
    g_watch_state.pomodoro.work_minutes = 25;
    g_watch_state.pomodoro.short_break_minutes = 5;
    g_watch_state.pomodoro.long_break_minutes = 15;
    g_watch_state.pomodoro.long_break_after_sessions = 4;
    g_watch_state.pomodoro.cycles_target = 4;
    g_watch_state.pomodoro.remaining_seconds = (uint16_t)FastMath_Mul60U32FromU8(g_watch_state.pomodoro.work_minutes);
    g_watch_state.pomodoro.work_sessions = 0;
    g_watch_state.pomodoro.paused = false;
    
    g_watch_state.needs_redraw = false;
    g_watch_state.needs_full_redraw = true;
}

bool WatchSettingsStore_Load(WatchSettingsSnapshot_t* out) {
    if (!out) return false;
    SettingsRecord_t rec;
    settings_read_record(&rec);
    if (!settings_record_is_valid(&rec)) return false;
    *out = rec.payload;
    return true;
}

bool WatchSettingsStore_Save(const WatchSettingsSnapshot_t* in) {
    if (!settings_snapshot_is_valid(in)) return false;

    SettingsRecord_t rec;
    uint16_t row_words[FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS * 2U];

    memset(&rec, 0, sizeof(rec));
    rec.magic = SETTINGS_STORE_MAGIC;
    rec.version = SETTINGS_STORE_VERSION;
    rec.payload_size = (uint16_t)sizeof(WatchSettingsSnapshot_t);
    rec.payload = *in;
    rec.crc16 = 0U;
    rec.crc16 = settings_crc16((const uint8_t*)&rec, (uint16_t)sizeof(rec));

    for (uint16_t i = 0; i < (uint16_t)(sizeof(row_words) / sizeof(row_words[0])); i++) {
        row_words[i] = 0xFFFFU;
    }
    memcpy(row_words, &rec, sizeof(rec));

    FLASH_Unlock(FLASH_UNLOCK_KEY);
    bool ok = FLASH_ErasePage(SETTINGS_STORE_FLASH_ADDRESS);
    if (ok) {
        ok = FLASH_WriteRow16(SETTINGS_STORE_FLASH_ADDRESS, row_words);
    }
    FLASH_Lock();
    return ok;
}

void WatchSettingsStore_FromState(const WatchState_t* state, WatchSettingsSnapshot_t* out) {
    if (!state || !out) return;
    memset(out, 0, sizeof(*out));
    out->hour = state->current_time.hour;
    out->minute = state->current_time.minute;
    out->second = state->current_time.second;
    out->day = state->current_date.day;
    out->month = state->current_date.month;
    out->time_format = (uint8_t)state->time_format;
    out->watch_face = (uint8_t)state->watch_face;
    out->alarm_hour = state->alarm.hour;
    out->alarm_minute = state->alarm.minute;
    out->alarm_enabled = state->alarm.enabled ? 1U : 0U;
    out->pomo_work_minutes = state->pomodoro.work_minutes;
    out->pomo_short_break_minutes = state->pomodoro.short_break_minutes;
    out->pomo_long_break_minutes = state->pomodoro.long_break_minutes;
    out->pomo_long_break_after_sessions = state->pomodoro.long_break_after_sessions;
    out->pomo_cycles_target = state->pomodoro.cycles_target;
}

void WatchSettingsStore_ApplyToState(const WatchSettingsSnapshot_t* in, WatchState_t* state) {
    if (!state || !in) return;
    state->current_time.hour = in->hour;
    state->current_time.minute = in->minute;
    state->current_time.second = in->second;
    state->current_date.day = in->day;
    state->current_date.month = in->month;
    state->time_format = (TimeFormat_t)in->time_format;
    state->watch_face = (WatchFace_t)in->watch_face;
    state->alarm.hour = in->alarm_hour;
    state->alarm.minute = in->alarm_minute;
    state->alarm.enabled = (in->alarm_enabled != 0U);

    if (in->pomo_work_minutes >= 1U && in->pomo_work_minutes <= 60U) {
        state->pomodoro.work_minutes = in->pomo_work_minutes;
    }
    if (in->pomo_short_break_minutes >= 1U && in->pomo_short_break_minutes <= 30U) {
        state->pomodoro.short_break_minutes = in->pomo_short_break_minutes;
    }
    if (in->pomo_long_break_minutes >= 1U && in->pomo_long_break_minutes <= 60U) {
        state->pomodoro.long_break_minutes = in->pomo_long_break_minutes;
    }
    if (in->pomo_long_break_after_sessions >= 1U && in->pomo_long_break_after_sessions <= 12U) {
        state->pomodoro.long_break_after_sessions = in->pomo_long_break_after_sessions;
    }
    if (in->pomo_cycles_target >= 1U && in->pomo_cycles_target <= 8U) {
        state->pomodoro.cycles_target = in->pomo_cycles_target;
    }
}

bool WatchSettingsStore_LoadState(WatchState_t* state) {
    WatchSettingsSnapshot_t snap;
    if (!state) return false;
    if (!WatchSettingsStore_Load(&snap)) return false;
    WatchSettingsStore_ApplyToState(&snap, state);
    return true;
}

bool WatchSettingsStore_SaveState(const WatchState_t* state) {
    WatchSettingsSnapshot_t snap;
    if (!state) return false;
    WatchSettingsStore_FromState(state, &snap);
    return WatchSettingsStore_Save(&snap);
}


