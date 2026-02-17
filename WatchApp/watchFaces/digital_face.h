/*
 * Arc-themed digital watch face with large time text and second progress trail.
 */

#ifndef DIGITAL_FACE_H
#define DIGITAL_FACE_H

// ============================================================================
// DIGITAL FACE FUNCTIONS
// ============================================================================

/**
 * @brief Initialize digital face cached draw state.
 * @note Must be called before first draw.
 */
void DigitalFace_Init(void);

/**
 * @brief Draw the full digital face from scratch.
 * @note Rebuilds full layout: frame, time, seconds, date, AM/PM, and alarm icon.
 */
void DigitalFace_Draw(void);

/**
 * @brief Incrementally update digital face elements.
 * @note Intended for periodic updates; redraws only changed regions.
 */
void DigitalFace_DrawUpdate(void);

#endif // DIGITAL_FACE_H
