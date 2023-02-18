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
			MessageBox(GetHWnd(), L"白AI胜出！", L"游戏结束：", MB_OKCANCEL);
			break;
		}
		if (check == black)
		{
			MessageBox(GetHWnd(), L"黑AI胜出！", L"游戏结束：", MB_OKCANCEL);
			break;
		}
		if (check ==tie)
		{
			MessageBox(GetHWnd(), L"平局", L"游戏结束：", MB_OKCANCEL);
			break;
		}

		Piece += changePiece;
		changePiece *= -1;	
	}


	mciSendString(L"stop m", NULL, 0, NULL);     //停止播放音乐
	return 0;
}
