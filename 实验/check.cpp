
#include "point.h"
#include"check.h"
#include "UI.h"
#include "AI.h"
#include <stdlib.h>

int score[15] = { 100000000,5000000,80000,76000,75000,65000,100,80,65,60,20,2,1,0 };

long double abs(long double val) {
	if (val >= 0) return val;
	else return -val;
}

int linkFive(point p1, point p2, point p3, point p4, point p5, int color) {//*****
	if (p1.state == p2.state &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color) return 1;
	return 0;
}

int liveFour(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//_****_
	if (p1.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color) return 1;
	return 0;
}

int rushFour1(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//ememy a****
	if ((p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p1.state == 0 &&
		p6.state == -color) ||
		(p2.state == p3.state &&
			p3.state == p4.state &&
			p4.state == p5.state &&
			p5.state == color &&
			p6.state == 0 &&
			p1.state == -color)) return 1;
	return 0;
}
int rushFour2(point p1, point p2, point p3, point p4, point p5, int color) {//no enemy *_***
	if ((p1.state == p2.state &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p4.state == 0) ||
		(p1.state == p4.state &&
			p4.state == p3.state &&
			p3.state == p5.state &&
			p5.state == color &&
			p2.state == 0)) return 1;
	if ((p1.state == p2.state &&
		p2.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p3.state == 0)) return 1;
	return 0;
}

int linkThree1(point p1, point p2, point p3, point p4, point p5, int color) {//_***_
	if (p1.state == p5.state &&
		p5.state == 0 &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == color) return 1;
	return 0;
}

int linkThree2(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//_**_*_ ||_*_**_
	if ((p1.state == p4.state &&
		p4.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color) ||
		(p1.state == p3.state &&
			p3.state == p6.state &&
			p6.state == 0 &&
			p2.state == p4.state &&
			p4.state == p5.state &&
			p5.state == color)) return 1;
	return 0;
}

int sleepThree1(point p1, point p2, point p3, point p4, point p5, int color)//no enemy *__**||**__*||*_*_* 
{
	if (p1.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p2.state == p3.state &&
		p3.state == 0) return 1;
	if (p1.state == p2.state &&
		p2.state == p5.state &&
		p5.state == color &&
		p3.state == p4.state &&
		p4.state == 0) return 1;
	if (p1.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p2.state == p4.state &&
		p4.state == 0) return 1;
	return 0;
}
int sleepThree2(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//enemy
	if (p1.state == p2.state &&
		p2.state == 0 &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p6.state == -color)return 1;//__***a
	if (p5.state == p6.state &&
		p6.state == 0 &&
		p3.state == p4.state &&
		p4.state == p2.state &&
		p2.state == color &&
		p1.state == -color)return 1;//a***__
	return 0;
}

int sleepThree3(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//enemy
	if (p1.state == p3.state &&
		p3.state == 0 &&
		p2.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p6.state == -color)return 1;//_*_**a
	if (p4.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p1.state == -color)return 1;//a**_*_
	if (p1.state == p4.state &&
		p4.state == 0 &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p6.state == -color)return 1;//_**_*a
	if (p3.state == p6.state &&
		p6.state == 0 &&
		p2.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p1.state == -color)return 1;//a*_**_
	return 0;
}

int sleepThree4(point p1, point p2, point p3, point p4, point p5, point p6, point p7, int color) {//enemy a_***_a
	if (p1.state == p7.state &&
		p2.state == -color &&
		p2.state == p6.state &&
		p6.state == 0 &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color)return 1;
	return 0;
}

int liveTwo1(point p1, point p2, point p3, point p4, int color) {//*__*
	if (p1.state == p4.state &&
		p4.state == color &&
		p2.state == p3.state &&
		p3.state == 0) return 1;
	return 0;
}

int liveTwo2(point p1, point p2, point p3, point p4, point p5, int color) {//_*_*_
	if (p1.state == p3.state &&
		p3.state == p5.state &&
		p5.state == 0 &&
		p2.state == p4.state &&
		p4.state == color) return 1;
	return 0;
}

int liveTwo3(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//__**__
	if (p1.state == p2.state &&
		p2.state == p5.state &&
		p5.state == p6.state &&
		p6.state == 0 &&
		p3.state == p4.state &&
		p4.state == color) return 1;
	return 0;
}

int sleepTwo1(point p1, point p2, point p3, point p4, point p5, int color) {//*___*
	if (p1.state == p5.state &&
		p5.state == color &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == 0) return 1;
	return 0;
}

