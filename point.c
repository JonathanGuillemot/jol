#include <stdio.h>
#include <stdlib.h>

typedef struct point * P_point;
typedef struct point S_point;

struct point {
	float x;
	float y;
} point;

void point_debug (P_point p) {
	printf("(%2f , %2f)\n", p->x, p->y); 
}

S_point point_construct (float x, float y) {
		S_point p;
		p.x = x;
		p.y = y;
		return p;
}

P_point point_construct_dyn (float x, float y) {
	P_point p = malloc (sizeof (S_point));
	p->x = x;
	p->y = y;
	return p;
}

void point_increase (P_point p) {
	p->x += 1.0;
	p->y += 1.0;
}

int main (int argv, char ** argc) {
	S_point p = point_construct (12.2, -5.0);
	point_debug (&p);
	point_increase (&p);
	point_debug(&p);
	P_point q = point_construct_dyn (56.0, 14);
	point_debug (q);
	free(q);
	return EXIT_SUCCESS;
}
