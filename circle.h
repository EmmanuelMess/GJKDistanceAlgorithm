#ifndef GJKDISTANCEALGORITHM_CIRCLE_H
#define GJKDISTANCEALGORITHM_CIRCLE_H

#include <malloc.h>
#include "generics.h"
#include "vector_math.h"

struct CircleData {
	float radius;
};

struct Point farthestInCircleData(struct Shape shape, float x, float y) {
	struct CircleData * data = shape.shapeData;
	struct Point dir = n(p(x, y));

	return p((shape.average.x + dir.x) * data->radius, (shape.average.y + dir.y) * data->radius);
}

struct Shape c(float radius, struct Point center){
	struct Shape shape;
	struct CircleData * data = malloc(sizeof(struct CircleData));
	shape.shapeData = data;
	data->radius = radius;
	shape.farthestInDirection = farthestInCircleData;
	shape.average = center;
	return shape;
}
#endif //GJKDISTANCEALGORITHM_CIRCLE_H