# define _CRT_SECURE_NO_WARNINGS 1
#include"wu.h"
HWND gc;
int white[15][15];
int stick[15][15];

void downpoint(int m, int n) {
	setcolor(WHITE);
	white[m][n] = 1;
	stick[m][n] = 1;
	setfillcolor(WHITE);
	fillcircle((m + 1) * 30, (n + 1) * 30, 10);

}//���

void start()
{
	int cont = 0;

	initgraph(600, 800);
	/*setbkcolor(WHITE);
	setbkmode(TRANSPARENT);		*/		//���ô���͸��
	setbkcolor(GREEN);
	settextcolor(YELLOW);	//����������ɫ
	settextstyle(128, 0, _T("����"));		//���������С����ȡ�����
	outtextxy(100, 100, _T("������"));
	setlinecolor(GREEN);
	rectangle(150, 300, 450, 580);
	rectangle(160, 310, 440, 570);
	line(160,440,440,440);
	settextstyle(65, 0, _T("��������"));
	outtextxy(170, 340, _T("�˻�����"));
	outtextxy(170, 470, _T("�˻�����"));
	setlinecolor(WHITE);
	settextcolor(WHITE);
	
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x <= 440 && m.x >= 160 && m.y < 420 && m.y > 310)
				machine1();
			if (m.x <= 440 && m.x >= 160 && m.y < 560 && m.y > 420)
				machine2();
		}
	}
}
		



void board()
{
	initgraph(1000, 700);
	setbkcolor(BROWN);
	cleardevice();
	setlinecolor(BLACK);

	for (int i = 30; i <= 450; i += 30)
	{
		line(i, 30, i, 450);
		line(30, i, 450, i);
	}

	for (int i = 120; i < 480; i += 240)
	{
		for (int j = 120; j < 480; j += 240)
			fillcircle(i, j, 5);
	}
	fillcircle(30 * 8, 30 * 8, 5);

	setlinecolor(BLACK);
	rectangle(560, 250, 840, 540);
	rectangle(570, 260, 830, 530);
	line(570, 350, 830, 350);
	line(570, 440, 830, 440);
	settextstyle(50, 0, _T("����"));
	outtextxy(640, 275, _T("�� ��"));
	outtextxy(640, 365, _T("�� ��"));
	outtextxy(640, 455, _T("Ͷ ��"));
	outtextxy(600, 50, _T("���:"));
	outtextxy(600, 140, _T("����:"));
	setfillcolor(BLACK);
	fillcircle(780, 70, 20);
	setfillcolor(WHITE);
	fillcircle(780, 170, 20);

}


int success(int x[15][15])
{
	int m, n;
	for (m = 0; m < 15; m++)
	{
		for (n = 0; n < 15; n++)
		{
			if (x[m][n] == 1 && x[m][n + 1] == 1 && x[m][n + 2] == 1 && x[m][n + 3] == 1 && x[m][n + 4] == 1)return 1;
			if (x[m][n] == 1 && x[m + 1][n] == 1 && x[m + 2][n] == 1 && x[m + 3][n] == 1 && x[m + 4][n] == 1)return 1;
			if (x[m][n] == 1 && x[m + 1][n + 1] == 1 && x[m + 2][n + 2] == 1 && x[m + 3][n + 3] == 1 && x[m + 4][n + 4] == 1)return 1;
			if (n > 3 && x[m][n] == 1 && x[m + 1][n - 1] == 1 && x[m + 2][n - 2] == 1 && x[m + 3][n - 3] == 1 && x[m + 4][n - 4] == 1)return 1;
		}
	}
	return 0;
}

void regret(int x[15][15], int y[15][15])
{
	board();
	setrop2(R2_COPYPEN);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (x[i][j] == 1) {
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillcircle((i + 1) * 30, (j + 1) * 30, 10);
			}
			if (y[i][j] == 1) {
				setcolor(WHITE);
				setfillcolor(WHITE);
				fillcircle((i + 1) * 30, (j + 1) * 30, 10);
			}
		}
	}
}//����

