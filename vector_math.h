#ifndef GJKDISTANCEALGORITHM_VECTOR_MATH_H
#define GJKDISTANCEALGORITHM_VECTOR_MATH_H

#include "generics.h"

/**
 * scalar product
 */
float scalar(struct Point p1, struct Point p2);

/**
 * Computes: (p1 * p2) * p1
 * where * is vector product
 */
struct Point tripleProd(struct Point p1, struct Point p2);

/**
 * Creates point
 */
struct Point p(float x, float y);

/**
 * Normalizes vector
 */
struct Point n(struct Point p);

#endif //GJKDISTANCEALGORITHM_VECTOR_MATH_H
