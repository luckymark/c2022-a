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
#define DEFINE 100   // E=����/����
#define KILL 10000
#define VALUE 10         //λ�ó�ʼ���Լ�����
#define MIN 5
#define MAX 20
#define MAXMAX 999999999999999999
long double Alpha = -MAXMAX;
long double Beta =MAXMAX;
int ii = 0, jj = 0, xx = 0, yy = 0;    //��¼��һ����λ��
int num = 0;   
enum Winner{draw=1,hum,com};
Winner winner;
void board();
void regret(struct point p[25][25]);		
void play(struct point p[25][25]);  	
void gameOver(int x);	
void p_assess(struct point p[25][25]);     //ĳ���ֵ������
double assess(struct point p[25][25]);     //������������

double deduction(struct point p[25][25], int depth, long double a, long double b);
int computer(struct point p[25][25]);	

int result(struct point p[25][25]);     //���
void initialize(struct point p[25][25]);  
void drop(struct point p[25][25], int x, int y);    //����
bool hasNieghbor(struct point p[25][25], int m, int n);

struct point {
	int state;          //  ���-1,   ��λ��0,   ����1
	long double value;        //�õ��ֵ��
	long double n_value;        //�����Ʒ�
};



int main()
{
	point p[25][25];       //  15*15�߽�Ϊ5
	initialize(p);
	play(p);
	return 0;
}


//��ʼ��
void initialize(struct point p[25][25])
{
	int i, j;
	num = 0;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 25; j++)
		{
			p[i][j].state = 0;   //Ϊ��
			p[i][j].value = 0;
			p[i][j].n_value = 0;
		}
	}
}
//ʤ����������
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
					winner= draw;//ƽ��
				}
			}
			if (p[i][j].state)
			{
				for (x = -2; p[i][j].state == p[i][j + x].state && x < 4; x++)     //��
				{
				}
				for (y = -2; p[i][j].state == p[i + y][j].state && y < 4; y++)      //��
				{
				}
				for (b = -2; p[i][j].state == p[i + b][j + b].state && b < 4; b++)    //б��
				{
				}
				for (q = -2; p[i][j].state == p[i - q][j + q].state && q < 4; q++)    //б��
				{
				}
				if (x == 3 || y == 3 || b == 3 || q == 3)
				{
					if (p[i][j].state == 1)
					{
						winner = com; //����Ӯ
					}
					if (p[i][j].state == -1)
					{
						winner = hum; //���Ӯ
					}
				}
			}
		}
	}
	return winner;  //e=0Ĭ��δ����
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
	settextstyle(40, 0, "����");
	outtextxy(800, 200, "�� ��");
	outtextxy(800, 300, "�� ��");
	outtextxy(800, 400, "�� ��");
	outtextxy(800, 500, "�� ��");
	settextcolor(BLACK);
	settextstyle(15, 0, "����");
}

void drop(struct point p[25][25], int x, int y)
{
	setfillcolor(WHITE); //�����ɫ
	fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);//��Բ������һ��
	xx = x;
	yy = y;    //Ϊ������������¼
	p[x][y].state = 1;     //�޸�״̬
}

void regret(struct point p[25][25])
{
	board();
	setrop2(R2_COPYPEN);  //���û�����ɫ
	setcolor(WHITE);
	p[ii][jj].state = 0;  //����һ�������
	p[xx][yy].state = 0;
	for (int i = MIN; i < MAX; i++) {        //���»�������
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
			if (m.x <= 900 && m.y < 250 && m.x >= 800 && m.y > 200)  //����
			{
				regret(p);
				continue;
			}
			if (m.x <= 900 && m.y < 350 && m.x >= 800 && m.y > 300)	//�ؿ�
			{
				initialize(p);   //��ʼ��
				play(p);
			}
			if (m.x <= 900 && m.y < 450 && m.x >= 800 && m.y > 400)  //����
			{
				if (num < 1)
				{
					computer(p);   //����ִ��
					num++;
				}
			}
			if (m.x <= 900 && m.y < 550 && m.x >= 800 && m.y > 500)  //�˳�
			{
				closegraph(); 
				exit(0);    
			}

			if (x >= 25)     //���ִ��
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
					ii = i;    //Ϊ������������¼
					jj = j;
					p[i][j].state = -1;//�޸ĸ�λ�õ�״̬
				}
				if (result(p) != 0)//�����ж�
				{
					Sleep(1000);
					gameOver(result(p));
				}
				computer(p);   
				if (result(p) != 0)
				{
					gameOver(result(p));
				}
				num++;    //���Ĵ���
			}
		}
	}
}

void gameOver(int winner)
{
	point pp[25][25];      	
	initialize(pp);      //��ʼ��
	initgraph(400, 400);
	cleardevice();     //ʹ�õ�ǰ����ɫ��ջ�ͼ�豸
	settextstyle(50, 24, "����");
	settextcolor(RED);    //������ɫ
	if (winner == draw)
	{
		outtextxy(100, 50, "ƽ��");
	}
	else if (winner == hum)
	{
		outtextxy(100, 50, "��һ�ʤ");
	}
	else if (winner == com)
	{
		outtextxy(100, 50, "���Ի�ʤ");
	}
	settextcolor(WHITE);
	outtextxy(50, 200, "������Ϸ����");
	outtextxy(80, 300, " ������Ϸ");

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

//������������
double assess(struct point p[25][25])
{
	int i, j;
	p_assess(p);     //ĳ���ֵ
	long double s_value = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			s_value += p[i][j].value;//���������Ʒ�Ϊ���е�����ĺ�
		}
	}
	return s_value;
}


