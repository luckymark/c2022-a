#include "title.h"

MOUSEMSG m;

int playerVSAI()
{
	int x, y, manPiece =0, AIPiece = 0;

	/*�ڰ���ѡ��*/
	wchar_t choice[10];
	InputBox(choice, 10, L"ѡ�����������1��ѡ�����������2");
	int chosenColor = _wtoi(choice);
	manPiece = chosenColor;
	while ((chosenColor!=white)&&(chosenColor!=black))
	{
		MessageBox(GetHWnd(), L"����ȷ����������ɫ", L"����", MB_OKCANCEL);
		InputBox(choice, 10, L"ѡ�����������1��ѡ�����������2");
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
	FlushMouseMsgBuffer();  //����

	/*���ƴ���*/
	drawBoard2();
	settextstyle(30, 0, L"����");
	settextcolor(RGB(70, 70, 70));
	outtextxy(200, 455, L"����");

	
	/*ִ��*/
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
			/*����*/
			if ((m.x >= 180) && (m.x < 375) && (m.y >= 450) && (m.y <= 500))    //����
			{
				regret();
				regret();
			}

			x = (m.x - offsetx + piece_size / 2) / piece_size;      //x����������
			y = (m.y - offsety + piece_size / 2) / piece_size;
			if (pieceSet(x, y, manPiece))
			{
				drawPiece(x, y, manPiece);
				judge(x, y,manPiece);           
				if (check == manPiece)
				{
					MessageBox(GetHWnd(), L"����ʤ����", L"��Ϸ������", MB_OKCANCEL);
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
					MessageBox(GetHWnd(), L"AIʤ����", L"��Ϸ������", MB_OKCANCEL);
					break;
				}
				if (check == tie)
				{
					MessageBox(GetHWnd(), L"ƽ��", L"��Ϸ������", MB_OKCANCEL);
					break;
				}
				num += 1;
				order[AIx][AIy] = num;
			}
			
		}
	}
	mciSendString(L"stop m", NULL, 0, NULL);    //ֹͣ��������

	return 0;
}

	