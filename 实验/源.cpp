#include<graphics.h>
#include<windows.h>
#include<cstdio>
#include<mmsystem.h>
#include<cmath>
#include "ChessData.h"
#include "AI.h"
#pragma comment(lib,"winmm.lib")

//�������̵Ĵ���
IMAGE chessBlack;                 //��loadimageһͬ
IMAGE chessWhite;

//ָ��ýṹ��ı���
struct ChessData chess;

int clickPosCol, clickPosRow;


//��ʼ��
void init()
{
	initgraph(785, 712);
	loadimage(0, _T("five.jpg"));       
	loadimage(&chessBlack, _T("hei.jpg"), CHESS_SIZE, CHESS_SIZE, true); 
	loadimage(&chessWhite, _T("bai.jpg"), CHESS_SIZE, CHESS_SIZE, true);
}
             
//�������
bool clickCheck(MOUSEMSG msg) 
//msg�Ǳ����� MOUSEMSG�Ƕ���õĽṹ��
{
	int col = (msg.x - LEFT) / BOARD_NUM1;     //��ȡ��
	int row = (msg.y - UP) / BOARD_NUM2;       

	int leftTop_x = LEFT + col * BOARD_NUM1;   //
	int leftTop_y = UP + row * BOARD_NUM2;

	int selectPos = false;
	do {
		int len = sqrt((msg.x - leftTop_x) * (msg.x - leftTop_x) +
			(msg.y - leftTop_y) * (msg.y - leftTop_y));
		if (len < POS_OFFSET)                  //�ڷ�Χ��
		{
			clickPosRow = row;
			clickPosCol = col;
			selectPos = true;
			break;
		}

		//���Ͻ�
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

		//���½�
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

		//���½�
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
	//���Ͻ�
	return selectPos;
}

int main()
{
	init();
	init_chessData(&chess);
	while (1)
	{
		MOUSEMSG msg = GetMouseMsg();      //��ȡ�����Ϣ
		if (msg.uMsg == WM_LBUTTONDOWN && clickCheck(msg))     //�������������ɹ�
		{
			struct chessPos pos;           //���԰�structȥ����
			pos.col = clickPosCol;
			pos.row = clickPosRow;
			int x, y;
			x = LEFT + clickPosCol * BOARD_NUM1 - 0.3 * CHESS_SIZE;
			y = UP + clickPosRow * BOARD_NUM2 - 0.4 * CHESS_SIZE;
			if (chess.Chessmap[clickPosCol][clickPosRow] != 0)  //������
			{
				continue;                                       
			}
			putimage(x, y, &chessBlack);                        //����ͼƬ
			chess.Chessmap[clickPosCol][clickPosRow] = 1;       //�к���
			if (checkOver(&pos, &chess))
			{
				system("pause");
				break;                                          //�˳�ѭ�� 
			}
			//�õ�������
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