#pragma once
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include<mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")
#define R_DRAW 33
#define R_WHITE 66
#define R_BLACK 99
#define DEEP 4
#define C_NONE 0//棋子：黑子,白子,无子
#define C_BLACK 1
#define C_WHITE 2
#define C_PLACE 2
//棋型代号 下标 权重
#define OTHER 0//0,
#define WIN 1//100000,白赢
#define LOSE 2//-10000000
#define FLEX4 3//50000,白活4
#define flex4 4//-80000
#define BLOCK4 5//400
#define block4 6//-80000
#define FLEX3 7//400白

#define flex3 8//-8000

#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20白
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2
#define GO -155
#define FLEX30 17//400白
#define flex30 18//-4000
#define BLOCK40 19
#define block40   20
#define BLOCK401 21
#define numb  4
typedef struct point {
    int x[numb];
    int y[numb];
    double tscore[numb];

}point;

typedef struct EVALUATION {
	double score;
	int result;
	int STAT[8];
}EVALUATION;

void start();											//游戏初始化

void board();											//绘画棋盘

int success(int[15][15]);								//胜利条件判断

void regret(int[15][15], int[15][15]);					//悔棋

void machine1();											//人机后手

void machine2();                                        //人机先手

void win(int);								//胜利界面	

void over();								//游戏结束

point seekpoint(int[15][15],int);          //寻找落点

double MAXMINvalue(int [15][15], int , double , double );   //极大极小值搜索加剪枝

void init_tuple6type();                          //初始化棋型

EVALUATION evaluate(int [15][15]);      //估值

void downpoint(int, int);                    //落点