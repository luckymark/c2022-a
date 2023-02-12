﻿#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<graphics.h>
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<easyx.h>
#include<stdlib.h>
#include<time.h>

#define MAX 20
#define MIN 5
#define WIN 5
#define INFINITY 1000000

typedef struct place {
	int x;
	int y;
}place;

struct point {
	int state;
	long double a_value;
	long double d_value;
	place place;
};

int main();
int num = 0;
int ni = 0, nj = 0, nx = 0, ny = 0;//for regret
place walk[230];
int len = 0;//for walk
place record_for_check[230];
int clen = 0;
point record_for_state[25][25];

int score[15] = { 1000000,300000,3000,2800,2500,500,100,50,30,15,5,3,1,0 };
#define MAX 20
#define MIN 5
#define WIN 5
#define INFINITY 1000000

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

int checkVal(struct point p[25][25], point p1, int color) {
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


void initialize(struct point p[25][25]) {
	int i, j;
	num = 0;
	for (int i = 0; i < 230; i++) walk[i] = { NULL,NULL };
	for (i = 0; i < 25; i++) {
		for (j = 0; j < 25; j++) {
			p[i][j].state = record_for_state[i][j].state = 2;
			p[i][j].a_value = record_for_state[i][j].a_value = 0;
			p[i][j].d_value = record_for_state[i][j].d_value = 0;
			p[i][j].place.x = record_for_state[i][j].place.x = i;
			p[i][j].place.y = record_for_state[i][j].place.y = j;
		}
	}
	for (i = MIN; i < MAX; i++) {
		for (j = MIN; j < MAX; j++) {
			p[i][j].state = record_for_state[i][j].state = 0;
		}
	}
}

void board() {//draw the board
	setbkcolor(LIGHTGRAY);
	cleardevice();//use bkcolor to fill graph
	setlinecolor(BLACK);
	setfillcolor(DARKGRAY);
	setbkcolor(DARKGRAY);
	settextstyle(40, 20, _T("Consolas"));
	for (int i = 50; i <= 750; i += 50) {
		line(i, 50, i, 750);
		line(50, i, 750, i);
	}
	fillrectangle(820, 190, 1030, 255);
	fillrectangle(820, 340, 1030, 405);
	fillrectangle(820, 490, 1030, 555);
	TCHAR s1[] = _T("重來");
	TCHAR s2[] = _T("悔棋");
	TCHAR s3[] = _T("結束遊戲");
	outtextxy(885, 200, s1);
	outtextxy(885, 350, s2);
	outtextxy(845, 500, s3);
}

void execute(struct point p[25][25], int x, int y, int z) {//draw the chess(circle) and make the record with the state
	if (z != 0) {
		if (z == 1)
			setfillcolor(BLACK);
		if (z == -1)
			setfillcolor(WHITE);
		fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);
		p[x][y].state = z;
		record_for_state[x][y].state = z;
	}
}

int end(struct point p[25][25]) {//it will return 0 if nobody win or draw
	int i, j, k = 0, x, y, q, b, e = 0;
	x = y = b = q = -2;
	for (i = MIN; i < MAX; i++) {
		for (j = MIN; j < MAX; j++) {
			if (p[i][j].state == 0) k++;

			else {
				for (x = -2; p[i][j].state == p[i][j + x].state && x < 4; x++) {}
				for (y = -2; p[i][j].state == p[i + y][j].state && y < 4; y++) {}
				for (b = -2; p[i][j].state == p[i + b][j + b].state && b < 4; b++) {}
				for (q = -2; p[i][j].state == p[i - q][j + q].state && q < 4; q++) {}
			}
			if (x == WIN - 2 || y == WIN - 2 || b == WIN - 2 || q == WIN - 2) {
				if (p[i][j].state == 1) e = 1;
				else if (p[i][j].state == -1) e = -1;
			}
		}
	}
	if (k == 0) e = 2;
	return e;
}

