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
		if (msg.x < PICTURE_WIDTH) {
			if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
			{
				printf("%d %d\n", pos.x, pos.y);
				break;
			}
		}
		
		else if (msg.uMsg == WM_LBUTTONDOWN
			&& msg.x< CHESSMAP_WIDTH - 50
			&& msg.x> PICTURE_WIDTH +50
			&& msg.y < PICTURE_HEIGHT - 150
			&& msg.y>400) {
			printf("%d %d\n",msg.x,msg.y);
			chess->changchessif= !chess->changchessif;
			chess->changEchessif = 1;
			break;
		}
		else if (msg.uMsg == WM_LBUTTONDOWN
			&& msg.x< CHESSMAP_WIDTH - 50
			&& msg.x> PICTURE_WIDTH + 50
			&& msg.y < PICTURE_HEIGHT - 250
			&& msg.y>300) {
			printf("%d %d\n", msg.x, msg.y);
			chess->gobackchess();
		}
		else if (msg.uMsg == WM_LBUTTONDOWN
			&& msg.x< CHESSMAP_WIDTH - 50
			&& msg.x> PICTURE_WIDTH + 50
			&& msg.y < PICTURE_HEIGHT - 350
			&& msg.y>200) {
			printf("%d %d\n", msg.x, msg.y);
			chess->faill();
		}
	}

	

	//落子
	chess->chessDown(&pos, CHESS_BLACK);
}
