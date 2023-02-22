#include "Chess.h"
#include "Chessman.h"



void Chessman::init(Chess* chess)
{
	this->chess = chess;
}

void Chessman::move()
{
	//�����Ϣ�洢���������λ��
	ChessPos pos;

	//�����Ϣ�洢λ��
	MOUSEMSG msg;
	
	
	while (1)
	{
		//��ȡ�������Ϣ
		msg=GetMouseMsg();
		
		//ͨ��chess�������ж������Ƿ���Ч
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

	

	//����
	chess->chessDown(&pos, CHESS_BLACK);
}
