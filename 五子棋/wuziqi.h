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
	int flag = 0;//���ڱ���Ƿ���������,-1��ʾ���¹��ˣ�1��ʾ��û�£��������ں�������,2��ʾ��������,3��ʾ���Ž�
}p;
typedef struct alphabeta {//��֦����
	int a = -100000000, b = 100000000;
}ab;
enum { len = 19 };


int getposition();
void draw_piece(int x, int y);
int judge(void);//�ж���Ϸ�Ƿ����
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
//void cut(int acolor, ab now, int value);//��Ϊ��now�����ʵ��̫�࣬���������ַ���
int minormax(int a, int b, int c, int minormax);//��������ͨͨ������С���ֵ��
void firstab(ab now, int acolor, int min, int max);




extern int step;
extern IMAGE a;
extern ab bridge;//���ڲ�ͬ��ȵĴ���
extern int bc;
extern const int DEPTH;
extern int firsttime;
extern int whetherfive;
extern IMAGE a;
extern int color, flag;
extern int qp[len][len];
extern int qpvalue[len][len];
extern p xyvalue[len][len];
extern p best;//��õ�λ

