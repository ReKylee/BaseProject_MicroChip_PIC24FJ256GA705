/*
 * binary_face.h
 * Binary watch face - displays time in binary format
 */

#ifndef BINARY_FACE_H
#define BINARY_FACE_H

// ============================================================================
// BINARY FACE FUNCTIONS
// ============================================================================

/**
 * @brief Initialize binary watch face
 */
void BinaryFace_Init(void);

/**
 * @brief Draw the binary watch face
 */
void BinaryFace_Draw(void);

/**
 * @brief Update binary watch face (called every second)
 */
void BinaryFace_Update(void);

#endif // BINARY_FACE_H
