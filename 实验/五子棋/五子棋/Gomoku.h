#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include<mmsystem.h>
#include<easyx.h>
#include<iostream>
#include<stdlib.h>

#define JUDGE 10         // 判断防守/攻击
#define VALUE 10         //位置初始分以及倍率
#define MIN 5
#define MAX 20
long double A = -999999999999999999;
long double B = 999999999999999999;
int ii = 0, jj = 0, xx = 0, yy = 0;    //记录上一步棋位置
int num = 0;    //对弈次数

void board();	//绘画棋盘
void regret(struct point p[25][25]);		//悔棋
void begin(struct point p[25][25]);  	//开始
int robot(struct point p[25][25]);		//电脑执棋
void over(int x);		//结束界面	
void value(struct point p[25][25]);     //某点价值分评定
double all_value(struct point p[25][25]);     //局面优势评估
double recursion(struct point p[25][25], int sex, int depth, long double a, long double b);//递归推演 
int end(struct point p[25][25]);     //胜负代数返回
void initialize(struct point p[25][25]);    //棋盘初始化
void play(struct point p[25][25], int x, int y);    //下棋
