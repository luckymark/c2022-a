#include "title.h"
int Piece = black;
int changePiece = -1;
int order[20][20] = { 0 }, num = 0, jump = 0;

int playerVSplayer()
{
	drawBoard2();
	settextstyle(30, 0, L"����");
	settextcolor(RGB(70, 70, 70));
	outtextxy(200, 455, L"����");


	MOUSEMSG m;
	int x, y;
	
	while (1)
	{
		m = GetMouseMsg();
		
		if (m.mkLButton)
		{
			if ((m.x >= 180) && (m.x < 375) && (m.y >= 450) && (m.y <= 500))
			{
				regret();
			}
			
			x = (m.x - offsetx + piece_size / 2) / piece_size;     //x��piece_size������������������
			y = (m.y - offsety + piece_size / 2) / piece_size;
			if (pieceSet(x, y, Piece))    
			{
				drawPiece(x, y, Piece);

				judge(x, y,Piece);
				if (check == white)
				{
					MessageBox(GetHWnd(), L"����ʤ����", L"��Ϸ������", MB_OKCANCEL);
					break;
				}
				if (check == black)
				{
					MessageBox(GetHWnd(), L"����ʤ����", L"��Ϸ������", MB_OKCANCEL);
					break;
				}

				Piece += changePiece;
				changePiece *= -1;
				
				num = num + 1;
				order[x][y] = num;
				
			}
		}
	}
	mciSendString(L"stop m", NULL, 0, NULL);   //ֹͣ��������

	return 0;
}