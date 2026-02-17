/*
 * Shared fixed-point and reciprocal math helpers.
 */

#ifndef FAST_MATH_H
#define FAST_MATH_H

#include <stdint.h>

/**
 * @brief Compute floor(value / 10) without hardware division.
 * @param value 8-bit unsigned value in [0, 255].
 * @return floor(value / 10), exact for full uint8_t range.
 */
static inline uint8_t FastMath_Div10U8(uint8_t value) {
    /* Exact for 0..255: floor(value / 10). */
    return (uint8_t)(((uint16_t)value * 205U) >> 11);
}

/**
 * @brief Multiply an 8-bit value by 10 using shifts/adds.
 * @param value 8-bit unsigned value.
 * @return value * 10 (wraps modulo 256 if overflowed).
 */
static inline uint8_t FastMath_Mul10U8(uint8_t value) {
    return (uint8_t)((value << 3) + (value << 1));
}

/**
 * @brief Compute floor(value / 6) without hardware division.
 * @param value 8-bit unsigned value in [0, 255].
 * @return floor(value / 6), exact for full uint8_t range.
 */
static inline uint8_t FastMath_Div6U8(uint8_t value) {
    /* Exact for 0..255: floor(value / 6). */
    return (uint8_t)(((uint16_t)value * 171U) >> 10);
}

/**
 * @brief Multiply an 8-bit value by 5 using shifts/adds.
 * @param value 8-bit unsigned value.
 * @return value * 5 (wraps modulo 256 if overflowed).
 */
static inline uint8_t FastMath_Mul5U8(uint8_t value) {
    return (uint8_t)((value << 2) + value);
}

/**
 * @brief Compute value modulo 5 without hardware division.
 * @param value 8-bit unsigned value.
 * @return value % 5.
 */
static inline uint8_t FastMath_Mod5U8(uint8_t value) {
    uint8_t out = value;
    while (out >= 5U) {
        out = (uint8_t)(out - 5U);
    }
    return out;
}

/**
 * @brief Subtract a delta on a circular 0..59 index.
 * @param value Current index in [0, 59].
 * @param delta Steps to subtract.
 * @return (value - delta) modulo 60.
 */
static inline uint8_t FastMath_SubMod60U8(uint8_t value, uint8_t delta) {
    uint8_t out = value;
    while (out < delta) {
        out = (uint8_t)(out + 60U);
    }
    return (uint8_t)(out - delta);
}

/**
 * @brief Absolute difference between two 16-bit unsigned values.
 * @return |a - b|.
 */
static inline uint16_t FastMath_AbsDiffU16(uint16_t a, uint16_t b) {
    return (a >= b) ? (uint16_t)(a - b) : (uint16_t)(b - a);
}

/**
 * @brief Multiply an 8-bit value by 60 into a 32-bit result.
 * @param value 8-bit unsigned value.
 * @return Exact value * 60.
 */
static inline uint32_t FastMath_Mul60U32FromU8(uint8_t value) {
    uint32_t n = (uint32_t)value;
    return (n << 6) - (n << 2);
}

/**
 * @brief Multiply an 8-bit value by 3600 into a 32-bit result.
 * @param value 8-bit unsigned value.
 * @return Exact value * 3600.
 */
static inline uint32_t FastMath_Mul3600U32FromU8(uint8_t value) {
    uint32_t n = (uint32_t)value;
    return (n << 11) + (n << 10) + (n << 9) + (n << 4);
}

/**
 * @brief Multiply a 32-bit value by 86400 using shift/add decomposition.
 * @param value 32-bit unsigned value.
 * @return value * 86400 (modulo 2^32 on overflow).
 */
static inline uint32_t FastMath_Mul86400U32(uint32_t value) {
    return (value << 16) + (value << 14) + (value << 12) + (value << 8) + (value << 7);
}

/**
 * @brief Compute floor(value / 86400) via reciprocal multiplication.
 * @param value 32-bit unsigned value.
 * @return floor(value / 86400), exact for uint32_t range.
 */
static inline uint32_t FastMath_Div86400U32(uint32_t value) {
    /* Exact for uint32_t input: floor(value / 86400). */
    return (uint32_t)(((uint64_t)value * 3257812231ULL) >> 48);
}

#endif // FAST_MATH_H
