#ifndef _HEAD_
#define _HEAD_

#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<queue>
extern int gamemode;
const int windowWidth = 720;
const int windowHeight = 720;
const enum kind { EMPTY, WHITE, BLACK };
struct chess {//棋子
	int chesskind = EMPTY;
};
extern chess chessmap[15][15];//用于逻辑判断的数据

struct chess_pos {
	int xpos;
	int ypos;
};

struct formstatistic {//用于局面棋型统计
	int l5_b = 0;//活五
	int l5_w = 0;
	int l4_b = 0;//活四
	int l4_w = 0;
	int d4_b = 0;//死四
	int d4_w = 0;
	int l3_b = 0;//活三
	int l3_w = 0;
	int d3_b = 0;//死三
	int d3_w = 0;
	int l2_b = 0;//活二
	int l2_w = 0;
	int d2_b = 0;//死二
	int d2_w = 0;
};

struct judgetree {//决策树
	chess_pos donepos;
	int expectation;
	int gd_expectation;
	struct judgetree* bor_node;
	struct judgetree* kid_node;
	struct judgetree* listend;
};

extern int AI_ThinkWidth[4];//划定AI选取局部最优解的范围,0~4分别为上下左右
extern chess_pos chess_pos_cursor;
extern int count;
extern bool isWin;
extern int chess_draw_list[15 * 15][3];
void winchack(int nowchess[3]);
struct judgetree* AI_MakeTree();
int AI_Analysis(int cnt, int btw, int dis_1, int dis_2);//棋型分析函数
int AI_Calculation(struct formstatistic);//评分函数
void AI_Estimate();//评估函数
void AI_Judgetree_BuildTree(struct judgetree* root, int height);//建立五层决策树
void AI_JudgeTree_Choose(struct judgetree* root);
void AI_JudgeTree_Delete(struct judgetree* root);
void AI_Running();
#endif 