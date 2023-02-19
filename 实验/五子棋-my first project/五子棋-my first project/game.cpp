#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<time.h>
#include"interface.h"
#include"game.h"
#include"core.h"

int bushu = 0;                       //���岽��
int arr[15][15] = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},    //0��ʾ��λ��1��ʾ���壬2��ʾ����
};
int (*cp[2])(int) = { caculateX ,caculateY };
void (*rp[3])(int, int) = { printred,clearredBlack,clearredWhite };
player Players;
static int cx = 20, cy = 20;
int computer;

void playmusic(int musicchoice)
{
	switch (musicchoice)
	{
	case 1:
		mciSendString(L"open D:\\CloudMusic\\ѯ��1.mp3 alias ѯ��1", NULL, 0, NULL);
		mciSendString(L"play ѯ��1 repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"open D:\\CloudMusic\\ѯ��2.mp3 alias ѯ��2", NULL, 0, NULL);
		mciSendString(L"play ѯ��2 repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"open D:\\CloudMusic\\ѯ��3.mp3 alias ѯ��3", NULL, 0, NULL);
		mciSendString(L"play ѯ��3 repeat", NULL, 0, NULL);
		break;
	case 4:
		mciSendString(L"open D:\\CloudMusic\\ѯ��4.mp3 alias ѯ��4", NULL, 0, NULL);
		mciSendString(L"play ѯ��4 repeat", NULL, 0, NULL);
		break;
	default:
		printf("û���ҵ������֣�\a\n");
		exit(0);
	}
}

void closemusic(int musicchoice)
{
	switch (musicchoice)
	{
	case 1:
		mciSendString(L"close ѯ��1 ", NULL, 0, NULL);
		mciSendString(L"close ѯ��1+ ", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"close ѯ��2 ", NULL, 0, NULL);
		mciSendString(L"close ѯ��2+ ", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"close ѯ��3 ", NULL, 0, NULL);
		mciSendString(L"close ѯ��3+ ", NULL, 0, NULL);
		break;
	case 4:
		mciSendString(L"close ѯ��4 ", NULL, 0, NULL);
		mciSendString(L"close ѯ��4+ ", NULL, 0, NULL);
		break;
	default:
		exit(0);
	}
}

void changemusic(int musicchoice)
{
	switch (musicchoice)
	{
	case 1:
		mciSendString(L"close ѯ��1", NULL, 0, NULL);
		mciSendString(L"open D:\\CloudMusic\\ѯ��1+.mp3 alias ѯ��1+", NULL, 0, NULL);
		mciSendString(L"play ѯ��1+ repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"close ѯ��2", NULL, 0, NULL);
		mciSendString(L"open D:\\CloudMusic\\ѯ��2+.mp3 alias ѯ��2+", NULL, 0, NULL);
		mciSendString(L"play ѯ��2+ repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"close ѯ��3", NULL, 0, NULL);
		mciSendString(L"open D:\\CloudMusic\\ѯ��3+.mp3 alias ѯ��3+", NULL, 0, NULL);
		mciSendString(L"play ѯ��3+ repeat", NULL, 0, NULL);
		break;
	case 4:
		mciSendString(L"close ѯ��4", NULL, 0, NULL);
		mciSendString(L"open D:\\CloudMusic\\ѯ��4+.mp3 alias ѯ��4+", NULL, 0, NULL);
		mciSendString(L"play ѯ��4+ repeat", NULL, 0, NULL);
		break;
	default:
		exit(0);
	}
}
//���ֲ��ţ��ر������

void printred(int x, int y)
{
	setlinecolor(RED);
	circle(x * 40 + 50, y * 40 + 50, 18);
}
void clearredWhite(int x, int y)
{
	setlinecolor(WHITE);
	circle(x * 40 + 50, y * 40 + 50, 18);
}
void clearredBlack(int x, int y)
{
	setlinecolor(BLACK);
	circle(x * 40 + 50, y * 40 + 50, 18);
}
//���ɫ��Ȧ��غ���
int caculateX(int X)
{
	if ((X - 50) % 40 < 10)
	{
		return (X - 50) / 40;
	}
	else if ((X - 50) % 40 > 30)
	{
		return (X - 50) / 40 + 1;
	}
	else
	{
		return 20;
	}
}
int caculateY(int Y)
{
	if ((Y - 50) % 40 < 10)
	{
		return (Y - 50) / 40;
	}
	else if ((Y - 50) % 40 > 30)
	{
		return (Y - 50) / 40 + 1;
	}
	else
	{
		return 20;
	}
}
//������������
void Judge_victory(player Players, int playertype, int arr[15][15], int x, int y, int musicchoice)  //1Ϊ���壬2Ϊ����
{
	int assist[23][23] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	int a, b;
	x += 4;
	y += 4;
	for (int aa = 0; aa < 15; aa++)              //���츨�����鲢�Ҹ�������
	{
		for (int bb = 0; bb < 15; bb++)
		{
			assist[aa + 4][bb + 4] = arr[aa][bb];
		}
	}

	for (a = x - 4; a <= x; a++)         //�����ж�
	{
		if (assist[y][a] == playertype && assist[y][a + 1] == playertype
			&& assist[y][a + 2] == playertype
			&& assist[y][a + 3] == playertype && assist[y][a + 4] == playertype)
		{
			if (Players == 1)
			{
				closemusic(musicchoice);
				Sleep(2000);
				victory();
			}
			else
			{
				closemusic(musicchoice);
				Sleep(2000);
				failure();
			}
		}
	}
	for (a = y - 4; a <= y; a++)           //�����ж�
	{
		if (assist[a][x] == playertype && assist[a + 1][x] == playertype && assist[a + 2][x] == playertype
			&& assist[a + 3][x] == playertype && assist[a + 4][x] == playertype)
		{
			if (Players == 1)
			{
				closemusic(musicchoice);
				Sleep(2000);
				victory();
			}
			else
			{
				closemusic(musicchoice);
				Sleep(2000);
				failure();
			}
		}
	}
	for (a = x - 4, b = y - 4; a <= x && b <= y; a++, b++)    //б���ж�
	{
		if (assist[b][a] == playertype && assist[b + 1][a + 1] == playertype && assist[b + 2][a + 2] == playertype
			&& assist[b + 3][a + 3] == playertype && assist[b + 4][a + 4] == playertype)
		{
			if (Players == 1)
			{
				closemusic(musicchoice);
				Sleep(2000);
				victory();
			}
			else
			{
				closemusic(musicchoice);
				Sleep(2000);
				failure();
			}
		}
	}
	for (a = x - 4, b = y + 4; a <= x && b >= y; a++, b--)
	{
		if (assist[b][a] == playertype && assist[b - 1][a + 1] == playertype && assist[b - 2][a + 2] == playertype
			&& assist[b - 3][a + 3] == playertype && assist[b - 4][a + 4] == playertype)
		{
			if (Players == 1)
			{
				closemusic(musicchoice);
				Sleep(2000);
				victory();
			}
			else
			{
				closemusic(musicchoice);
				Sleep(2000);
				failure();
			}
		}
	}
}

void computerplay(int playertype, int X, int Y, int musicchoice)
{                                               //��������

	setbkcolor(LIGHTMAGENTA);
	settextcolor(WHITE);
	outtextxy(0, 0, L"������=>");
	srand((unsigned)time(NULL));

	Stack* HumanFirst = NULL, *PCfirst = NULL;

	if (playertype == 1) {

		setfillcolor(WHITE);
		setlinecolor(WHITE);

		if (bushu == 1) {
			do
			{
				cx = rand() % 3 + 6;
				cy = rand() % 3 + 6;
			} while (arr[cy][cx] == 1);
		}
		else {
			HumanFirst = AIcomputer(arr, ����);
			cy = pop(HumanFirst);
			cx = pop(HumanFirst);
		}

		arr[cy][cx] = 2;
		rp[1](cp[0](X), cp[1](Y));
		fillcircle(cx * 40 + 50, cy * 40 + 50, 18);
		bushu++;           //��¼����

		rp[0](cx, cy);

		Judge_victory(����, 2, arr, cx, cy, musicchoice);

		if (bushu == 225)
		{
			closemusic(musicchoice);
			draw();
		}
	}
	else
	{
		setfillcolor(BLACK);
		setlinecolor(BLACK);
		if (bushu == 0)
		{
			cx = rand() % 3 + 6;
			cy = rand() % 3 + 6;
		}
		else
		{
			PCfirst=AIcomputer(arr,����);
			cy = pop(PCfirst);
			cx = pop(PCfirst);
		}

		rp[2](cp[0](X), cp[1](Y));
		arr[cy][cx] = 1;
		fillcircle(cx * 40 + 50, cy * 40 + 50, 18);
		bushu++;            //��¼����

		rp[0](cx, cy);

		Judge_victory(����, 1, arr, cx, cy, musicchoice);

		if (bushu == 225)
		{
			closemusic(musicchoice);
			draw();
		}
	}
}

void game(int number)
{
	srand((unsigned)time(NULL));
	int musicchoice = rand() % 4 + 1;//���������������

	bushu = 0;                               //��¼����
	for (int a = 0; a < 15; a++)             //�������
	{
		for (int b = 0; b < 15; b++)
		{
			arr[a][b] = 0;
		}
	}

	computer = 1;

	initgraph(660, 660);                     //��������
	setbkcolor(LIGHTCYAN);
	setlinestyle(PS_SOLID, 2);
	cleardevice();
	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\ľ��.png");
	setlinecolor(BLACK);

	for (int x = 50; x <= 610; x += 40)      //��������
	{
		line(x, 50, x, 610);
	}
	for (int y = 50; y <= 610; y += 40)
	{
		line(50, y, 610, y);
	}

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	setfillcolor(CYAN);
	settextstyle(40, 0, L"�����п���");
	solidroundrect(290, 5, 370, 45, 5, 5);
	outtextxy(290, 5, L"Ͷ��");
	setbkmode(OPAQUE);

	HWND headline = GetHWnd();
	SetWindowText(headline, L"�������ս");
	settextstyle(40, 0, L"����");

	playmusic(musicchoice);

	if (number == 1) {                     //����

		settextcolor(BLACK);
		outtextxy(0, 0, L"�����=>");
		setfillcolor(BLACK);

		while (1) {
			if (MouseHit())
			{
				MOUSEMSG mes = GetMouseMsg();
				int Y = mes.y, X = mes.x;
				switch (mes.uMsg)
				{
				case WM_LBUTTONDOWN:

					if (X >= 40 && X <= 620 && Y >= 40 && Y <= 620 && cp[0](X) != 20 && cp[1](Y) != 20 && arr[cp[1](Y)][cp[0](X)] == 0)
					{      //�ж���������

						if (!(computer == 1)) {
							rp[2](cx, cy);
						}

						arr[cp[1](Y)][cp[0](X)] = 1;
						fillcircle(cp[0](X) * 40 + 50, cp[1](Y) * 40 + 50, 18);
						rp[0](cp[0](X), cp[1](Y));     //��ӡ��ɫ
						bushu++;

						Judge_victory(���, 1, arr, cp[0](X), cp[1](Y), musicchoice);  //�ж�ʤ��

						computerplay(1, X, Y, musicchoice);
						computer++;
						//���Կ�ʼ����

						settextcolor(BLACK);
						setbkcolor(LIGHTCYAN);
						outtextxy(0, 0, L"�����=>");
					}
					setfillcolor(BLACK);
					setlinecolor(BLACK);

					if (bushu == 24) {
						changemusic(musicchoice);
					}//���ֱ���
					if (bushu == 225)
					{
						closemusic(musicchoice);
						draw();
					}
					break;
				case WM_RBUTTONDOWN:
					if (X >= 290 && X <= 370 && Y >= 5 && Y <= 45)
					{
						closemusic(musicchoice);
						failure();
					}
					break;
				default:break;
				}
			}
		}
	}
	else                                     //����
	{
		computerplay(2, 0, 0, musicchoice);
		computer++;

		settextcolor(BLACK);
		settextstyle(40, 0, L"����");
		outtextxy(0, 0, L"�����=>");
		setfillcolor(WHITE);
		setlinecolor(WHITE);

		while (1) {
			if (MouseHit())
			{
				MOUSEMSG mes = GetMouseMsg();
				int Y = mes.y, X = mes.x;
				switch (mes.uMsg)
				{
				case WM_LBUTTONDOWN:

					if (X >= 40 && X <= 620 && Y >= 40 && Y <= 620 && cp[0](X) != 20 && cp[1](Y) != 20 && arr[cp[1](Y)][cp[0](X)] == 0)
					{      //�ж���������

						if (!(computer == 1)) {
							rp[1](cx, cy);
						}

						arr[cp[1](Y)][cp[0](X)] = 2;
						fillcircle(cp[0](X) * 40 + 50, cp[1](Y) * 40 + 50, 18);
						rp[0](cp[0](X), cp[1](Y));
						bushu++;

						Judge_victory(���, 2, arr, cp[0](X), cp[1](Y), musicchoice);  //�ж�ʤ��

						computerplay(2, X, Y, musicchoice);         //���Կ�ʼ����

						setbkcolor(LIGHTCYAN);
						settextcolor(BLACK);
						outtextxy(0, 0, L"�����=>");
					}
					setfillcolor(WHITE);
					setlinecolor(WHITE);
					if (bushu == 25) {//���ֱ���
						changemusic(musicchoice);
					}
					if (bushu == 225)
					{
						closemusic(musicchoice);
						draw();
					}
					break;
				case WM_RBUTTONDOWN:
					if (X >= 290 && X <= 370 && Y >= 5 && Y <= 45)
					{
						closemusic(musicchoice);
						failure();
					}
					break;
				default:break;
				}
			}
		}
	}
	system("pause");
}