void machine1()//�˻�����
{
	board();
	MOUSEMSG m; // ���������Ϣ
	int i = 0, x, y, q = 0, p = 0;
	int red[15][15];
	int whtie1[15][15];
	int store[15][15];
	for (int x1 = 0; x1 < 15; x1++) {
		for (int y1 = 0; y1 < 15; y1++) {
			store[x1][y1] = 0;
			white[x1][y1] = 0;
			red[x1][y1]=0;
			stick[x1][y1] = 0;
		}
	}
	while (true)
	{

		m = GetMouseMsg();
		x = m.x % 30;
		y = m.y % 30;
		setrop2(R2_COPYPEN);	//��Ԫ��դ�����룺R2_COPYPEN��ǰ��ɫ
		if (m.uMsg == WM_LBUTTONDOWN)		// ʹ�����������в���
		{
			if (m.x <= 830 && m.y < 530 && m.x >= 560 && m.y > 440)				 //Ͷ��
				win(2);
			if (m.x <= 830 && m.y < 440 && m.x >= 560 && m.y > 350) {
				machine1();
			}				//�ؿ�
			if (m.x <= 830 && m.y < 350 && m.x >= 560 && m.y > 260)          //����
			{
				for (int x1 = 0; x1 < 15; x1++) {
					for (int y1 = 0; y1 < 15; y1++) {
						if (whtie1[x1][y1] != white[x1][y1]) {
							white[x1][y1] = 0;
							stick[x1][y1] = 0;
						}

					}
				}
				red[p][q] = 0;
				stick[p][q] = 0;
				regret(red, whtie1);
				continue;
			}

			if (x >= 15)
				m.x = m.x - x + 30;
			else
				m.x = m.x - x;
			if (y >= 15)
				m.y = m.y - y + 30;
			else
				m.y = m.y - y;
			p = m.x / 30 - 1;
			q = m.y / 30 - 1;
			if (p < 15 && q < 15)
			{
				if (stick[p][q] == 1)
					continue;
				if (m.x <= 450 && m.y <= 450 && m.x >= 30 && m.y >= 30)
				{
					setlinecolor(BLACK);
					setfillcolor(BLACK);
					fillcircle(m.x, m.y, 10);
					red[p][q] = 1;
					if (success(red) == 1)
						win(1);
					stick[p][q] = 1;
				}
				for (int x1 = 0; x1 < 15; x1++) {
					for (int y1 = 0; y1 < 15; y1++) {
						whtie1[x1][y1] = white[x1][y1];
					}//���������й�
				}
				for (int x1 = 0; x1 < 15; x1++) {
					for (int y1 = 0; y1 < 15; y1++) {
						if (white[x1][y1] != 0)
							store[x1][y1] = white[x1][y1]+1;
						if (red[x1][y1] != 0)
							store[x1][y1] = red[x1][y1];
					}//�����¼
				}
				
			MAXMINvalue( store, DEEP, (double)INT_MIN, INT_MAX);
				if (success(white) == 1)
					win(2);
			}
			
		}
	}
}


