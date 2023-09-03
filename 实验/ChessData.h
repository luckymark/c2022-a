#pragma once
#include <stdbool.h>

#define CHESS_SIZE 40        //���Ӵ�С            
#define BOARD_SIZE 16        //����������         
const int BOARD_NUM1 = 50;   //��������ʲô��˼
const int BOARD_NUM2 = 45;
const int POS_OFFSET = (CHESS_SIZE * 0.4);
const int LEFT = 5;
const int UP = 9;

struct ChessData {
	//0:�հ�  1������  -1������
	int Chessmap[BOARD_SIZE][BOARD_SIZE];       //boolҲ��

	//������ļ�ֵ
	int Scoremap[BOARD_SIZE][BOARD_SIZE];

	//true:��  false:��
	bool playSign;           
};


extern void init_chessData(struct ChessData*);