void p_assess(struct point p[25][25])
{
	int i, j, k, m, n, x, y;
	for (i = MIN; i < MAX; i++)     //�ɸĽ�Ϊ����ˢ��
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)
			{
				p[i][j].value = 0;      //��λ��ֵΪ�� 
			}
			else     //��Ϊ��
			{                                 //8������ÿ����ֵΪ10
				long double v1 = VALUE, v2 = VALUE, v3 = VALUE, v4 = VALUE, v5 = VALUE, v6 = VALUE, v7 = VALUE, v8 = VALUE;
				//****************************************************************************
				for (x = 0, n = j; p[i][j].state != -p[i][n + 1].state && n + 1 < 20 && x < 4; x++, n++)       //��
				{
				}
				if (x < 4)
				{
					v1 = 0;    //����סΪ0
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n + 1].state && k < 5; k++, n++)       //��
					{
						v1 *= VALUE;     //������������
					}
				}
				for (y = 0, n = j; p[i][j].state != -p[i][n - 1].state && n - 1 > 4 && y < 4; y++, n--)      //��
				{
				}
				if (y < 4)
				{
					v2 = 0;    //����סΪ0
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n - 1].state && k < 5; k++, n--)      //��
					{
						v2 *= VALUE;     //������������
					}
				}
				//******************************    ����ͬ��   ***************************************
				for (x = 0, n = i; p[i][j].state != -p[n + 1][j].state && n + 1 < 20 && x < 5; x++, n++)       //��
				{
				}
				if (x < 4)
				{
					v3 = 0;    //����סΪ0
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n + 1][j].state && k < 5; k++, n++)       //��
					{
						v3 *= VALUE;   //������������
					}
				}
				for (y = 0, n = i; p[i][j].state != -p[n - 1][j].state && n - 1 > 4 && y < 5; y++, n--)       //��
				{
				}
				if (y < 4)
				{
					v4 = 0;   //����סΪ0
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n - 1][j].state && k < 5; k++, n--)       //��
					{
						v4 *= VALUE;   //������������
					}
				}
				//**********************************   ����ͬ��    **************************************
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n + 1].state && n + 1 < 20 && m - 1 > 4 && x < 5; x++, m--, n++) //����
				{
				}
				if (x < 4)
				{
					v5 = 0;   //����סΪ0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n + 1].state && k < 5; k++, m--, n++)       //����
					{
						v5 *= VALUE;    //������������
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n - 1].state && m + 1 < 20 && n - 1 > 4 && y < 5; y++, m++, n--) //����
				{
				}
				if (y < 4)
				{
					v6 = 0;    //����סΪ0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n - 1].state && k < 5; k++, m++, n--)       //����
					{
						v6 *= VALUE;    //������������
					}
				}
				//***********************************    ����ͬ��    **************************************
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n - 1].state && n - 1 > 4 && m - 1 > 4 && x < 5; x++, m--, n--)  //����
				{
				}
				if (x < 4)
				{
					v7 = 0;    //����סΪ0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n - 1].state && k < 5; k++, m--, n--)       //����
					{
						v7 *= VALUE;    //������������
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n + 1].state && n + 1 < 20 && m + 1 < 20 && y < 5; y++, m++, n++) //����
				{
				}
				if (y < 4)
				{
					v8 = 0;    //����סΪ0
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n + 1].state && k < 5; k++, m++, n++)       //����
					{
						v8 *= VALUE;     //������������
					}
				}
				//********************************************************************************    //100000?ɱ
				p[i][j].value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));    //���Ͼ����������Ʒ�
				if (p[i][j].state == -1)    //�������Ϊ����
				{
					p[i][j].value = -p[i][j].value * DEFINE;       //EΪƫ����س̶�
				}
			}
		}
	}
}
//�ݹ����� 
double deduction(struct point p[25][25], /*int sex,*/ int depth, long double a, long double b)
{
	int m, n, i, j, t = 0, br = 0;
	long double value = 0;
	if (depth == 0 || result(p) != 0)   //�ﵽ��Ȼ���ֽ���
	{
		return assess(p);       //�ݹ���ڣ����ط���
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
				if (p[m][n].state == 0)   //Ϊ��
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
		return b; //���ط���
	}
	else if (depth % 2 == 0)     //���Բ�
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) {   
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0)     //Ϊ��
				{

					if (num < 80 && !hasNieghbor(p, m, n))
					{
						value = Alpha;
					}
					else {
						p[m][n].state = 1;     //����������ط�
						value = deduction(p,/* sex + 1,*/ depth - 1, a, b);
						p[m][n].state = 0;     //����
					}
					if (value > a)    //�����ֵ
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
		return a;//���ط���
	}
	return 0;
}
//����ִ��
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
			
				if (hasNieghbor(p,i,j) )  //��ƫƧ
				{
					p[i][j].state = 1;    //ģ������
					if (result(p) == com)           //��ö�����ӿɶ���
					{
						drop(p, i, j);    
						return 0;
					}
					else if ((p[i][j].n_value = deduction(p, 2, Alpha, Beta)) > KILL)       //��������
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
	drop(p, x, y);    //����
	return 0;
}