void over(int x) {
	setbkcolor(LIGHTGRAY);
	settextstyle(40, 0, _T("Consolas"));
	settextcolor(BLACK);
	if (x == 1) {
		TCHAR s[] = _T("Black Win!");
		outtextxy(835, 20, s);
	}
	else if (x == -1) {
		TCHAR s[] = _T("White Win!");
		outtextxy(835, 20, s);
	}
	else {
		TCHAR s[] = _T("Draw");
		outtextxy(850, 20, s);
	}
	clearrectangle(800, 175, 1100, 800);
	settextcolor(WHITE);
	setbkcolor(DARKGRAY);
	setfillcolor(DARKGRAY);
	fillrectangle(800, 335, 1065, 400);
	fillrectangle(800, 485, 1065, 550);
	TCHAR s1[] = _T("返回遊戲界面");
	TCHAR s2[] = _T("結束遊戲");
	outtextxy(820, 350, s1);
	outtextxy(855, 500, s2);

	while (true)
	{
		MOUSEMSG n;
		n = GetMouseMsg(); 
		if (n.x <= 1065 && n.x >= 800 && n.y <= 400 && n.y >= 335) {
			settextcolor(LIGHTCYAN);
			outtextxy(820, 350, s1);
			if (n.uMsg == WM_LBUTTONDOWN) {
				main();
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(820, 350, s1);
		}
		if (n.x <= 1065 && n.x >= 800 && n.y <= 550 && n.y >= 485) {
			settextcolor(LIGHTCYAN);
			outtextxy(855, 500, s2);
			if (n.uMsg == WM_LBUTTONDOWN) {
				closegraph();
				exit(0);
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(855, 500, s2);
		}
	}
}


int has_neightnor(place pt) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			for (int count = 0; count < len; count++) {
				if (pt.x + i == walk[count].x && pt.y + j == walk[count].y) {
					return 1;
				}
			}
		}
	}
	return 0;
}

place robot2(struct point p[25][25], int color, int f) {//AI 
	time_t t;
	place max_p, min_p;
	long double min = 0, max = 0;
	if (f == 0) return { 12,12 };
	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			p[i][j].a_value = p[i][j].d_value = 0;
			if (p[i][j].state == 0) {
				p[i][j].a_value = checkVal(p, p[i][j], color);
				if (p[i][j].a_value > max) {
					max = p[i][j].a_value;
					max_p.x = i;
					max_p.y = j;
				}
				p[i][j].d_value = checkVal(p, p[i][j], -color);
				if (p[i][j].d_value > min) {
					min = p[i][j].d_value;
					min_p.x = i;
					min_p.y = j;
				}
			}
		}
	}
	if (max >= min) return max_p;
	else return min_p;
}

place robot(struct point p[25][25]) {// random.
	place place;
	time_t t;
	srand((unsigned)time(&t));
	place.x = rand() % (MAX - MIN + 1) + MIN;
	srand((unsigned)time(&t));
	place.y = rand() % (MAX - MIN + 1) + MIN;
	return place;
}

void regret(struct point p[25][25]) {
	p[walk[len - 1].x][walk[len - 1].y].state = 0;
	len--;
	num--;
	board();
	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			if (p[i][j].state != 0) {
				execute(p, i, j, p[i][j].state);
			}
		}
	}
}

