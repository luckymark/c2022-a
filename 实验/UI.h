#include"point.h"
#ifndef _UI_H_
#define _UI_H_

extern place record_for_check[230];
extern int clen;
extern int player;
extern int num;
extern struct point p[25][25];

void board();
int end(struct point p[25][25]);
void execute(struct point p[25][25], int x, int y, int z,bool is_regect);
int first();
void initialize(struct point p[25][25]);
void over(int x);
int random();
void regret(struct point p[25][25]);
void set_neighnors(struct point p[25][25], point p1,int regect);
void start();
#endif _UI_H_