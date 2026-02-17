/*
 * Shared numeric/date formatting helpers.
 */

#ifndef WATCH_FORMAT_H
#define WATCH_FORMAT_H

#include <stdint.h>
#include "fast_math.h"
#include "watch_types.h"

/**
 * @brief Split a base-10 value into tens and ones digits.
 * @param value Numeric value to split.
 * @param tens Output tens digit.
 * @param ones Output ones digit.
 * @note Intended for 0..99 display values.
 */
static inline void Watch_SplitDigits10(uint8_t value, uint8_t* tens, uint8_t* ones) {
    uint8_t t = FastMath_Div10U8(value);
    uint8_t rem = (uint8_t)(value - FastMath_Mul10U8(t));
    *tens = t;
    *ones = rem;
}

/**
 * @brief Format a number as zero-padded two digits.
 * @param value Value to format (expected 0..99).
 * @param out Output buffer of size 3; result is "NN\\0".
 */
static inline void Watch_Format2D(uint8_t value, char out[3]) {
    uint8_t tens;
    uint8_t ones;
    Watch_SplitDigits10(value, &tens, &ones);
    out[0] = (char)('0' + tens);
    out[1] = (char)('0' + ones);
    out[2] = '\0';
}

/**
 * @brief Format a date into "DD/MM".
 * @param date Input date structure.
 * @param out Output buffer of size 6; result is "DD/MM\\0".
 */
static inline void Watch_FormatDateDDMM(const Date_t* date, char out[6]) {
    uint8_t day_tens;
    uint8_t day_ones;
    uint8_t month_tens;
    uint8_t month_ones;
    Watch_SplitDigits10(date->day, &day_tens, &day_ones);
    Watch_SplitDigits10(date->month, &month_tens, &month_ones);
    out[0] = (char)('0' + day_tens);
    out[1] = (char)('0' + day_ones);
    out[2] = '/';
    out[3] = (char)('0' + month_tens);
    out[4] = (char)('0' + month_ones);
    out[5] = '\0';
}

#endif // WATCH_FORMAT_H
