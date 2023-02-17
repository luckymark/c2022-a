#include<cstdio>
#include<cstring>
#include "ChessData.h"


void init_chessData(struct ChessData* data)                 //结构体变量的地址
{
	if (data == NULL)                 //确保非空
	{
		return;
	}
	memset(data->Chessmap, 0, sizeof(data->Chessmap));      //赋值？
	memset(data->Scoremap, 0, sizeof(data->Scoremap));
	data->playSign = true;

}