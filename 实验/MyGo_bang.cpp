#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include<mmsystem.h>
#include<easyx.h>
#include<iostream>
#include<stdlib.h>

using namespace std;
#define DEFINE 100   // E=防守/攻击
#define KILL 10000
#define VALUE 10         //位置初始分以及倍率
#define MIN 5
#define MAX 20
#define MAXMAX 999999999999999999
long double Alpha = -MAXMAX;
long double Beta =MAXMAX;
int ii = 0, jj = 0, xx = 0, yy = 0;    //记录上一步棋位置
int num = 0;   
enum Winner{draw=1,hum,com};
Winner winner;
void board();
void regret(struct point p[25][25]);		
void play(struct point p[25][25]);  	
void gameOver(int x);	
void p_assess(struct point p[25][25]);     //某点价值分评定
double assess(struct point p[25][25]);     //局面优势评估

double deduction(struct point p[25][25], int depth, long double a, long double b);
int computer(struct point p[25][25]);	

int result(struct point p[25][25]);     //结果
void initialize(struct point p[25][25]);  
void drop(struct point p[25][25], int x, int y);    //下棋
bool hasNieghbor(struct point p[25][25], int m, int n);

struct point {
	int state;          //  玩家-1,   空位置0,   电脑1
	long double value;        //该点价值分
	long double n_value;        //总优势分
};



int main()
{
	point p[25][25];       //  15*15边界为5
	initialize(p);
	play(p);
	return 0;
}


//初始化
void initialize(struct point p[25][25])
{
	int i, j;
	num = 0;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 25; j++)
		{
			p[i][j].state = 0;   //为空
			p[i][j].value = 0;
			p[i][j].n_value = 0;
		}
	}
}
//胜负代数返回
int result(struct point p[25][25])
{
	int i, j, k = 0, x = 0, y = 0, b = 0, q = 0, winner = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)
			{
				k++;
				if (k == 0)
				{
					winner= draw;//平局
				}
			}
			if (p[i][j].state)
			{
				for (x = -2; p[i][j].state == p[i][j + x].state && x < 4; x++)     //横
				{
				}
				for (y = -2; p[i][j].state == p[i + y][j].state && y < 4; y++)      //纵
				{
				}
				for (b = -2; p[i][j].state == p[i + b][j + b].state && b < 4; b++)    //斜下
				{
				}
				for (q = -2; p[i][j].state == p[i - q][j + q].state && q < 4; q++)    //斜上
				{
				}
				if (x == 3 || y == 3 || b == 3 || q == 3)
				{
					if (p[i][j].state == 1)
					{
						winner = com; //电脑赢
					}
					if (p[i][j].state == -1)
					{
						winner = hum; //玩家赢
					}
				}
			}
		}
	}
	return winner;  //e=0默认未结束
}

void board()
{
	initgraph(950, 800);
	setbkcolor(RGB(209, 209, 209));
	cleardevice();
	for (int i = 50; i <= 750; i += 50)
	{
		line(i, 50, i, 750);
		line(50, i, 750, i);
	}

	setlinecolor(BLACK);
	settextstyle(40, 0, "宋体");
	outtextxy(800, 200, "悔 棋");
	outtextxy(800, 300, "重 来");
	outtextxy(800, 400, "后 手");
	outtextxy(800, 500, "退 出");
	settextcolor(BLACK);
	settextstyle(15, 0, "宋体");
}

void drop(struct point p[25][25], int x, int y)
{
	setfillcolor(WHITE); //填充颜色
	fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);//画圆，下这一步
	xx = x;
	yy = y;    //为悔棋坐标做记录
	p[x][y].state = 1;     //修改状态
}

void regret(struct point p[25][25])
{
	board();
	setrop2(R2_COPYPEN);  //设置绘制颜色
	setcolor(WHITE);
	p[ii][jj].state = 0;  //将上一步棋清空
	p[xx][yy].state = 0;
	for (int i = MIN; i < MAX; i++) {        //重新绘制棋盘
		for (int j = MIN; j < MAX; j++) {
			if (p[i][j].state == -1) {
				setfillcolor(BLACK);
				fillcircle((i + 1 - MIN) * 50, (j + 1 - MIN) * 50, 20);
			}
			if (p[i][j].state == 1) {
				setfillcolor(WHITE);
				fillcircle((i + 1 - MIN) * 50, (j + 1 - MIN) * 50, 20);
			}
		}
	}
}

