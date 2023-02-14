#pragma once
#include <graphics.h>
#include <conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<mmsystem.h>
#include<time.h>
#include<Windows.h>
//#programe  cocolcolent(lib,"winmm.lib")
typedef struct positionandvalue {
	int x = 0, y = 0;
	int value = 0;
	int flag = 0;//用于标记是否用于搜索,-1表示被下过了，1表示还没下，但会用于后续搜索,2表示搜索过了,3表示最优解
}p;
typedef struct alphabeta {//剪枝所用
	int a = -100000000, b = 100000000;
}ab;
enum { len = 19 };


int getposition();
void draw_piece(int x, int y);
int judge(void);//判断游戏是否结束
void endgame(void);
void init(void);

void findblank(void);
int evaluate(int x, int y, int acolor);
void fillblank(void);
void aidraw(void);
int getscore(void);
int count(int x, int y, int direction);
int findbest(int acolor, int depth, ab c);
void qpevaluate(void);
//void cut(int acolor, ab now, int value);//因为改now的情况实在太多，故舍弃这种方法
int minormax(int a, int b, int c, int minormax);//就是普普通通的找最小最大值的
void firstab(ab now, int acolor, int min, int max);




extern int step;
extern IMAGE a;
extern ab bridge;//用于不同深度的传递
extern int bc;
extern const int DEPTH;
extern int firsttime;
extern int whetherfive;
extern IMAGE a;
extern int color, flag;
extern int qp[len][len];
extern int qpvalue[len][len];
extern p xyvalue[len][len];
extern p best;//最好的位

