#include <stdbool.h>
#include <assert.h>
#include "generics.h"
#include "vector_math.h"
#include "multipoint.h"
#include "circle.h"

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