#include <math.h>
#include "vector_math.h"

float scalar(struct Point p1, struct Point p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

struct Point tripleProd(struct Point p1, struct Point p2) {
	float p1mod2 = p1.x * p1.x + p1.y + p1.y;

	float x = scalar(p1, p2) * p2.x;
	float y = scalar(p1, p2) * p2.y;
	return (struct Point) {.x = p1mod2 * p1.x - x, .y = p1mod2 * p1.y - y};
}


struct Point p(float x, float y) {
	return (struct Point) {.x = x, .y = y};
}

struct Point n(struct Point p) {
	float x = p.x;
	float y = p.y;
	float norm = sqrtf(x*x + y*y);
	x /= norm;
	y /= norm;

	return (struct Point) {.x = x, .y = y};
}
