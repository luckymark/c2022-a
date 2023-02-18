#include "title.h"

MOUSEMSG m;

int playerVSAI()
{
	int x, y, manPiece =0, AIPiece = 0;

	/*黑白棋选择*/
	wchar_t choice[10];
	InputBox(choice, 10, L"选择白棋请输入1，选择黑棋请输入2");
	int chosenColor = _wtoi(choice);
	manPiece = chosenColor;
	while ((chosenColor!=white)&&(chosenColor!=black))
	{
		MessageBox(GetHWnd(), L"请正确输入棋子颜色", L"错误：", MB_OKCANCEL);
		InputBox(choice, 10, L"选择白棋请输入1，选择黑棋请输入2");
		chosenColor = _wtoi(choice);
		manPiece = chosenColor;
	}
	if (manPiece == white)
	{
		AIPiece = black;
	}
	else
	{
		AIPiece = white;
	}
	FlushMouseMsgBuffer();  //防误触

	/*绘制窗口*/
	drawBoard2();
	settextstyle(30, 0, L"宋体");
	settextcolor(RGB(70, 70, 70));
	outtextxy(200, 455, L"悔棋");

	
	/*执行*/
	if (AIPiece == black)
	{
		drawPiece(7, 7, AIPiece);
		map[7][7] = AIPiece; 
		num += 1;
		order[AIx][AIy] = num;
	}
	while (1)
	{
		m = GetMouseMsg();


		if (m.mkLButton)
		{
			/*人类*/
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
				judge(x, y,manPiece);           
				if (check == manPiece)
				{
					MessageBox(GetHWnd(), L"人类胜出！", L"游戏结束：", MB_OKCANCEL);
					break;
				}
				num += 1;
				order[x][y] = num;
				
				/*AI*/
				AI(x,y);
				drawPiece(AIx, AIy, AIPiece);
				map[AIx][AIy] = AIPiece;         
				judge(AIx, AIy,AIPiece);
				if (check == AIPiece)
				{
					MessageBox(GetHWnd(), L"AI胜出！", L"游戏结束：", MB_OKCANCEL);
					break;
				}
				if (check == tie)
				{
					MessageBox(GetHWnd(), L"平局", L"游戏结束：", MB_OKCANCEL);
					break;
				}
				num += 1;
				order[AIx][AIy] = num;
			}
			
		}
	}
	mciSendString(L"stop m", NULL, 0, NULL);    //停止播放音乐

	return 0;
}

	