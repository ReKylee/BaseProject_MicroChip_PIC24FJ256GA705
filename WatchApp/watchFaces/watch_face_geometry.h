#ifndef WATCH_FACE_GEOMETRY_H
#define WATCH_FACE_GEOMETRY_H

#include <stdint.h>

// Number of points (seconds/minutes/hours) on the clock face
#define NUM_CLOCK_POINTS 60

/**
 * @brief Precomputed points for clock hour hand endpoints (60 positions).
 * Each point is {x, y} relative to the center of the clock.
 */
extern const int8_t HOUR_POINTS[NUM_CLOCK_POINTS][2];

/**
 * @brief Precomputed points for clock minute hand endpoints (60 positions).
 * Each point is {x, y} relative to the center of the clock.
 */
extern const int8_t MIN_POINTS[NUM_CLOCK_POINTS][2];

/**
 * @brief Precomputed points for clock second hand endpoints (60 positions).
 * Each point is {x, y} relative to the center of the clock.
 */
extern const int8_t SEC_POINTS[NUM_CLOCK_POINTS][2];

#endif // WATCH_FACE_GEOMETRY_H
