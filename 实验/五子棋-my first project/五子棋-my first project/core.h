#pragma once
#include"stack.h"
//�������������� ���� / ����/ ����/ ����
//                 ����/ ����/ ���� /����
//                 ����/ �߶�/���/ һ
//�������ط����� ���� / ����/ ����/ ����
//                 ����/ ����/ ���� /����
//                 ����/ �߶�/���/ һ
#define linkfive 1000000
#define livefour 20000
#define dashfour 5000
#define livethree 4999
#define sleepthree 500
#define livetwo 2499
#define sleeptwo 800
#define deadspot 0     //�����������������������
#define one 500

typedef struct {
	int alpha;
	int beta;
}Node;
//�����ڵ�
typedef enum {
	����=1,����
}Computertype;
//�������ԣ����ֻ��Ǻ���
//��������
int calculation(int arr[15][15], Computertype computertype);
int judge_sixBlack(int six[6]);
int judge_sixWhite(int six[6]);
int judge_fiveBlack(int five[5]);
int judge_fiveWhite(int five[5]);

int JudgeEmpty(int(*p)[15], int y, int x);

Stack* AIcomputer(int(*p)[15], Computertype computertype);