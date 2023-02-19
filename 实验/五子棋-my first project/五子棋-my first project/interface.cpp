#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include"interface.h"
#include"game.h"

int WelcomeMusic = 0;
int VictoryMusic = 0;
int FailureMusic = 0;

void welcome()
{
	srand((unsigned)time(NULL));
	WelcomeMusic = rand() % 4 + 1;

	initgraph(500, 500); //��ʼ��

	HWND headline = GetHWnd();
	SetWindowText(headline, L"�������ս");

	setbkcolor(BLACK);
	cleardevice();                       //���ñ�����ɫ
	setfillcolor(MAGENTA);

	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\��ӭ����.jpeg");

	settextcolor(WHITE);
	settextstyle(50, 0, L"����");        //����������ɫ����ʽ

	fillroundrect(150, 200, 350, 300, 20, 20);
	fillroundrect(150, 350, 350, 450, 20, 20);//���þ��α߿�

	outtextxy(75, 75, L"��ӭ������Ϸ��");
	setbkmode(TRANSPARENT);         //����������͸������

	settextstyle(50, 0, L"����");
	outtextxy(200, 225, L"����");
	outtextxy(200, 375, L"�˳�");   //��ע����

	//��������û�¼��˺ܶ�������
	switch (WelcomeMusic)
	{
	case 1:
		mciSendString(L"open D:\\CloudMusic\\��ͥ1.mp3 alias ��ͥ1", NULL, 0, NULL);
		mciSendString(L"play ��ͥ1 repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"open D:\\CloudMusic\\��ͥ2.mp3 alias ��ͥ2", NULL, 0, NULL);
		mciSendString(L"play ��ͥ2 repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"open D:\\CloudMusic\\��ͥ3.mp3 alias ��ͥ3", NULL, 0, NULL);
		mciSendString(L"play ��ͥ3 repeat", NULL, 0, NULL);
		break;
	case 4:
		mciSendString(L"open D:\\CloudMusic\\��ͥ4.mp3 alias ��ͥ4", NULL, 0, NULL);
		mciSendString(L"play ��ͥ4 repeat", NULL, 0, NULL);
		break;
	default:
		printf("�Ҳ��������֣�\a\n");
		exit(0);
		break;
	}
	

	while (1) {
		if (MouseHit())
		{
			MOUSEMSG mes = GetMouseMsg();

			switch (mes.uMsg)
			{
			case WM_LBUTTONDOWN:

				if (mes.x > 150 && mes.x < 350 && mes.y>200 && mes.y < 300)
				{
					closegraph();
					switch (WelcomeMusic)
					{
					case 1:
						mciSendString(L"close ��ͥ1", 0, 0, 0);
						break;
					case 2:
						mciSendString(L"close ��ͥ2", 0, 0, 0);
						break;
					case 3:
						mciSendString(L"close ��ͥ3", 0, 0, 0);
						break;
					case 4:
						mciSendString(L"close ��ͥ4", 0, 0, 0);
						break;
					default:
						printf("�Ҳ��������֣�\a\n");
						exit(0);
						break;
					}
					choice();
				}
				else if (mes.x > 150 && mes.x < 350 && mes.y>350 && mes.y < 450)
				{
					exit(0);
				}
				else { ; }
				break;
			case WM_RBUTTONDOWN:
				break;
			default:break;
			}
		}
	}
	
}

void victory()
{
	srand((unsigned)time(NULL));
	VictoryMusic = rand() % 4 + 1;

	closegraph();
	initgraph(500, 500);

	HWND headline = GetHWnd();
	SetWindowText(headline, L"��Ϸʤ��");

	switch (WelcomeMusic)
	{
	case 1:
		mciSendString(L"open D:\\CloudMusic\\ʤ��1.mp3 alias ʤ��1", NULL, 0, NULL);
		mciSendString(L"play ʤ��1 repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"open D:\\CloudMusic\\ʤ��2.mp3 alias ʤ��2", NULL, 0, NULL);
		mciSendString(L"play ʤ��2 repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"open D:\\CloudMusic\\ʤ��3.mp3 alias ʤ��3", NULL, 0, NULL);
		mciSendString(L"play ʤ��3 repeat", NULL, 0, NULL);
		break;
	case 4:
		mciSendString(L"open D:\\CloudMusic\\ʤ��4.mp3 alias ʤ��4", NULL, 0, NULL);
		mciSendString(L"play ʤ��4 repeat", NULL, 0, NULL);
		break;
	default:
		printf("�Ҳ��������֣�\a\n");
		exit(0);
		break;
	}

	settextcolor(LIGHTMAGENTA);
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\��ӭ����.jpeg");

	settextstyle(50, 0, L"����");
	outtextxy(75, 100, L"��ϲ��ȡ��ʤ����");

	// ���ʺ�(ͨ��ɫ��������)
	float H = 0;
	float S = 1;
	float L = 0.5f;
	setlinestyle(PS_SOLID, 2);		// �����߿�Ϊ 2
	for (int r = 400; r > 344; r--)
	{
		H += 5;
		setlinecolor(HSLtoRGB(H, S, L));
		circle(250, 400, r);
	}

	//��������������
	setfillcolor(LIGHTCYAN);
	solidroundrect(100, 250, 400, 350, 20, 20);
	solidroundrect(100, 400, 400, 500, 20, 20);

	settextstyle(50, 0, L"����");
	settextcolor(BLACK);
	outtextxy(150, 275, L"����һ��");
	outtextxy(150, 425, L"��������");
	while (1) {
		if (MouseHit())
		{
			MOUSEMSG mes = GetMouseMsg();

			switch (mes.uMsg)
			{
			case WM_LBUTTONDOWN:

				if (mes.x > 100 && mes.x < 400 && mes.y>250 && mes.y < 350)
				{
					closegraph();
					switch (WelcomeMusic)
					{
					case 1:
						mciSendString(L"close ʤ��1", 0, 0, 0);
						break;
					case 2:
						mciSendString(L"close ʤ��2", 0, 0, 0);
						break;
					case 3:
						mciSendString(L"close ʤ��3", 0, 0, 0);
						break;
					case 4:
						mciSendString(L"close ʤ��4", 0, 0, 0);
						break;
					default:
						printf("�Ҳ��������֣�\a\n");
						exit(0);
						break;
					}
					choice();
				}
				else if (mes.x > 100 && mes.x < 400 && mes.y>400 && mes.y < 500)
				{
					exit(0);
				}
				else { ; }
				break;
			case WM_RBUTTONDOWN:
				break;
			default:break;
			}
		}
	}
}

void failure()
{
	srand((unsigned)time(NULL));
	FailureMusic = rand() % 3 + 1;

	closegraph();
	initgraph(500, 500);

	HWND headline = GetHWnd();
	SetWindowText(headline, L"��Ϸʧ��");

	switch (WelcomeMusic)
	{
	case 1:
		mciSendString(L"open D:\\CloudMusic\\�������Ĵ�˵.mp3 alias �������Ĵ�˵", NULL, 0, NULL);
		mciSendString(L"play �������Ĵ�˵ repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"open D:\\CloudMusic\\DL6.mp3 alias DL6", NULL, 0, NULL);
		mciSendString(L"play DL6 repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"open D:\\CloudMusic\\����Ŀ�ɬζ.mp3 alias ����Ŀ�ɬζ", NULL, 0, NULL);
		mciSendString(L"play ����Ŀ�ɬζ repeat", NULL, 0, NULL);
		break;
	default:
		printf("�Ҳ��������֣�\a\n");
		exit(0);
	}
	

	settextcolor(DARKGRAY);
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\��ӭ����.jpeg");

	settextstyle(50, 0, L"����");
	outtextxy(75, 100, L"���ź���ʧ���ˣ�");

	//��������������
	setfillcolor(LIGHTGRAY);
	solidroundrect(100, 250, 400, 350, 20, 20);
	solidroundrect(100, 400, 400, 500, 20, 20);

	settextstyle(50, 0, L"����");
	settextcolor(BLACK);
	outtextxy(150, 275, L"������ս");
	outtextxy(150, 425, L"�ҷ�����");
	while (1) {
		if (MouseHit())
		{
			MOUSEMSG mes = GetMouseMsg();

			switch (mes.uMsg)
			{
			case WM_LBUTTONDOWN:

				if (mes.x > 100 && mes.x < 400 && mes.y>250 && mes.y < 350)
				{
					closegraph();
					switch (WelcomeMusic)
					{
					case 1:
						mciSendString(L"close �������Ĵ�˵", 0, 0, 0);
						break;
					case 2:
						mciSendString(L"close DL6", 0, 0, 0);
						break;
					case 3:
						mciSendString(L"close ����Ŀ�ɬζ", 0, 0, 0);
						break;
					default:
						printf("�Ҳ��������֣�\a\n");
						exit(0);
					}
					choice();
				}
				else if (mes.x > 100 && mes.x < 400 && mes.y>400 && mes.y < 500)
				{
					exit(0);
				}
				else { ; }
				break;
			case WM_RBUTTONDOWN:
				break;
			default:break;
			}
		}
	}
}

void choice()
{
	initgraph(500, 500);

	HWND headline = GetHWnd();
	SetWindowText(headline, L"��ѡ��ģʽ");

	mciSendString(L"open D:\\CloudMusic\\�Ȗ�opening1.mp3 alias ����", 0, 0, 0);
	mciSendString(L"play ���� repeat", 0, 0, 0);

	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\��ӭ����.jpeg");
	settextcolor(BLACK);
	setbkcolor(LIGHTMAGENTA);

	settextstyle(80, 0, L"����");
	outtextxy(0, 50, L"��ѡ��=>");

	setlinecolor(LIGHTBLUE);
	setfillcolor(LIGHTCYAN);
	fillroundrect(50, 300, 200, 400, 30, 30);
	fillroundrect(300, 300, 450, 400, 30, 30);

	setbkmode(TRANSPARENT);         //����������͸������
	settextstyle(50, 0, L"�����п�");
	outtextxy(75, 325, L"����");
	outtextxy(325, 325, L"����");

	while (1) {
		if (MouseHit())
		{
			MOUSEMSG mes = GetMouseMsg();

			switch (mes.uMsg)
			{
			case WM_LBUTTONDOWN:

				if (mes.x > 50 && mes.x < 200 && mes.y>300 && mes.y < 400)
				{
					closegraph();
					mciSendString(L"close ����", 0, 0, 0);
					game(1);
				}
				else if (mes.x > 300 && mes.x < 450 && mes.y>300 && mes.y < 400)
				{
					closegraph();
					mciSendString(L"close ����", 0, 0, 0);
					game(2);
				}
				else { ; }
				break;
			case WM_RBUTTONDOWN:
				break;
			default:break;
			}
		}
	}
}

void draw()
{
	initgraph(500, 500);

	HWND headline = GetHWnd();
	SetWindowText(headline, L"ƽ�ֽ���");

	mciSendString(L"open D:\\CloudMusic\\��ͥ2.mp3 alias ��ͥ2", NULL, 0, NULL);
	mciSendString(L"play ��ͥ2 repeat", NULL, 0, NULL);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\��ӭ����.jpeg");

	settextstyle(60, 0, L"����");
	outtextxy(125, 100, L"���ƽ�֣�");

	//��������������
	setfillcolor(LIGHTBLUE);
	solidroundrect(100, 250, 400, 350, 20, 20);
	solidroundrect(100, 400, 400, 500, 20, 20);

	settextstyle(50, 0, L"����");
	settextcolor(BLACK);
	outtextxy(150, 275, L"����һ��");
	outtextxy(150, 425, L"��Ҫ�˳�");
	while (1) {
		if (MouseHit())
		{
			MOUSEMSG mes = GetMouseMsg();

			switch (mes.uMsg)
			{
			case WM_LBUTTONDOWN:

				if (mes.x > 100 && mes.x < 400 && mes.y>250 && mes.y < 350)
				{
					closegraph();
					mciSendString(L"close ��ͥ2", 0, 0, 0);
					choice();
				}
				else if (mes.x > 100 && mes.x < 400 && mes.y>400 && mes.y < 500)
				{
					exit(0);
				}
				else { ; }
				break;
			case WM_RBUTTONDOWN:
				break;
			default:break;
			}
		}
	}
}
