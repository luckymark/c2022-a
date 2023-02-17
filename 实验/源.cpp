#include<graphics.h>
#include<windows.h>
#include<cstdio>
#include<mmsystem.h>
#include<cmath>
#include "ChessData.h"
#include "AI.h"
#pragma comment(lib,"winmm.lib")

//创建棋盘的窗口
IMAGE chessBlack;                 //和loadimage一同
IMAGE chessWhite;

//指向该结构体的变量
struct ChessData chess;

int clickPosCol, clickPosRow;


//初始化
void init()
{
	initgraph(785, 712);
	loadimage(0, _T("five.jpg"));       
	loadimage(&chessBlack, _T("hei.jpg"), CHESS_SIZE, CHESS_SIZE, true); 
	loadimage(&chessWhite, _T("bai.jpg"), CHESS_SIZE, CHESS_SIZE, true);
}
             
//下棋操作
bool clickCheck(MOUSEMSG msg) 
//msg是变量名 MOUSEMSG是定义好的结构体
{
	int col = (msg.x - LEFT) / BOARD_NUM1;     //会取整
	int row = (msg.y - UP) / BOARD_NUM2;       

	int leftTop_x = LEFT + col * BOARD_NUM1;   //
	int leftTop_y = UP + row * BOARD_NUM2;

	int selectPos = false;
	do {
		int len = sqrt((msg.x - leftTop_x) * (msg.x - leftTop_x) +
			(msg.y - leftTop_y) * (msg.y - leftTop_y));
		if (len < POS_OFFSET)                  //在范围内
		{
			clickPosRow = row;
			clickPosCol = col;
			selectPos = true;
			break;
		}

		//右上角
		int posX = leftTop_x + BOARD_NUM1;
		int posY = leftTop_y;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET)
		{
			clickPosRow = row;
			clickPosCol = col + 1;
			selectPos = true;
			break;
		}

		//右下角
		posX = leftTop_x + BOARD_NUM1;
		posY = leftTop_y + BOARD_NUM2;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET)
		{
			clickPosRow = row + 1;
			clickPosCol = col + 1;
			selectPos = true;
			break;
		}

		//左下角
		posX = leftTop_x;
		posY = leftTop_y + BOARD_NUM2;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET)
		{
			clickPosRow = row + 1;
			clickPosCol = col;
			selectPos = true;
			break;
		}
	} while (0);
	//左上角
	return selectPos;
}

int main()
{
	init();
	init_chessData(&chess);
	while (1)
	{
		MOUSEMSG msg = GetMouseMsg();      //获取鼠标信息
		if (msg.uMsg == WM_LBUTTONDOWN && clickCheck(msg))     //是左键且人下棋成功
		{
			struct chessPos pos;           //可以把struct去掉？
			pos.col = clickPosCol;
			pos.row = clickPosRow;
			int x, y;
			x = LEFT + clickPosCol * BOARD_NUM1 - 0.3 * CHESS_SIZE;
			y = UP + clickPosRow * BOARD_NUM2 - 0.4 * CHESS_SIZE;
			if (chess.Chessmap[clickPosCol][clickPosRow] != 0)  //若无棋
			{
				continue;                                       
			}
			putimage(x, y, &chessBlack);                        //载入图片
			chess.Chessmap[clickPosCol][clickPosRow] = 1;       //有黑棋
			if (checkOver(&pos, &chess))
			{
				system("pause");
				break;                                          //退出循环 
			}
			//该电脑下棋
			pos = think(&chess);                              
			x = LEFT + pos.col * BOARD_NUM1 - 0.3 * CHESS_SIZE;
			y = UP + pos.row * BOARD_NUM2 - 0.4 * CHESS_SIZE;
			putimage(x, y, &chessWhite);
			chess.Chessmap[pos.col][pos.row] = -1;
			if (checkOver(&pos, &chess))
			{
				system("pause");
				break;
			}
		}

	}


	system("pause");
}