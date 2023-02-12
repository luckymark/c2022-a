#include<windows.h>
#include<easyx.h>
#include<stdio.h>
#include"creatmap.h"
#include"begin.h"
#include"chessdata.h"
#include"trasprent_img.h"
#pragma comment(lib,"winmm.lib")
#define _CRT_SECURE_NO_WARNINGS

IMAGE renew;
IMAGE read;
FILE* plog;
FILE* precord;
extern IMAGE chess_black;
extern IMAGE chess_white;
extern IMAGE b_mask;
extern IMAGE w_mask;
extern struct chessdata game;
char name1[30];
extern int turn;

int main(void) 
{
	initgraph(500, 550);
	setbkcolor(RGB(250, 200, 177));
	cleardevice();
	loadimage(&renew, "wuzi/new.jpg", 400, 200);
	putimage(50, 50, &renew);
	loadimage(&read, "wuzi/read.jpg", 400, 200);
	putimage(50, 300, &read);

	mciSendString("open wuzi/bgm.mp3", NULL, 0, NULL);
	mciSendString("play wuzi/bgm.mp3 repeat", NULL, 0, NULL);

	MOUSEMSG msg1;
	while (1)
	{

		msg1 = GetMouseMsg();
		if (msg1.uMsg == WM_LBUTTONDOWN && msg1.x > 50 && msg1.x < 450 && msg1.y>50 && msg1.y < 250)
		{
			printf("先生，早上好！\n对局结束后将会显示您的当局得分和往期得分，\n");
			printf("所以为您自己或者为这局棋想一个有意思的名字吧\n");
			printf("请输入：");
			scanf_s("%s", name1,30);
			printf("真是个优雅的名字呢，想必阁下棋术一定了得\n");

			Sleep(2000);
			init();

			begin();

			break;

		}
		else if (msg1.uMsg == WM_LBUTTONDOWN && msg1.x > 50 && msg1.x < 450 && msg1.y>300 && msg1.y < 500)
		{
			init();
			fopen_s(&precord, "存档.txt", "rb");
			fscanf_s(precord, "%s", name1,30);
			fscanf_s(precord, "%d", &turn);
			for (int a = 0; a < 25; a++)
			{
				for (int b = 0; b < 25; b++)
				{
					fscanf_s(precord, "%d", &game.chessmap[a][b]);
					if (game.chessmap[a][b] == -1)
					{
						int x = margin + (b - 5) * node_size - node_size / 2;
						int y = margin + (a - 5) * node_size - node_size / 2;
						puttrimage(x, y, &w_mask, &chess_white);
					}
					else if(game.chessmap[a][b] ==1)
					{
						int x = margin + (b - 5) * node_size - node_size / 2;
						int y = margin + (a - 5) * node_size - node_size / 2;
						puttrimage(x, y, &b_mask, &chess_black);
					}
				}
			}
			fclose(precord);
			//fopen_s(&plog, "战绩.txt", "a");
			//rewind(plog);
			//char ac[30];
			//fscanf_s(plog,"%s",ac);
			begin();
		}
	}

		system("pause");

		return 0;


}	

		
			
