#ifndef GJKDISTANCEALGORITHM_GENERICS_H
#define GJKDISTANCEALGORITHM_GENERICS_H

struct Point {
	float x, y;
};

struct Shape {
	void * shapeData;
	struct Point average;
	struct Point (*farthestInDirection)(struct Shape, float, float);
};

#endif //GJKDISTANCEALGORITHM_GENERICS_H
