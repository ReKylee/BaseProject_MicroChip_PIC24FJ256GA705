#ifndef SWITCH_H
#define SWITCH_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../systemExtensions/systemExtensions.h"

#define DEBOUNCE_TIME_MS 25

// Masks
#define S1_MASK (1 << 11)
#define S2_MASK (1 << 12)

// Compile-time down/up macros
#define SWITCH_ISDOWN(portReg, mask)  (!((portReg) & (mask))) // active low
#define SWITCH_ISUP(portReg, mask)    (!SWITCH_ISDOWN(portReg, mask))

#define S1_ISDOWN() (SWITCH_ISDOWN(PORTA, S1_MASK))
#define S2_ISDOWN() (SWITCH_ISDOWN(PORTA, S2_MASK))

// Initialize switches
#define S1_Init() (TRISA |= S1_MASK)
#define S2_Init() (TRISA |= S2_MASK)

// Edge detection functions (debounced)

bool S1_WasPressed(void) {
    static bool stableState = false;
    static uint32_t lastChange = 0;
    bool raw = S1_ISDOWN();

    if (raw != stableState) {
        if ((millis() - lastChange) >= DEBOUNCE_TIME_MS) {
            stableState = raw;
            if (stableState) return true;
        }
    } else {
        lastChange = millis();
    }
    return false;
}

bool S2_WasPressed(void) {
    static bool stableState = false;
    static uint32_t lastChange = 0;
    bool raw = S2_ISDOWN();

    if (raw != stableState) {
        if ((millis() - lastChange) >= DEBOUNCE_TIME_MS) {
            stableState = raw;
            if (stableState) return true;
        }
    } else {
        lastChange = millis();
    }
    return false;
}

bool S1_WasReleased(void) {
    static bool stableState = false;
    static uint32_t lastChange = 0;
    bool raw = S1_ISDOWN();

    if (raw != stableState) {
        if ((millis() - lastChange) >= DEBOUNCE_TIME_MS) {
            stableState = raw;
            if (!stableState) return true;
        }
    } else {
        lastChange = millis();
    }
    return false;
}

bool S2_WasReleased(void) {
    static bool stableState = false;
    static uint32_t lastChange = 0;
    bool raw = S2_ISDOWN();

    if (raw != stableState) {
        if ((millis() - lastChange) >= DEBOUNCE_TIME_MS) {
            stableState = raw;
            if (!stableState) return true;
        }
    } else {
        lastChange = millis();
    }
    return false;
}


#endif
