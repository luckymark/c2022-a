#pragma once
#include "ChessData.h"

struct chessPos
{
	int row;
	int col;
};

void calculateScore(ChessData* chess);   
//����ֵ�Ǹ��ṹ��
chessPos think(ChessData*);                    //
bool checkOver(chessPos* pos, ChessData* chess);     //�ж�ʤ��