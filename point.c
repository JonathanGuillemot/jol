#include <stdlib.h>
#include <stdio.h>



typedef struct _point point;

struct _point {
	float x;
	float y;
};

void point_debug (point A) {
	printf("(%f ; %f)", A.x, A.y);
}

point point_construct (float x, float y) {
	point p;
	p.x = x;
	p.y = y;
	return p;
}


int main (int argc, char ** argv) {
	
	point p = point_construct(12.0 , 5.0);
	point_debug(p);
	printf("\n");
	p.x += 2.7;
	point_debug(p);
	printf("\n");

	return EXIT_SUCCESS;
}