int sleepTwo2(point p1, point p2, point p3, point p4, point p5, point p6, int color) {
	if (p1.state == p2.state &&
		p2.state == p3.state &&
		p3.state == 0 &&
		p5.state == p4.state &&
		p4.state == color &&
		p6.state == -color) return 1;//___**a
	if (p4.state == p5.state &&
		p5.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p2.state == color &&
		p1.state == -color) return 1;//a**___
	if (p1.state == p2.state &&
		p2.state == p4.state &&
		p4.state == 0 &&
		p5.state == p3.state &&
		p5.state == color &&
		p6.state == -color) return 1;//__*_*a
	if (p5.state == p6.state &&
		p6.state == p3.state &&
		p3.state == 0 &&
		p2.state == p4.state &&
		p4.state == color &&
		p1.state == -color) return 1;//a*_*__
	if (p1.state == p3.state &&
		p3.state == p4.state &&
		p4.state == 0 &&
		p5.state == p2.state &&
		p2.state == color &&
		p6.state == -color) return 1;//_*__*a
	if (p3.state == p4.state &&
		p4.state == p6.state &&
		p6.state == 0 &&
		p2.state == p5.state &&
		p5.state == color &&
		p1.state == -color) return 1;//a*__*_
	return 0;
}

int Max(int a, int b) {
	if (a > b) return a;
	return b;
}
int Min(int a, int b) {
	if (a < b) return a;
	return b;
}

int check1(point p1, struct point p[25][25], int color) {//return 0 if all of neightnor are enemy
	int x = p1.place.x;
	int y = p1.place.y;
	if (p[x + 1][y].state == p[x + 1][y + 1].state &&
		p[x + 1][y + 1].state == p[x][y + 1].state &&
		p[x][y + 1].state == p[x - 1][y + 1].state &&
		p[x - 1][y + 1].state == p[x - 1][y].state &&
		p[x - 1][y].state == p[x - 1][y - 1].state &&
		p[x - 1][y - 1].state == p[x][y - 1].state &&
		p[x][y - 1].state == p[x + 1][y - 1].state &&
		p[x + 1][y - 1].state == -color) return 0;
	return 1;
}