void begin(struct point p[25][25], int player) {
	MOUSEMSG m;
	int x, y, i, j, e, f = 0;
	board();
	setlinecolor(BLACK);
	if (player == 0) player = 1;
	else player = -1;
	while (TRUE) {
		setbkcolor(LIGHTGRAY);
		int color;
		if (num % 2 == 0) {
			color = 1;
			setfillcolor(BLACK);
		}
		else {
			color = -1;
			setfillcolor(WHITE);
		}
		fillcircle(925, 125, 40);
		if (color == player) {//test
			int state;
			setrop2(R2_COPYPEN);//R2_COPYPEN 當前顔色
			while (true) {
				m = GetMouseMsg();
				x = m.x % 50;
				y = m.y % 50;
				setbkcolor(DARKGRAY);
				TCHAR s1[] = _T("重來");
				TCHAR s2[] = _T("悔棋");
				TCHAR s3[] = _T("結束遊戲");
				if (m.x <= 1030 && m.x >= 820 && m.y <= 255 && m.y >= 190) {//重來
					settextcolor(LIGHTCYAN);
					outtextxy(885, 200, s1);
					if (m.uMsg == WM_LBUTTONDOWN) {
						initialize(p);
						begin(p, player);
					}
				}
				else {
					settextcolor(WHITE);
					outtextxy(885, 200, s1);
				}
				if (m.x <= 1030 && m.x >= 820 && m.y <= 405 && m.y >= 340) {//悔棋
					settextcolor(LIGHTCYAN);
					outtextxy(885, 350, s2);
					if (m.uMsg == WM_LBUTTONDOWN) {
						if (len > 1 && num > 1) {
							regret(p);
							regret(p);//2 times;
						}
						else {
							TCHAR s[] = _T("不可悔棋");
							outtextxy(850, 700, s);
						}
					}
				}
				else {
					settextcolor(WHITE);
					outtextxy(885, 350, s2);
				}
				if (m.x <= 1030 && m.x >= 820 && m.y <= 555 && m.y >= 490) {//結束遊戲
					settextcolor(LIGHTCYAN);
					outtextxy(845, 500, s3);
					if (m.uMsg == WM_LBUTTONDOWN) {
						closegraph();
						exit(0);
					}
				}
				else {
					settextcolor(WHITE);
					outtextxy(845, 500, s3);
				}

				if (x > 25)
					m.x = m.x - x + 50;
				else
					m.x = m.x - x;
				if (y > 25)
					m.y = m.y - y + 50;
				else
					m.y = m.y - y;
				i = m.x / 50 - 1 + MIN;
				j = m.y / 50 - 1 + MIN;

				if (m.uMsg == WM_LBUTTONDOWN) {
					if (i < MAX && j < MAX && i >= MIN && j >= MIN) {
						if (p[i][j].state == 0) {
							execute(p, i, j, color);
							walk[len].x = i;
							walk[len].y = j;
							len++;
							record_for_check[clen] = { i,j };
							clen++;
							Sleep(10);
							num++;
							setbkcolor(LIGHTGRAY);
							clearrectangle(800, 700, 1200, 800);
							break;
						}
					}
				}
			}
		}
		else {//robot

			struct place place;
			place = robot2(p, -player, f);
			while (!(place.x < MAX && place.y < MAX && place.x >= MIN && place.y >= MIN && p[place.x][place.y].state == 0)) {
				place = robot2(p, -player, f);
			}
			execute(p, place.x, place.y, color);
			walk[len].x = place.x;
			walk[len].y = place.y;
			len++;
			record_for_check[clen] = { place.x,place.y };
			clen++;
			Sleep(10);
			num++;
		}

		e = end(p);
		if (e != 0) {
			Sleep(500);
			over(e);
			break;
		}
		f = 1;
	}
}

int random() {
	int num;
	time_t t;
	srand((unsigned)time(&t));
	num = rand() % 2;
	setbkcolor(LIGHTGRAY);
	settextcolor(WHITE);
	cleardevice();
	if (num == 0) {
		TCHAR s[] = _T("you are black");
		outtextxy(400, 400, s);
	}
	else if (num == 1) {
		TCHAR s[] = _T("you are white");
		outtextxy(400, 400, s);
	}
	else {
		TCHAR s[] = _T("error");
		outtextxy(400, 400, s);
	}
	setbkcolor(DARKGRAY);
	setfillcolor(DARKGRAY);
	setlinecolor(DARKGRAY);
	TCHAR s1[] = _T("確定");
	TCHAR s2[] = _T("重抽");
	fillrectangle(175, 590, 300, 650);
	fillrectangle(775, 590, 900, 650);
	outtextxy(200, 600, s1);
	outtextxy(800, 600, s2);
	return num;
}