void play(struct point p[25][25])
{
	MOUSEMSG m;
	int  x, y, i, j;
	board();
	setlinecolor(WHITE);

	while (1)
	{
		m = GetMouseMsg();
		x = m.x % 50;
		y = m.y % 50;
		setrop2(R2_COPYPEN);
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x <= 900 && m.y < 250 && m.x >= 800 && m.y > 200)  //悔棋
			{
				regret(p);
				continue;
			}
			if (m.x <= 900 && m.y < 350 && m.x >= 800 && m.y > 300)	//重开
			{
				initialize(p);   //初始化
				play(p);
			}
			if (m.x <= 900 && m.y < 450 && m.x >= 800 && m.y > 400)  //后手
			{
				if (num < 1)
				{
					computer(p);   //电脑执棋
					num++;
				}
			}
			if (m.x <= 900 && m.y < 550 && m.x >= 800 && m.y > 500)  //退出
			{
				closegraph(); 
				exit(0);    
			}

			if (x >= 25)     //玩家执棋
				m.x = m.x - x + 50;
			else
				m.x = m.x - x;
			if (y >= 25)
				m.y = m.y - y + 50;
			else
				m.y = m.y - y;
			i = m.x / 50 - 1 + MIN; 
			j = m.y / 50 - 1 + MIN;
			if (i < 20 && j < 20)
			{
				if (p[i][j].state == -1)
					break;
				if (m.x <= 750 && m.y <= 750 && m.x >= 50 && m.y >= 50)
				{
					setfillcolor(BLACK);
					fillcircle(m.x, m.y, 20);
					ii = i;    //为悔棋坐标做记录
					jj = j;
					p[i][j].state = -1;//修改该位置的状态
				}
				if (result(p) != 0)//结束判断
				{
					Sleep(1000);
					gameOver(result(p));
				}
				computer(p);   
				if (result(p) != 0)
				{
					gameOver(result(p));
				}
				num++;    //对弈次数
			}
		}
	}
}

void gameOver(int winner)
{
	point pp[25][25];      	
	initialize(pp);      //初始化
	initgraph(400, 400);
	cleardevice();     //使用当前背景色清空绘图设备
	settextstyle(50, 24, "宋体");
	settextcolor(RED);    //字体颜色
	if (winner == draw)
	{
		outtextxy(100, 50, "平局");
	}
	else if (winner == hum)
	{
		outtextxy(100, 50, "玩家获胜");
	}
	else if (winner == com)
	{
		outtextxy(100, 50, "电脑获胜");
	}
	settextcolor(WHITE);
	outtextxy(50, 200, "返回游戏界面");
	outtextxy(80, 300, " 结束游戏");

	while (true)
	{
		MOUSEMSG n;
		n = GetMouseMsg();
		switch (n.uMsg) {
		case WM_LBUTTONDOWN:
			if (n.x <= 350 && n.x >= 50 && n.y <= 250 && n.y >= 200)
				play(pp);   
			if (n.x <= 300 && n.x >= 80 && n.y <= 350 && n.y >= 300)
			{
				closegraph(); 
				exit(0);  
			}
		}
	}
}

bool hasNieghbor(struct point p[25][25], int m, int n)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (p[i + m][j + n].state != 0)
			{
				return true;
			}
		}
	}
	return false;
}

//局面优势评估
double assess(struct point p[25][25])
{
	int i, j;
	p_assess(p);     //某点价值
	long double s_value = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			s_value += p[i][j].value;//棋盘总优势分为所有点分数的和
		}
	}
	return s_value;
}


