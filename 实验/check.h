#ifndef _CHECK_H_
#define _CHECK_H_
int check1(point p1, struct point p[25][25], int color);
int checkL5(point p1, struct point p[25][25], int color);
int checkL4(point p1, struct point p[25][25], int color);
int checkR4A(point p1, struct point p[25][25], int color);
int checkR4B(point p1, struct point p[25][25], int color);
int checkL3A(point p1, struct point p[25][25], int color);
int checkL3B(point p1, struct point p[25][25], int color);
int checkS3A(point p1, struct point p[25][25], int color);
int checkS3B(point p1, struct point p[25][25], int color);
int checkS3C(point p1, struct point p[25][25], int color);
int checkS3D(point p1, struct point p[25][25], int color);
int checkL2A(point p1, struct point p[25][25], int color);
int checkL2B(point p1, struct point p[25][25], int color);
int checkS2(point p1, struct point p[25][25], int color);
int* checkState(struct point p[25][25], int color);
int checkVal(struct point p[25][25], int color);
long double checkStateVal(struct point p[25][25]);
long double checkPointVal(struct point p[25][25], point p1, int color);
int Max(int a, int b);
int Min(int a, int b);
long double abs(long double val);
extern int score[15];

evaluation checkScore(point p[25][25]);
#endif _CHECK_H_