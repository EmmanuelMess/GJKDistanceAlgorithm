make:
	gcc -std=c11 -O3 -fPIC -o intersection.so main.c circle.h multipoint.h generics.h vector_math.h vector_math.c -shared