void p_assess(struct point p[25][25])
{
	int i, j, k, m, n, x, y;
	for (i = MIN; i < MAX; i++)     //可改进为米字刷新
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)
			{
				p[i][j].value = 0;      //空位价值为零 
			}
			else     //不为空
			{                                 //8个方向每个价值为10
				long double v1 = VALUE, v2 = VALUE, v3 = VALUE, v4 = VALUE, v5 = VALUE, v6 = VALUE, v7 = VALUE, v8 = VALUE;
				//****************************************************************************
				for (x = 0, n = j; p[i][j].state != -p[i][n + 1].state && n + 1 < 20 && x < 4; x++, n++)       //右
				{
				}
				if (x < 4)
				{
					v1 = 0;    //被挡住为0
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n + 1].state && k < 5; k++, n++)       //右
					{
						v1 *= VALUE;     //连续分数翻倍
					}
				}
				for (y = 0, n = j; p[i][j].state != -p[i][n - 1].state && n - 1 > 4 && y < 4; y++, n--)      //左
				{
				}
				if (y < 4)
				{
					v2 = 0;    //被挡住为0
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n - 1].state && k < 5; k++, n--)      //左
					{
						v2 *= VALUE;     //连续分数翻倍
					}
				}
				//******************************    以下同上   ***************************************
				for (x = 0, n = i; p[i][j].state != -p[n + 1][j].state && n + 1 < 20 && x < 5; x++, n++)       //上
				{
				}
				if (x < 4)
				{
					v3 = 0;    //被挡住为0
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n + 1][j].state && k < 5; k++, n++)       //上
					{
						v3 *= VALUE;   //连续分数翻倍
					}
				}
				for (y = 0, n = i; p[i][j].state != -p[n - 1][j].state && n - 1 > 4 && y < 5; y++, n--)       //下
				{
				}
				if (y < 4)
				{
					v4 = 0;   //被挡住为0
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n - 1][j].state && k < 5; k++, n--)       //下
					{
						v4 *= VALUE;   //连续分数翻倍
					}
				}
				//**********************************   以下同上    **************************************
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n + 1].state && n + 1 < 20 && m - 1 > 4 && x < 5; x++, m--, n++) //右上
				{
				}
				if (x < 4)
				{
					v5 = 0;   //被挡住为0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n + 1].state && k < 5; k++, m--, n++)       //右上
					{
						v5 *= VALUE;    //连续分数翻倍
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n - 1].state && m + 1 < 20 && n - 1 > 4 && y < 5; y++, m++, n--) //左下
				{
				}
				if (y < 4)
				{
					v6 = 0;    //被挡住为0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n - 1].state && k < 5; k++, m++, n--)       //左下
					{
						v6 *= VALUE;    //连续分数翻倍
					}
				}
				//***********************************    以下同上    **************************************
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n - 1].state && n - 1 > 4 && m - 1 > 4 && x < 5; x++, m--, n--)  //左上
				{
				}
				if (x < 4)
				{
					v7 = 0;    //被挡住为0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n - 1].state && k < 5; k++, m--, n--)       //左上
					{
						v7 *= VALUE;    //连续分数翻倍
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n + 1].state && n + 1 < 20 && m + 1 < 20 && y < 5; y++, m++, n++) //右下
				{
				}
				if (y < 4)
				{
					v8 = 0;    //被挡住为0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n + 1].state && k < 5; k++, m++, n++)       //右下
					{
						v8 *= VALUE;     //连续分数翻倍
					}
				}
				//********************************************************************************    //100000?杀
				p[i][j].value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));    //加上距离中心优势分
				if (p[i][j].state == -1)    //玩家棋子为负分
				{
					p[i][j].value = -p[i][j].value * DEFINE;       //E为偏向防守程度
				}
			}
		}
	}
}
//递归推演 
double deduction(struct point p[25][25], /*int sex,*/ int depth, long double a, long double b)
{
	int m, n, i, j, t = 0, br = 0;
	long double value = 0;
	if (depth == 0 || result(p) != 0)   //达到深度或棋局结束
	{
		return assess(p);       //递归出口，返回分数
	}
	else if (/*sex */depth % 2 == 1)    
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) { 
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0)   //为空
				{
		
					if (num<80&&!hasNieghbor(p, m, n))
					{
						value = Beta;
					}
					else {
						p[m][n].state = -1;   
						value = deduction(p,  depth - 1, a, b);
						p[m][n].state = 0;      
					}
					if (value < b)    
					{
						b = value;
					}
					if (b <= a)
					{
						br = 1;
						break;    
						
					}
				}
			}
		}
		return b; //返回分数
	}
	else if (depth % 2 == 0)     //电脑层
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) {   
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0)     //为空
				{

					if (num < 80 && !hasNieghbor(p, m, n))
					{
						value = Alpha;
					}
					else {
						p[m][n].state = 1;     //棋下在这个地方
						value = deduction(p,/* sex + 1,*/ depth - 1, a, b);
						p[m][n].state = 0;     //撤回
					}
					if (value > a)    //找最大值
					{
						a = value;
					}
					if (b <= a)
					{
						br = 1;
						break;    
						
					}
				}
			}
		}
		return a;//返回分数
	}
	return 0;
}
//电脑执棋
int computer(struct point p[25][25])
{
	int i, j, x = 12, y = 12, m, n, t = 0;
	long double v = -MAXMAX;    
	for (i = MIN; i < MAX; i++)       
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)     
			{
			
				if (hasNieghbor(p,i,j) )  //不偏僻
				{
					p[i][j].state = 1;    //模拟落子
					if (result(p) == com)           //改枚举增加可读性
					{
						drop(p, i, j);    
						return 0;
					}
					else if ((p[i][j].n_value = deduction(p, 2, Alpha, Beta)) > KILL)       //迭代加深
					{
						drop(p, i, j);
						return 0;
					}  
					p[i][j].n_value = deduction(p, 4, Alpha, Beta);
					  p[i][j].state = 0;   
					if (p[i][j].n_value > v)
					{
						v = p[i][j].n_value;    
						x = i;
						y = j;     
					}					
				}
			}
		}
	}
	drop(p, x, y);    //下棋
	return 0;
}

