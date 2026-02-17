/*
 * Persistent watch settings storage API (flash-backed).
 */

#ifndef WATCH_SETTINGS_STORE_H
#define WATCH_SETTINGS_STORE_H

#include <stdbool.h>
#include <stdint.h>
#include "watch_state.h"

/**
 * @brief Minimal persisted settings payload stored in flash.
 * @note Keep this compact and versioned by the storage layer.
 */
typedef struct {
    /** Current clock hour (0..23). */
    uint8_t hour;
    /** Current clock minute (0..59). */
    uint8_t minute;
    /** Current clock second (0..59). */
    uint8_t second;
    /** Calendar day (1..31). */
    uint8_t day;
    /** Calendar month (1..12). */
    uint8_t month;
    /** Time format enum value (TimeFormat_t). */
    uint8_t time_format;
    /** Active watch face enum value (WatchFace_t). */
    uint8_t watch_face;
    /** Alarm hour (0..23). */
    uint8_t alarm_hour;
    /** Alarm minute (0..59). */
    uint8_t alarm_minute;
    /** Alarm enabled flag (0/1). */
    uint8_t alarm_enabled;
    /** Reserved for forward-compatible expansion. */
    uint8_t reserved[6];
} WatchSettingsSnapshot_t;

/**
 * @brief Load settings snapshot from persistent storage.
 * @param out Output snapshot.
 * @return true if data is present and valid; false otherwise.
 */
bool WatchSettingsStore_Load(WatchSettingsSnapshot_t* out);

/**
 * @brief Save settings snapshot to persistent storage.
 * @param in Snapshot to persist.
 * @return true on successful write/verify path; false on validation or flash error.
 */
bool WatchSettingsStore_Save(const WatchSettingsSnapshot_t* in);

/**
 * @brief Copy the persisted subset of fields from runtime state.
 * @param state Source runtime state.
 * @param out Output snapshot.
 */
void WatchSettingsStore_FromState(const WatchState_t* state, WatchSettingsSnapshot_t* out);

/**
 * @brief Apply a persisted snapshot into runtime state.
 * @param in Source snapshot.
 * @param state Destination runtime state.
 */
void WatchSettingsStore_ApplyToState(const WatchSettingsSnapshot_t* in, WatchState_t* state);

/**
 * @brief Load persistent snapshot and apply it to runtime state.
 * @param state State to update.
 * @return true on successful load and apply; false otherwise.
 */
bool WatchSettingsStore_LoadState(WatchState_t* state);

/**
 * @brief Build a snapshot from runtime state and persist it.
 * @param state Source state.
 * @return true on successful save; false otherwise.
 */
bool WatchSettingsStore_SaveState(const WatchState_t* state);

#endif // WATCH_SETTINGS_STORE_H
