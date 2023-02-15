#ifndef _POINT_H_
#define _POINT_H_
struct place {
	int x;
	int y;
};

struct point {
	int state;
	int has_neighnors;
	long double a_value;
	long double d_value;
	long double val;
	place place;
};

#define MAX 20
#define MIN 5
#define WIN 5
#define INFINITY 100000000

#endif _POINT_H_