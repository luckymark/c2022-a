#pragma once
#include <stdbool.h>

#define CHESS_SIZE 40        //棋子大小            
#define BOARD_SIZE 16        //棋盘行列数         
const int BOARD_NUM1 = 50;   //这两个数什么意思
const int BOARD_NUM2 = 45;
const int POS_OFFSET = (CHESS_SIZE * 0.4);
const int LEFT = 5;
const int UP = 9;

struct ChessData {
	//0:空白  1：黑子  -1：白子
	int Chessmap[BOARD_SIZE][BOARD_SIZE];       //bool也行

	//各个点的价值
	int Scoremap[BOARD_SIZE][BOARD_SIZE];

	//true:黑  false:白
	bool playSign;           
};


extern void init_chessData(struct ChessData*);