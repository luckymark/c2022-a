//五子棋.cpp头文件
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
extern int gamer_color;
const int windowWidth = 1440;
const int windowHeight = 1440;
const enum kind { EMPTY, WHITE, BLACK };
struct chess {//棋子
	int chesskind = EMPTY;
};
extern chess chessmap[15][15];

 struct chess_pos {
	int xpos;
	int ypos;
};

struct judgetree {//决策树
	chess_pos donepos;
	int expectation;
	struct judgetree* bor_node;
	struct judgetree* kid_node;
	struct judgetree* listend;
};

extern int AI_ThinkWidth[4];//划定AI选取局部最优解的范围,0~4分别为上下左右
extern chess_pos chess_pos_cursor;
extern int count;
extern bool isWin;
extern int chess_draw_list[15 * 15][3];
void winchack(int nowchess[3]);//根据最新落子，判断是否游戏结束，参数：最新落子数据
struct judgetree* AI_MakeTree(int height);//新建空树
int AI_Analysis(int cnt, int btw, int dis_1, int dis_2,int i);//棋型分析函数
void AI_Estimate();//评估函数
bool AI_Judgetree_Greedy(struct judgetree* root, int height);//贪心搜索
void AI_Judgetree_BuildTree(struct judgetree* root, int height,int stoppos,int gd_expectation,int fa_expectation);//建立3层最大最小决策树，同步进行剪枝
void AI_JudgeTree_Choose(struct judgetree* root);//输出最终落子
void AI_JudgeTree_Delete(struct judgetree* root);//删除树
void AI_Running();//AI运行程序
#endif 