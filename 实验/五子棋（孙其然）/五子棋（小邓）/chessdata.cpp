//chessdata.cpp
#include"chessdata.h"
#include<stdio.h>
#include<memory.h>

//���ڳ�ʼ��  ȫ����ֵΪ0
void initChessData(struct ChessData* data)
{
	if (!data)return;
	memset(data->chessMap, 0, sizeof(data->chessMap));
	memset(data->scoreMap, 0, sizeof(data->scoreMap));
	data->playerFlag = true;
}
