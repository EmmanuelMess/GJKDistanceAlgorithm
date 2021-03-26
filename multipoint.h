#ifndef GJKDISTANCEALGORITHM_MULTIPOINT_H
#define GJKDISTANCEALGORITHM_MULTIPOINT_H

#include <malloc.h>
#include <stdarg.h>
#include "generics.h"
#include "vector_math.h"

struct MultipointData {
	int len;
	struct Point * points;
};

struct Point farthestInMultipointData(struct Shape shape, float x, float y) {
	struct MultipointData * data = shape.shapeData;

	int maxIndex = -1;
	float maxScalarProd = -1;
	for (int i = 0; i < data->len; ++i) {
		float scalarProd = scalar(n(p(x, y)), n(data->points[i]));
		if(scalarProd > maxScalarProd) {
			maxIndex = i;
			maxScalarProd = scalarProd;
		}
	}
	return data->points[maxIndex];
}

struct Shape s(int count, ...){
	struct Shape shape;
	struct MultipointData * data = malloc(sizeof(struct MultipointData));
	shape.shapeData = data;
	data->len = count;
	data->points = calloc(count, sizeof(struct Point));
	shape.farthestInDirection = farthestInMultipointData;

	va_list ap;
	va_start(ap, count);
	for(int j = 0; j < count; j++) {
		data->points[j] = (struct Point) {.x = va_arg(ap, double), .y = va_arg(ap, double)};// DO NOT use p()
		shape.average.x += data->points[j].x;
		shape.average.y += data->points[j].y;
	}
	va_end(ap);

	shape.average.x /= (float) count;
	shape.average.y /= (float) count;

	return shape;
}

struct Shape sFromArray(int count, float array[]) {
	struct Shape shape;
	struct MultipointData * data = malloc(sizeof(struct MultipointData));
	shape.shapeData = data;
	data->len = count;
	data->points = calloc(count, sizeof(struct Point));
	shape.farthestInDirection = farthestInMultipointData;

	for(int i = 0, j = 0; j < count; i++, j++) {
		data->points[j] = p(array[i], array[i+1]);
		shape.average.x += data->points[j].x;
		shape.average.y += data->points[j].y;
	}

	shape.average.x /= (float) count;
	shape.average.y /= (float) count;

	return shape;
}

#endif //GJKDISTANCEALGORITHM_MULTIPOINT_H