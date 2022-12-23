#include "Chess.h"
#include "Chessman.h"



void Chessman::init(Chess* chess)
{
	this->chess = chess;
}

void Chessman::move()
{
	//鼠标信息存储在下面这个位置
	ChessPos pos;

	//鼠标信息存储位置
	MOUSEMSG msg;
	
	
	while (1)
	{
		//获取鼠标点击信息
		msg=GetMouseMsg();
		
		//通过chess对象来判断落子是否有效
	
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			
			printf("%d %d", pos.x, pos.y);
			break;
		}		
	}

	

	//落子
	chess->chessDown(&pos, CHESS_BLACK);
}
