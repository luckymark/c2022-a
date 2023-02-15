#ifndef _AI_H_
#define _AI_H_
long double MiniMax(struct point p[25][25], int color, int depth, long double min, long double max);
place robot2(struct point p[25][25], int color, int f);
place robot(struct point p[25][25]);
place robotTry(struct point state[25][25], int f);
extern int canMakeMinSearch;
extern int bTurn;
#endif // !_AI_H_
