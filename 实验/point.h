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

struct MOVE {
	place place;
	long double val;
};

struct EvaPoint {
	place place[20];
	int score[20];
};

struct evaluation {
	long double score;
	int res;//1:b win; -1;w win; 0:continue
	int STAT[2][7];
};

#define MAX 20
#define MIN 5
#define WIN 5
#define INFINITY 10000000000
#define numOfEvaluate 5
#endif _POINT_H_

#define C_min 