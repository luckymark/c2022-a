#include "title.h"


int AIVSAI()
{
	int enemyPiece = 0;

	drawBoard2();

	Piece = black;
	changePiece=-1;


	AIx = 7, AIy = 7;
	map[AIx][AIy] = Piece;
	drawPiece(AIx, AIy, Piece);
	Piece += changePiece;
	changePiece *= -1;
	while (1)
	{
		AI(AIx, AIy);
		drawPiece(AIx, AIy, Piece);
		map[AIx][AIy] = Piece;
		judge(AIx, AIy,Piece);

		if (check == white)
		{
			MessageBox(GetHWnd(), L"��AIʤ����", L"��Ϸ������", MB_OKCANCEL);
			break;
		}
		if (check == black)
		{
			MessageBox(GetHWnd(), L"��AIʤ����", L"��Ϸ������", MB_OKCANCEL);
			break;
		}
		if (check ==tie)
		{
			MessageBox(GetHWnd(), L"ƽ��", L"��Ϸ������", MB_OKCANCEL);
			break;
		}

		Piece += changePiece;
		changePiece *= -1;	
	}


	mciSendString(L"stop m", NULL, 0, NULL);     //ֹͣ��������
	return 0;
}
