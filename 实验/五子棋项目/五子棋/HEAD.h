//������.cppͷ�ļ�
#ifndef _HEAD_
#define _HEAD_

#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<math.h>
extern int gamemode;
extern int gamer_color;
const int windowWidth = 1440;
const int windowHeight = 1440;
const int LineWidth = 6;
const int ChessSize = 80;
const enum kind { EMPTY, WHITE, BLACK };
struct chess {//����
	int chesskind = EMPTY;
};
extern chess chessmap[15][15];

 struct chess_pos {
	int xpos;
	int ypos;
};
typedef struct judgetree {//������
	chess_pos donepos;
	int expectation;
	int heuristic_value;
	struct judgetree* bor_node;
	struct judgetree* kid_node;
	struct judgetree* listend;

}judgetree;
extern int AI_ThinkWidth[4];//����AIѡȡ�ֲ����Ž�ķ�Χ,0~4�ֱ�Ϊ��������
extern chess_pos chess_pos_cursor;
extern int count;
extern bool isWin;
extern int chess_draw_list[15 * 15][3];
void wincheck(int nowchess[3]);//�����������ӣ��ж��Ƿ���Ϸ������������������������
struct judgetree* AI_Judgetree_MakeTree(int height);//�½�����
int AI_Analysis(int cnt, int btw, int dis_1, int dis_2,int i);//���ͷ�������
void AI_Estimate();//��������
bool AI_Judgetree_Greedy(struct judgetree* root, int height,int* fa_expectation,int* stoppos);//̰������
void AI_Judgetree_BuildTree(struct judgetree* root, int height,int stoppos,int gd_expectation,int fa_expectation);//����3�������С��������ͬ�����м�֦
void AI_JudgeTree_Choose(struct judgetree* root);//�����������
void AI_JudgeTree_Delete(struct judgetree* root);//ɾ����
void AI_Running();//AI���г���
#endif 