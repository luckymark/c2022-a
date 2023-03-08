//chessdata.cpp
#include"chessdata.h"
#include<stdio.h>
#include<memory.h>

//用于初始化  全部赋值为0
void initChessData(struct ChessData* data)
{
	if (!data)return;
	memset(data->chessMap, 0, sizeof(data->chessMap));
	memset(data->scoreMap, 0, sizeof(data->scoreMap));
	data->playerFlag = true;
}