int first() {//set player color
	initgraph(1100, 800);
	setbkcolor(LIGHTGRAY);
	cleardevice();
	int num;
	MOUSEMSG n;
	setbkcolor(DARKGRAY);
	setfillcolor(DARKGRAY);
	settextcolor(WHITE);
	settextstyle(40, 0, _T("Consolas"));
	fillrectangle(175, 375, 475, 465);
	fillrectangle(575, 375, 875, 465);
	TCHAR s1[] = _T("選擇白子/黑子");
	TCHAR s2[] = _T("隨機");
	outtextxy(200, 400, s1);
	outtextxy(685, 400, s2);
	while (true) {
		n = GetMouseMsg();
		if (n.x <= 475 && n.x >= 175 && n.y >= 375 && n.y <= 465) {
			settextcolor(LIGHTCYAN);
			outtextxy(200, 400, s1);
			if (n.uMsg == WM_LBUTTONDOWN) {
				setbkcolor(LIGHTGRAY);
				cleardevice();
				setbkcolor(DARKGRAY);
				fillrectangle(175, 375, 475, 465);
				fillrectangle(575, 375, 875, 465);
				TCHAR s1[] = _T("白子");
				TCHAR s2[] = _T("黑子");
				outtextxy(285, 400, s1);
				outtextxy(685, 400, s2);
				while (true) {
					n = GetMouseMsg();
					if (n.x <= 475 && n.x >= 175 && n.y >= 375 && n.y <= 465) {
						settextcolor(LIGHTCYAN);
						outtextxy(285, 400, s1);
						if (n.uMsg == WM_LBUTTONDOWN) return 1;
					}
					else {
						settextcolor(WHITE);
						outtextxy(285, 400, s1);
					}
					if (n.x <= 875 && n.x >= 575 && n.y >= 375 && n.y <= 465) {
						settextcolor(LIGHTCYAN);
						outtextxy(685, 400, s2);
						if (n.uMsg == WM_LBUTTONDOWN) return 0;
					}
					else {
						settextcolor(WHITE);
						outtextxy(685, 400, s2);
					}
				}
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(200, 400, s1);
		}
		if (n.x <= 875 && n.x >= 575 && n.y >= 375 && n.y <= 465) {
			settextcolor(LIGHTCYAN);
			outtextxy(685, 400, s2);
			if (n.uMsg == WM_LBUTTONDOWN) {
				num = random();
				while (true) {
					n = GetMouseMsg();
					TCHAR s1[] = _T("確定");
					TCHAR s2[] = _T("重抽");
					if (n.x >= 175 && n.y >= 590 && n.x <= 300 && n.y <= 650) {//mouse put on left button
						settextcolor(LIGHTCYAN);
						outtextxy(200, 600, s1);
						if (n.uMsg == WM_LBUTTONDOWN) return num;
					}
					else {
						settextcolor(WHITE);
						outtextxy(200, 600, s1);
					}
					if (n.x >= 775 && n.y >= 590 && n.x <= 900 && n.y <= 650) {//mouse put on right button
						settextcolor(LIGHTCYAN);
						outtextxy(800, 600, s2);
						if (n.uMsg == WM_LBUTTONDOWN) {
							setbkcolor(LIGHTGRAY);
							settextcolor(WHITE);
							num = random();
						}
					}
					else {
						settextcolor(WHITE);
						outtextxy(800, 600, s2);
					}
				}
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(685, 400, s2);
		}
	}

}

int main() {
	int num;
	num = first();
	point p[25][25];
	initialize(p);
	begin(p, num);
	_getch();
	closegraph();
	return 0;
}