int checkL5(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.x + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - WIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += linkFive(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			count += linkFive(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			count += linkFive(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			count += linkFive(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkL4(point p1, struct point p[25][25], int color) {//need to check
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN + 1, p1.place.x - WIN + 1); i < Min(MAX - 1, p1.place.x + WIN); i++) {
		for (int j = Max(MIN + 1, p1.place.y - WIN + 1); j < Min(MAX - 1, p1.place.y + WIN); j++) {
			count += liveFour(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			count += liveFour(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += liveFour(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			count += liveFour(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkR4A(point p1, struct point p[25][25], int color) {//need to check
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.x + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - WIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += rushFour1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][j + 5], color);
			count += rushFour1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[i + 5][j], color);
			count += rushFour1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			count += rushFour1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkR4B(point p1, struct point p[25][25], int color) {//need to check
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.x + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - WIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += rushFour2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			count += rushFour2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			count += rushFour2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			count += rushFour2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkL3A(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += linkThree1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			count += linkThree1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			count += linkThree1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			count += linkThree1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkL3B(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += linkThree2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			count += linkThree2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += linkThree2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			count += linkThree2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkS3A(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += sleepThree2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			count += sleepThree2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += sleepThree2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			count += sleepThree2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkS3B(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += sleepThree3(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			count += sleepThree3(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += sleepThree3(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			count += sleepThree3(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkS3C(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += sleepThree1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			count += sleepThree1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			count += sleepThree1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			count += sleepThree1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkS3D(point p1, struct point p[25][25], int color) {//need to check out of range
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += sleepThree4(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], p[i][Min(j + 6, 24)], color);
			count += sleepThree4(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], p[Min(i + 6, 24)][j], color);
			count += sleepThree4(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], p[Min(i + 6, 24)][Min(j + 6, 24)], color);
			count += sleepThree4(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], p[Min(i + 6, 24)][Max(j - 6, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkL2A(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += liveTwo3(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += liveTwo3(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += liveTwo3(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			count += liveTwo3(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkL2B(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += liveTwo1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], color);
			count += liveTwo1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], color);
			count += liveTwo1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], color);
			count += liveTwo1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], color);
			count += liveTwo2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			count += liveTwo2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			count += liveTwo2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			count += liveTwo2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkS2(point p1, struct point p[25][25], int color) {
	int count = 0;
	p[p1.place.x][p1.place.y].state = color;
	for (int i = Max(MIN, p1.place.x - WIN + 1); i < Min(MAX, p1.place.y + WIN); i++) {
		for (int j = Max(MIN, p1.place.y - MIN + 1); j < Min(MAX, p1.place.y + WIN); j++) {
			count += sleepTwo1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i + 4][j], color);
			count += sleepTwo1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			count += sleepTwo1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			count += sleepTwo1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
			count += sleepTwo2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += sleepTwo2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			count += sleepTwo2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			count += sleepTwo2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	p[p1.place.x][p1.place.y].state = 0;
	return count;
}

int checkVal(struct point p[25][25], int color) {
	int* st;
	st = (int*)malloc(13 * sizeof(int));
	st = checkState(p,color);
	int val = 0;
	for (int i = 0; i < 11; i++) {
		val += *st * score[i];
		st++;
	}
	return val;
}


int *checkState(struct point p[25][25], int color) {
	static int STAT[13];
	for (int i = 0; i < 13; i++) {
		STAT[i] = 0;
	}
	for (int i = MIN; i < MAX - 4; i++) {
		for (int j = MIN; j < MAX - 4; j++) {
			STAT[0] += linkFive(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			STAT[0] += linkFive(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			STAT[0] += linkFive(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			STAT[0] += linkFive(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
			STAT[1] += liveFour(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			STAT[1] += liveFour(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[1] += liveFour(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			STAT[1] += liveFour(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
			STAT[2] += rushFour1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			STAT[2] += rushFour1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[2] += rushFour1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			STAT[2] += rushFour1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
			STAT[3] += rushFour2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			STAT[3] += rushFour2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			STAT[3] += rushFour2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			STAT[3] += rushFour2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
			STAT[4] += linkThree1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			STAT[4] += linkThree1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			STAT[4] += linkThree1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			STAT[4] += linkThree1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
			STAT[5] += linkThree2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			STAT[5] += linkThree2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[5] += linkThree2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			STAT[5] += linkThree2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
			STAT[6] += sleepThree2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			STAT[6] += sleepThree2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[6] += sleepThree2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			STAT[6] += sleepThree2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
			STAT[7] += sleepThree3(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], color);
			STAT[7] += sleepThree3(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[7] += sleepThree3(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			STAT[7] += sleepThree3(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
			STAT[8] += sleepThree1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color) 
				+ sleepThree4(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], p[i][Min(j + 5, 24)], p[i][Min(j + 6, 24)], color);
			STAT[8] += sleepThree1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color) 
				+ sleepThree4(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], p[Min(i + 6, 24)][j], color);
			STAT[8] += sleepThree1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color)
				+ sleepThree4(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], p[Min(i + 6, 24)][Min(j + 6, 24)], color);
			STAT[8] += sleepThree1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color)
				+ sleepThree4(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], p[Min(i + 6, 24)][Max(j - 6, 0)], color);
			STAT[9] += liveTwo3(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[9] += liveTwo3(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[9] += liveTwo3(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			STAT[9] += liveTwo3(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
			STAT[10] += liveTwo1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], color);
			STAT[10] += liveTwo1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], color);
			STAT[10] += liveTwo1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], color);
			STAT[10] += liveTwo1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], color);
			STAT[10] += liveTwo2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i][j + 4], color);
			STAT[10] += liveTwo2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			STAT[10] += liveTwo2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			STAT[10] += liveTwo2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
			STAT[11] += sleepTwo1(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i + 4][j], color);
			STAT[11] += sleepTwo1(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], color);
			STAT[11] += sleepTwo1(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], color);
			STAT[11] += sleepTwo1(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], color);
			STAT[11] += sleepTwo2(p[i][j], p[i][j + 1], p[i][j + 2], p[i][j + 3], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[11] += sleepTwo2(p[i][j], p[i + 1][j], p[i + 2][j], p[i + 3][j], p[i + 4][j], p[Min(i + 5, 24)][j], color);
			STAT[11] += sleepTwo2(p[i][j], p[i + 1][j + 1], p[i + 2][j + 2], p[i + 3][j + 3], p[i + 4][j + 4], p[Min(i + 5, 24)][Min(j + 5, 24)], color);
			STAT[11] += sleepTwo2(p[i][j], p[i + 1][j - 1], p[i + 2][j - 2], p[i + 3][j - 3], p[i + 4][j - 4], p[Min(i + 5, 24)][Max(j - 5, 0)], color);
		}
	}
	return STAT;
}

long double checkStateVal(struct point p[25][25]) {
	long double s_value = 0;
	s_value += checkVal(p,-player);
	s_value -= checkVal(p, player)*1.5;
	return s_value;
}

long double checkPointVal (struct point p[25][25],point p1,int color) {
	int val = 0;
	val += checkL5(p1, p, color) * score[0];
	val += checkL4(p1, p, color) * score[1];
	val += checkR4A(p1, p, color) * score[2];
	val += checkR4B(p1, p, color) * score[3];
	val += checkL3A(p1, p, color) * score[4];
	val += checkL3B(p1, p, color) * score[5];
	val += checkS3A(p1, p, color) * score[6];
	val += checkS3B(p1, p, color) * score[7];
	val += checkS3C(p1, p, color) * score[8];
	val += checkS3D(p1, p, color) * score[8];
	val += checkL2A(p1, p, color) * score[9];
	val += checkL2B(p1, p, color) * score[10];
	val += checkS2(p1, p, color) * score[11];
	if (val == 0 && check1(p1, p, color) == 1) val = 1;
	return val;
}