void machine2()//�˻�����
{
	board();
	MOUSEMSG m; // ���������Ϣ
	int i = 0, x, y, q = 0, p = 0;
	int red[15][15];
	int whtie1[15][15];
	int store[15][15];
	for (int x1 = 0; x1 < 15; x1++) {
		for (int y1 = 0; y1 < 15; y1++) {
			store[x1][y1] = 0;
			white[x1][y1] = 0;
			red[x1][y1] = 0;
			stick[x1][y1] = 0;
		}
	}
	downpoint(7, 7);
	whtie1[7][7] = 1;
	while (true)
	{

		m = GetMouseMsg();
		x = m.x % 30;
		y = m.y % 30;
		setrop2(R2_COPYPEN);	//��Ԫ��դ�����룺R2_COPYPEN��ǰ��ɫ
		if (m.uMsg == WM_LBUTTONDOWN)		// ʹ�����������в���
		{
			if (m.x <= 830 && m.y < 530 && m.x >= 560 && m.y > 440)				 //Ͷ��
				win(2);
			if (m.x <= 830 && m.y < 440 && m.x >= 560 && m.y > 350) {
				machine2();
			}				//�ؿ�
			if (m.x <= 830 && m.y < 350 && m.x >= 560 && m.y > 260)          //����
			{
				for (int x1 = 0; x1 < 15; x1++) {
					for (int y1 = 0; y1 < 15; y1++) {
						if (whtie1[x1][y1] != white[x1][y1]) {
							white[x1][y1] = 0;
							stick[x1][y1] = 0;
						}

					}
				}
				red[p][q] = 0;
				stick[p][q] = 0;
				regret(red, whtie1);
				continue;
			}

			if (x >= 15)
				m.x = m.x - x + 30;
			else
				m.x = m.x - x;
			if (y >= 15)
				m.y = m.y - y + 30;
			else
				m.y = m.y - y;
			p = m.x / 30 - 1;
			q = m.y / 30 - 1;
			if (p < 15 && q < 15)
			{
				if (stick[p][q] == 1)
					continue;
				if (m.x <= 450 && m.y <= 450 && m.x >= 30 && m.y >= 30)
				{
					setfillcolor(BLACK);
					fillcircle(m.x, m.y, 10);
					red[p][q] = 1;
					if (success(red) == 1)
						win(1);
					stick[p][q] = 1;
				}
				for (int x1 = 0; x1 < 15; x1++) {
					for (int y1 = 0; y1 < 15; y1++) {
						whtie1[x1][y1] = white[x1][y1];
					}
				}
				for (int x1 = 0; x1 < 15; x1++) {
					for (int y1 = 0; y1 < 15; y1++) {
						if (white[x1][y1] != 0)
							store[x1][y1] = white[x1][y1] + 1;
						if (red[x1][y1] != 0)
							store[x1][y1] = red[x1][y1];
					}
				}

				MAXMINvalue(store, DEEP, (double)INT_MIN, INT_MAX);
				if (success(white) == 1)
					win(2);
			}

		}
	}
}
void win(int x)//�ж�ʤ��
{
initgraph(800, 600);
cleardevice();
settextstyle(100, 0, _T("��������"));
if (x == 1)
{
	settextcolor(GREEN);
	outtextxy(240, 270, _T("��Ӯ��"));
	Sleep(1000);
}
else
{
	settextcolor(RED);
	outtextxy(240, 270, _T("������"));
	Sleep(1000);
}
cleardevice();
settextcolor(WHITE);
settextstyle(50, 0, _T("��������"));
outtextxy(220, 220, _T("������Ϸ����"));
outtextxy(220, 400, _T(" ������Ϸ"));

while (true)
{
	int ID;
	MOUSEMSG n;
	n = GetMouseMsg();
	switch (n.uMsg) {
	case WM_LBUTTONDOWN:
		if (n.x <= 520 && n.x >= 220 && n.y <= 380 && n.y >= 220)
		{
			start();
		}
			if (n.x <= 470 && n.x >= 220 && n.y <= 580 && n.y >= 400) {
				gc = GetHWnd();    //����ǰ��
				ID = MessageBox(gc, _T("�Ƿ�ر���Ϸ?"), _T(""), MB_YESNO);
				if (ID == IDYES)
						over();
			}

	}
}
}

void over()
{

	initgraph(500, 500);
	settextcolor(RED);
	settextstyle(100, 0, _T("��������"));
	outtextxy(120, 200, _T("лл����"));
	Sleep(1800);
	closegraph(); // �رջ�ͼ����
}

int main()
{
	start();
	return 0;
}
