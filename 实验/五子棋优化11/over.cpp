#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include"creatmap.h"
#include"begin.h"
#include"chessdata.h"
#include<stdlib.h>
extern int turn;
extern FILE* plog;
extern struct chessdata game;
IMAGE exit1;
IMAGE reset;
extern char name1[30];

void over(int i)
{
	fopen_s(&plog, "战绩.txt", "a");
	rewind(plog);
	fprintf(plog, "%s\n", name1);

	/*		fclose(plog);*/
	//fopen_s(&plog, "战绩.txt", "a");
	fprintf(plog, "%d\n",turn);
	initgraph(450,800);
	setbkcolor(RGB(250, 200, 177));
	cleardevice();
	settextstyle(50, 24, "宋体");
	settextcolor(RED);
	if (i == 1)
	{
		outtextxy(100, 50, "是平局欸");
		fprintf(plog, "%d\n",1);
	}
	else if (i == 2)
	{
		outtextxy(100, 50, "玩家获胜");
		fprintf(plog, "%d\n", 2);
	}
	else if (i == 3)
	{
		outtextxy(100, 50, "AI获胜!");
		fprintf(plog, "%d\n", 3);
	}
	fflush(plog);
	rewind(plog);
	fclose(plog);


	FILE* plog2;

	fopen_s(&plog2, "战绩.txt", "rb");
	int score_temp=0,ifwin_temp=0,text_line=0,time1;
	char name_temp[30]; char ch,test1;

	rewind(plog2);
	while (1)
	{
		test1 = fgetc(plog2);
		if (test1 == '\n')
		{
			text_line += 1;
		}
		else if (test1 == EOF)
			break;
	}
	rewind(plog2);
	time1 = (text_line + 1) / 3;

	char text_tem[30];

	for (int k = 0; k < 4; k++,time1--)
	{

		for (int m=1;m<time1;m++)
		{
			fgets(text_tem, 30, plog2);
			fgets(text_tem, 30, plog2);
			fgets(text_tem, 30, plog2);
		}
	
		ch = fgetc(plog2);
		if (ch == EOF)
		{
			break;
		}
		else
		{
			fseek(plog2, -1, SEEK_CUR);
			fscanf_s(plog2, "%s", name_temp,30);
			fscanf_s(plog2, "%d", &score_temp);
			fscanf_s(plog2, "%d", &ifwin_temp);
			rewind(plog2);
			settextstyle(25,12, "宋体");
			settextcolor(RED);
			if (ifwin_temp == 2)
				score_temp = 100;
			char num_s[6]; sprintf(num_s, "%d", score_temp);
		
			outtextxy(50,150, "棋手          得分     输赢  \n");
			outtextxy(50, 200+k*50,name_temp);
			outtextxy(240, 200 + k * 50, num_s);
			if (ifwin_temp == 1)
				outtextxy(350, 200 + k * 50, "和");
			else if (ifwin_temp == 2)
				outtextxy(350, 200 + k * 50, "赢");
			else if(ifwin_temp == 3)
				outtextxy(350, 200 + k * 50, "输");
		}
	
	}
	fclose(plog2);
	loadimage(&exit1, "wuzi/exit.jpg",200, 100);
	putimage(100,600, &exit1);
	loadimage(&reset, "wuzi/restart.png", 200, 100);
	putimage(100, 450, &reset);

	MOUSEMSG msg2;
	while (1)
	{
		msg2 = GetMouseMsg();
		if (msg2.uMsg == WM_LBUTTONDOWN && msg2.x > 100 && msg2.x < 300 && msg2.y>450 && msg2.y < 550)
		{
			init();
			begin();
		}
		else if (msg2.uMsg == WM_LBUTTONDOWN && msg2.x > 100 && msg2.x < 300 && msg2.y>600 && msg2.y <700)
		{
			closegraph();
			printf("\n\n欢迎下次再来\n祝天天开心！万事如意！*(≧∇≦)ﾉ\n\n");
			exit(0);
		}
	}

}