#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

struct Point {
	float x, y;
};

float scalar(struct Point p1, struct Point p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

struct Point tripleProd(struct Point p1, struct Point p2) {
	float p1mod2 = p1.x * p1.x + p1.y + p1.y;

	float x = scalar(p1, p2) * p2.x;
	float y = scalar(p1, p2) * p2.y;
	return (struct Point) {.x = p1mod2 * p1.x - x, .y = p1mod2 * p1.y - y};
}

struct Shape {
	void * shapeData;
	struct Point average;
	struct Point (*farthestInDirection)(struct Shape, float, float);
};

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

bool checkIntersection(struct Shape shape1, struct Shape shape2) {
	float dirX = shape1.average.x - shape2.average.x;
	float dirY = shape1.average.y - shape2.average.y;

	struct Point p1 = shape1.farthestInDirection(shape1, dirX, dirY);
	struct Point p2 = shape2.farthestInDirection(shape2, -dirX, -dirY);

	struct Point A = p(p1.x - p2.x, p1.y - p2.y);

	if(A.x == 0 && A.y == 0) {
		return true;
	}

	dirX = -A.x;
	dirY = -A.y;

	p1 = shape1.farthestInDirection(shape1, dirX, dirY);
	p2 = shape2.farthestInDirection(shape2, -dirX, -dirY);

	struct Point B = p(p1.x - p2.x, p1.y - p2.y);

	if(B.x == 0 && B.y == 0) {
		return true;
	}

	if(scalar(p(dirX, dirY), B) < 0) {
		return false;
	}

	while(true) {
		struct Point newDir = tripleProd(p(B.x - A.x, B.y - A.y), p(-A.x, -A.y));
		dirX = newDir.x;
		dirY = newDir.y;

		p1 = shape1.farthestInDirection(shape1, dirX, dirY);
		p2 = shape2.farthestInDirection(shape2, -dirX, -dirY);

		struct Point C = p(p1.x - p2.x, p1.y - p2.y);

		if (C.x == 0 && C.y == 0) {
			return true;
		}

		if (scalar(p(dirX, dirY), C) < 0) {
			return false;
		}

		struct Point AC = p(C.x - A.x, C.y - A.y);
		struct Point BC = p(C.x - B.x, C.y - B.y);

		struct Point CO = p(-C.x, -C.y);

		if (scalar(BC, p(-C.x, -C.y)) > 0) {
			B = C;
		} else if (scalar(AC, CO) > 0) {
			A = C;
		} else {
			return true;
		}
	}
}

int main() {
	struct Shape shape1 = s(3, 0.0,  0.0, 2.0, 0.0, 2.0, 1.0);
	struct Shape shape2 = s(3, 0.0, 0.0, 2.0, 0.0, 2.0, 1.0);

	assert(checkIntersection(shape1, shape2));

	shape1 = s(3, 0.0, -0.0, 2.0, -0.0, 2.0, -1.0);
	shape2 = s(3, 0.0, 0.0, 2.0, 0.0, 2.0, 1.0);

	assert(checkIntersection(shape1, shape2));

	shape1 = s(3, 0.0, -1.0, 2.0, -1.0, 2.0, -2.0);
	shape2 = s(3, 0.0, 0.0, 2.0, 0.0, 2.0, 1.0);

	assert(!checkIntersection(shape1, shape2));

	shape1 = s(3, 0.0, -1.0, 2.0, -1.0, 2.0, -2.0);
	shape2 = c(3, p(0.0f, 0.0f));

	assert(checkIntersection(shape1, shape2));

	shape1 = s(3, 0.0, -1.0, 2.0, -1.0, 2.0, -2.0);
	shape2 = c(1, p(0.0f, 0.0f));

	assert(checkIntersection(shape1, shape2));
}