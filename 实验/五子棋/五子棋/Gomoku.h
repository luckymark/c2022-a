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

#define JUDGE 10         // �жϷ���/����
#define VALUE 10         //λ�ó�ʼ���Լ�����
#define MIN 5
#define MAX 20
long double A = -999999999999999999;
long double B = 999999999999999999;
int ii = 0, jj = 0, xx = 0, yy = 0;    //��¼��һ����λ��
int num = 0;    //���Ĵ���

void board();	//�滭����
void regret(struct point p[25][25]);		//����
void begin(struct point p[25][25]);  	//��ʼ
int robot(struct point p[25][25]);		//����ִ��
void over(int x);		//��������	
void value(struct point p[25][25]);     //ĳ���ֵ������
double all_value(struct point p[25][25]);     //������������
double recursion(struct point p[25][25], int sex, int depth, long double a, long double b);//�ݹ����� 
int end(struct point p[25][25]);     //ʤ����������
void initialize(struct point p[25][25]);    //���̳�ʼ��
void play(struct point p[25][25], int x, int y);    //����
