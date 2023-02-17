#pragma once
#include "ChessData.h"

struct chessPos
{
	int row;
	int col;
};

void calculateScore(ChessData* chess);   
//返回值是个结构体
chessPos think(ChessData*);                    //
bool checkOver(chessPos* pos, ChessData* chess);     //判断胜负