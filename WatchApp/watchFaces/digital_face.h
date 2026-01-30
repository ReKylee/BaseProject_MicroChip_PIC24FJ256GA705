/*
 * digital_face.h
 * Digital watch face with large digits
 */

#ifndef DIGITAL_FACE_H
#define DIGITAL_FACE_H

// ============================================================================
// DIGITAL FACE FUNCTIONS
// ============================================================================

/**
 * @brief Initialize digital watch face
 */
void DigitalFace_Init(void);

/**
 * @brief Draw the digital watch face
 */
void DigitalFace_Draw(void);

/**
 * @brief Update digital watch face (called every second)
 * Only redraws pixels that have changed.
 */
void DigitalFace_DrawUpdate(void);

#endif // DIGITAL_FACE_H
