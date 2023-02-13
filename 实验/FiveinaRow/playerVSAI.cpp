#include "title.h"

MOUSEMSG m;
int x, y, manPiece = 2, AIPiece = 1;

int playerVSAI()
{
	initgraph((map_width - 1) * piece_size + offsetx * 2, (map_height - 1) * piece_size + offsety * 4);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	for (int i = 0; i < map_width; i++)//竖线
	{
		line(i * piece_size + offsetx, offsety, i * piece_size + offsetx, offsety + (map_height - 1) * piece_size);
	}
	for (int i = 0; i < map_height; i++)//横线
	{
		line(offsetx, offsety + i * piece_size, (map_width - 1) * piece_size + offsetx, offsety + i * piece_size);
	}
	settextstyle(30, 0, L"宋体");
	settextcolor(RGB(70, 70, 70));
	outtextxy(200, 455, L"悔棋");

	num = 0, order[20][20] = { 0 }, jump = 0;


	while (1)
	{
		m = GetMouseMsg();
		if (m.mkLButton)
		{
			if ((m.x >= 180) && (m.x < 375) && (m.y >= 450) && (m.y <= 500))    //悔棋
			{
				regret();
				regret();
			}

			x = (m.x - offsetx + piece_size / 2) / piece_size;      //x的正整数化
			y = (m.y - offsety + piece_size / 2) / piece_size;
			if (pieceSet(x, y, manPiece))
			{
				drawPiece(x, y, manPiece);
				judge(x, y);           
				if (check == 2)
				{
					MessageBox(GetHWnd(), L"人类胜出！", L"游戏结束：", MB_OKCANCEL);
					break;
				}
				num += 1;
				order[x][y] = num;

				AI(x,y);
				drawPiece(AIx, AIy, AIPiece);
				map[AIx][AIy] = AIPiece;         //标记map值
				judge(AIx, AIy);
				if (check == 1)
				{
					MessageBox(GetHWnd(), L"AI胜出！", L"游戏结束：", MB_OKCANCEL);
					break;
				}
				if (check == 3)
				{
					MessageBox(GetHWnd(), L"平局", L"游戏结束：", MB_OKCANCEL);
					break;
				}
				num += 1;
				order[AIx][AIy] = num;
			}
			
		}
	}
	mciSendString(L"stop m", NULL, 0, NULL);
	return 0;
}

	