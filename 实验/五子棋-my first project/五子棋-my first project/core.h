#pragma once
#include"stack.h"
//制作进攻分数表： 连五 / 死四/ 冲四/ 活四
//                 死点/ 死三/ 眠三 /活三
//                 死二/ 眠二/活二/ 一
//制作防守分数表： 连五 / 死四/ 冲四/ 活四
//                 死点/ 死三/ 眠三 /活三
//                 死二/ 眠二/活二/ 一
#define linkfive 1000000
#define livefour 20000
#define dashfour 5000
#define livethree 4999
#define sleepthree 500
#define livetwo 2499
#define sleeptwo 800
#define deadspot 0     //死点包括死二、死三、死四
#define one 500

typedef struct {
	int alpha;
	int beta;
}Node;
//制作节点
typedef enum {
	先手=1,后手
}Computertype;
//电脑属性：先手还是后手
//评估函数
int calculation(int arr[15][15], Computertype computertype);
int judge_sixBlack(int six[6]);
int judge_sixWhite(int six[6]);
int judge_fiveBlack(int five[5]);
int judge_fiveWhite(int five[5]);

int JudgeEmpty(int(*p)[15], int y, int x);

Stack* AIcomputer(int(*p)[15], Computertype computertype);