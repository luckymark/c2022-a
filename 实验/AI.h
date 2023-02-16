#ifndef _AI_H_
#define _AI_H_
long double MiniMax(struct point p[25][25], int color, int depth, long double alpha, long double beta);
place robot2(struct point p[25][25], int color, int f);
place robot(struct point p[25][25]);
place robot3(struct point state[25][25], int f);
void copyBoard(struct point p1[25][25], point p2[25][25]);
void reverseBoard(struct point p1[25][25], point p2[25][25]);
EvaPoint evaluate(point p[25][25]);

#define DEPTH 2
extern int bTurn;
#endif // !_AI_H_
