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

	initgraph(500, 500); //初始化

	HWND headline = GetHWnd();
	SetWindowText(headline, L"五子棋对战");

	setbkcolor(BLACK);
	cleardevice();                       //设置背景颜色
	setfillcolor(MAGENTA);

	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\欢迎界面.jpeg");

	settextcolor(WHITE);
	settextstyle(50, 0, L"楷体");        //设置字体颜色及样式

	fillroundrect(150, 200, 350, 300, 20, 20);
	fillroundrect(150, 350, 350, 450, 20, 20);//设置矩形边框

	outtextxy(75, 75, L"欢迎进入游戏！");
	setbkmode(TRANSPARENT);         //给字体设置透明背景

	settextstyle(50, 0, L"宋体");
	outtextxy(200, 225, L"进入");
	outtextxy(200, 375, L"退出");   //标注功能

	//这里闲着没事加了很多首音乐
	switch (WelcomeMusic)
	{
	case 1:
		mciSendString(L"open D:\\CloudMusic\\开庭1.mp3 alias 开庭1", NULL, 0, NULL);
		mciSendString(L"play 开庭1 repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"open D:\\CloudMusic\\开庭2.mp3 alias 开庭2", NULL, 0, NULL);
		mciSendString(L"play 开庭2 repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"open D:\\CloudMusic\\开庭3.mp3 alias 开庭3", NULL, 0, NULL);
		mciSendString(L"play 开庭3 repeat", NULL, 0, NULL);
		break;
	case 4:
		mciSendString(L"open D:\\CloudMusic\\开庭4.mp3 alias 开庭4", NULL, 0, NULL);
		mciSendString(L"play 开庭4 repeat", NULL, 0, NULL);
		break;
	default:
		printf("找不到此音乐！\a\n");
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
						mciSendString(L"close 开庭1", 0, 0, 0);
						break;
					case 2:
						mciSendString(L"close 开庭2", 0, 0, 0);
						break;
					case 3:
						mciSendString(L"close 开庭3", 0, 0, 0);
						break;
					case 4:
						mciSendString(L"close 开庭4", 0, 0, 0);
						break;
					default:
						printf("找不到此音乐！\a\n");
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
	SetWindowText(headline, L"游戏胜利");

	switch (WelcomeMusic)
	{
	case 1:
		mciSendString(L"open D:\\CloudMusic\\胜诉1.mp3 alias 胜诉1", NULL, 0, NULL);
		mciSendString(L"play 胜诉1 repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"open D:\\CloudMusic\\胜诉2.mp3 alias 胜诉2", NULL, 0, NULL);
		mciSendString(L"play 胜诉2 repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"open D:\\CloudMusic\\胜诉3.mp3 alias 胜诉3", NULL, 0, NULL);
		mciSendString(L"play 胜诉3 repeat", NULL, 0, NULL);
		break;
	case 4:
		mciSendString(L"open D:\\CloudMusic\\胜诉4.mp3 alias 胜诉4", NULL, 0, NULL);
		mciSendString(L"play 胜诉4 repeat", NULL, 0, NULL);
		break;
	default:
		printf("找不到此音乐！\a\n");
		exit(0);
		break;
	}

	settextcolor(LIGHTMAGENTA);
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\欢迎界面.jpeg");

	settextstyle(50, 0, L"楷体");
	outtextxy(75, 100, L"恭喜你取得胜利！");

	// 画彩虹(通过色相逐渐增加)
	float H = 0;
	float S = 1;
	float L = 0.5f;
	setlinestyle(PS_SOLID, 2);		// 设置线宽为 2
	for (int r = 400; r > 344; r--)
	{
		H += 5;
		setlinecolor(HSLtoRGB(H, S, L));
		circle(250, 400, r);
	}

	//设置两个功能区
	setfillcolor(LIGHTCYAN);
	solidroundrect(100, 250, 400, 350, 20, 20);
	solidroundrect(100, 400, 400, 500, 20, 20);

	settextstyle(50, 0, L"隶书");
	settextcolor(BLACK);
	outtextxy(150, 275, L"再来一局");
	outtextxy(150, 425, L"改天再玩");
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
						mciSendString(L"close 胜诉1", 0, 0, 0);
						break;
					case 2:
						mciSendString(L"close 胜诉2", 0, 0, 0);
						break;
					case 3:
						mciSendString(L"close 胜诉3", 0, 0, 0);
						break;
					case 4:
						mciSendString(L"close 胜诉4", 0, 0, 0);
						break;
					default:
						printf("找不到此音乐！\a\n");
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
	SetWindowText(headline, L"游戏失败");

	switch (WelcomeMusic)
	{
	case 1:
		mciSendString(L"open D:\\CloudMusic\\被遗忘的传说.mp3 alias 被遗忘的传说", NULL, 0, NULL);
		mciSendString(L"play 被遗忘的传说 repeat", NULL, 0, NULL);
		break;
	case 2:
		mciSendString(L"open D:\\CloudMusic\\DL6.mp3 alias DL6", NULL, 0, NULL);
		mciSendString(L"play DL6 repeat", NULL, 0, NULL);
		break;
	case 3:
		mciSendString(L"open D:\\CloudMusic\\真相的苦涩味.mp3 alias 真相的苦涩味", NULL, 0, NULL);
		mciSendString(L"play 真相的苦涩味 repeat", NULL, 0, NULL);
		break;
	default:
		printf("找不到此音乐！\a\n");
		exit(0);
	}
	

	settextcolor(DARKGRAY);
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\欢迎界面.jpeg");

	settextstyle(50, 0, L"楷体");
	outtextxy(75, 100, L"很遗憾你失败了！");

	//设置两个功能区
	setfillcolor(LIGHTGRAY);
	solidroundrect(100, 250, 400, 350, 20, 20);
	solidroundrect(100, 400, 400, 500, 20, 20);

	settextstyle(50, 0, L"隶书");
	settextcolor(BLACK);
	outtextxy(150, 275, L"不服再战");
	outtextxy(150, 425, L"我放弃了");
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
						mciSendString(L"close 被遗忘的传说", 0, 0, 0);
						break;
					case 2:
						mciSendString(L"close DL6", 0, 0, 0);
						break;
					case 3:
						mciSendString(L"close 真相的苦涩味", 0, 0, 0);
						break;
					default:
						printf("找不到此音乐！\a\n");
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
	SetWindowText(headline, L"请选择模式");

	mciSendString(L"open D:\\CloudMusic\\捜査opening1.mp3 alias 助手", 0, 0, 0);
	mciSendString(L"play 助手 repeat", 0, 0, 0);

	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\欢迎界面.jpeg");
	settextcolor(BLACK);
	setbkcolor(LIGHTMAGENTA);

	settextstyle(80, 0, L"隶书");
	outtextxy(0, 50, L"请选择=>");

	setlinecolor(LIGHTBLUE);
	setfillcolor(LIGHTCYAN);
	fillroundrect(50, 300, 200, 400, 30, 30);
	fillroundrect(300, 300, 450, 400, 30, 30);

	setbkmode(TRANSPARENT);         //给字体设置透明背景
	settextstyle(50, 0, L"华文行楷");
	outtextxy(75, 325, L"先手");
	outtextxy(325, 325, L"后手");

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
					mciSendString(L"close 助手", 0, 0, 0);
					game(1);
				}
				else if (mes.x > 300 && mes.x < 450 && mes.y>300 && mes.y < 400)
				{
					closegraph();
					mciSendString(L"close 助手", 0, 0, 0);
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
	SetWindowText(headline, L"平局结束");

	mciSendString(L"open D:\\CloudMusic\\开庭2.mp3 alias 开庭2", NULL, 0, NULL);
	mciSendString(L"play 开庭2 repeat", NULL, 0, NULL);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(NULL, L"C:\\Users\\ASUS\\Desktop\\欢迎界面.jpeg");

	settextstyle(60, 0, L"楷体");
	outtextxy(125, 100, L"达成平局！");

	//设置两个功能区
	setfillcolor(LIGHTBLUE);
	solidroundrect(100, 250, 400, 350, 20, 20);
	solidroundrect(100, 400, 400, 500, 20, 20);

	settextstyle(50, 0, L"隶书");
	settextcolor(BLACK);
	outtextxy(150, 275, L"再来一次");
	outtextxy(150, 425, L"想要退出");
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
					mciSendString(L"close 开庭2", 0, 0, 0);
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
