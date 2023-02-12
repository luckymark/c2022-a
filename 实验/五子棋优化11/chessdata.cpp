#include"chessdata.h"
#include<stdio.h>
#include<memory.h>

extern int turn;

void initchessdata(chessdata* data)
{
	if (!data) {
		return;
	}

	memset(data->chessmap, 0, sizeof(data->chessmap));
	turn = 0;
}
