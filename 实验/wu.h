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
#define C_NONE 0//���ӣ�����,����,����
#define C_BLACK 1
#define C_WHITE 2
#define C_PLACE 2
//���ʹ��� �±� Ȩ��
#define OTHER 0//0,
#define WIN 1//100000,��Ӯ
#define LOSE 2//-10000000
#define FLEX4 3//50000,�׻�4
#define flex4 4//-80000
#define BLOCK4 5//400
#define block4 6//-80000
#define FLEX3 7//400��

#define flex3 8//-8000

#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20��
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2
#define GO -155
#define FLEX30 17//400��
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

void start();											//��Ϸ��ʼ��

void board();											//�滭����

int success(int[15][15]);								//ʤ�������ж�

void regret(int[15][15], int[15][15]);					//����

void machine1();											//�˻�����

void machine2();                                        //�˻�����

void win(int);								//ʤ������	

void over();								//��Ϸ����

point seekpoint(int[15][15],int);          //Ѱ�����

double MAXMINvalue(int [15][15], int , double , double );   //����Сֵ�����Ӽ�֦

void init_tuple6type();                          //��ʼ������

EVALUATION evaluate(int [15][15]);      //��ֵ

void downpoint(int, int);                    //���