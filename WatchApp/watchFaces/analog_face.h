/*
 * analog_face.h
 * Analog watch face with clock hands
 */

#ifndef ANALOG_FACE_H
#define ANALOG_FACE_H

// ============================================================================
// ANALOG FACE FUNCTIONS
// ============================================================================

/**
 * @brief Initialize analog watch face
 * Pre-calculates all 60 positions around clock face
 */
void AnalogFace_Init(void);

/**
 * @brief Draw the complete analog watch face
 */
void AnalogFace_Draw(void);

/**
 * @brief Update analog watch face (called every second)
 * Efficiently updates only what changed by erasing and redrawing hands.
 */
void AnalogFace_DrawUpdate(void);

#endif // ANALOG_FACE_H
