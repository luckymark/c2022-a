#include"Gomoku.h"


struct point {
	int state;          //λ�õ�״̬    ���-1,   ��λ��0,   ����1
	long double value;        //�õ��ֵ��
	long double n_value;        //��һ���������ʱ���̵������Ʒ�
};


void initialize(struct point board[25][25])  //��ʼ��
{
	int i, j;
	num = 0;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 25; j++)
		{
			board[i][j].state = 0;   //Ϊ��
			board[i][j].value = 0;
			board[i][j].n_value = 0;
		}
	}
}

int end(struct point board[25][25])//ʤ����������
{
	int i, j, k = 0, x = 0, y = 0, b = 0, q = 0, e = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (board[i][j].state == 0)
			{
				k++;
				if (k == 0)
				{
					e = 1;//ƽ��
				}
			}
			if (board[i][j].state)
			{
				for (x = -2; board[i][j].state == board[i][j + x].state && x < 4; x++)     //��
				{
				}
				for (y = -2; board[i][j].state == board[i + y][j].state && y < 4; y++)      //��
				{
				}
				for (b = -2; board[i][j].state == board[i + b][j + b].state && b < 4; b++)    //б��
				{
				}
				for (q = -2; board[i][j].state == board[i - q][j + q].state && q < 4; q++)    //б��
				{
				}
				if (x == 3 || y == 3 || b == 3 || q == 3)
				{
					if (board[i][j].state == 1)
					{
						e = 2; //�����
					}
					if (board[i][j].state == -1)
					{
						e = 3; //���Ӯ
					}
				}
			}
		}
	}
	return e;  //e=0Ĭ��δ����
}
//�滭����
void board()
{
	initgraph(950, 800);//��ʼ����ͼ����
	setbkcolor(BROWN);//��ͼ����ɫ
	cleardevice();//ʹ�õ�ǰ����ɫ�����һ����ͼ
	setlinecolor(WHITE);//���õ�ǰ�豸������ɫ
	for (int i = 50; i <= 750; i += 50)//������
	{
		line(i, 50, i, 750);
		line(50, i, 750, i);
	}
	setlinecolor(BLACK);//���õ�ǰ�豸������ɫ
	settextstyle(40, 0, "����");
	outtextxy(800, 200, "�� ��");
	outtextxy(800, 300, "�� ��");
	outtextxy(800, 400, "�� ��");
	outtextxy(800, 500, "�� ��");
	settextcolor(BLACK);
	settextstyle(15, 0, "����");
	outtextxy(2, 2, "���ߣ�������");
}
//����
void play(struct point p[25][25], int x, int y)
{
	setfillcolor(WHITE); //�����ɫ
	fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);//��Բ������һ��
	xx = x;
	yy = y;    //Ϊ������������¼
	p[x][y].state = 1;     //�޸�״̬
}
//����
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
//����
void begin(struct point p[25][25])
{
	MOUSEMSG m; // ���������Ϣ
	int  x, y, i, j;
	board();   //ͼ�α�������
	setlinecolor(WHITE); //���õ�ǰ�豸������ɫ

	while (1)
	{
		m = GetMouseMsg();//��ȡ�����Ϣ
		x = m.x % 50;
		y = m.y % 50;
		setrop2(R2_COPYPEN);	//��ǰ��ɫ
		if (m.uMsg == WM_LBUTTONDOWN)		//����������
		{
			if (m.x <= 900 && m.y < 250 && m.x >= 800 && m.y > 200)  //����
			{
				regret(p);//����
				continue;
			}
			if (m.x <= 900 && m.y < 350 && m.x >= 800 && m.y > 300)	//�ؿ�
			{
				initialize(p);   //��ʼ��
				begin(p);
			}
			if (m.x <= 900 && m.y < 450 && m.x >= 800 && m.y > 400)  //����
			{
				if (num < 1)
				{
					robot(p);   //����ִ��
					num++;
				}
			}
			if (m.x <= 900 && m.y < 550 && m.x >= 800 && m.y > 500)  //�˳�
			{
				closegraph(); // �رջ�ͼ����
				exit(0);    //ǿ���˳�
			}

			if (x >= 25)     //���ִ��
				m.x = m.x - x + 50;
			else
				m.x = m.x - x;
			if (y >= 25)
				m.y = m.y - y + 50;
			else
				m.y = m.y - y;
			i = m.x / 50 - 1 + MIN; //����ת��
			j = m.y / 50 - 1 + MIN;
			if (i < 20 && j < 20)
			{
				if (p[i][j].state == -1)
					break;
				if (m.x <= 750 && m.y <= 750 && m.x >= 50 && m.y >= 50)
				{
					setfillcolor(RED);//���õ�ǰ�豸������ɫ
					fillcircle(m.x, m.y, 20); //�ڸ�λ�û�Բ����
					ii = i;    //Ϊ������������¼
					jj = j;
					p[i][j].state = -1;//�޸ĸ�λ�õ�״̬
				}
				if (end(p) != 0)//�����ж�
				{
					Sleep(1000);
					over(end(p));//��������
				}
				robot(p);   //����ִ��
				if (end(p) != 0)//�����ж�
				{
					Sleep(1000);
					over(end(p));//��������
				}
				num++;    //���Ĵ���
			}
		}
	}
}
//��������	
void over(int x)
{
	point pp[25][25];       //  5--19	
	initialize(pp);      //��ʼ��
	initgraph(400, 400);
	cleardevice();     //ʹ�õ�ǰ����ɫ��ջ�ͼ�豸
	settextstyle(50, 24, "����");
	settextcolor(RED);    //������ɫ
	if (x == 1)
	{
		outtextxy(100, 50, "ƽ��");
	}
	else if (x == 2)
	{
		outtextxy(100, 50, "���Ի�ʤ");
	}
	else if (x == 3)
	{
		outtextxy(100, 50, "��һ�ʤ");
	}
	settextcolor(WHITE);
	outtextxy(50, 200, "������Ϸ����");
	outtextxy(80, 300, " ������Ϸ");

	while (true)
	{
		MOUSEMSG n;//�����Ϣ
		n = GetMouseMsg();
		switch (n.uMsg) {
		case WM_LBUTTONDOWN:
			if (n.x <= 350 && n.x >= 50 && n.y <= 250 && n.y >= 200)
				begin(pp);   //������Ϸ����
			if (n.x <= 300 && n.x >= 80 && n.y <= 350 && n.y >= 300)
			{
				closegraph(); // �رջ�ͼ����
				exit(0);    //ǿ���˳�
			}
		}
	}
}
//������������
double all_value(struct point p[25][25])
{
	int i, j;
	value(p);     //ĳ���ֵ����
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
//ĳ���ֵ����
void value(struct point p[25][25])
{
	int i, j, k, m, n, x, y;
	for (i = MIN; i < MAX; i++) 
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
				//********************************************************************************
				p[i][j].value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));    //���Ͼ����������Ʒ�
				if (p[i][j].state == -1)    //�������Ϊ����
				{
					p[i][j].value = -p[i][j].value * JUDGE;       //JUDGEΪƫ����س̶�
				}
			}
		}
	}
}
//�ݹ����� 
double recursion(struct point p[25][25], int sex, int depth, long double a, long double b)
{
	int m, n, i, j, t = 0, br = 0;
	long double va = 0;
	if (depth == 0 || end(p) != 0)   //�ﵽ��Ȼ���ֽ���
	{
		return all_value(p);       //���ڣ����ط���
	}
	else if (sex % 2 == 1)     //��һغ�
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) {   //b��֦
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0)   //Ϊ��
				{
					if (num < 80) {
						t = 0;
						for (i = -1; i < 2; i++) {
							for (j = -1; j < 2; j++) {
								if (p[i + m][j + n].state != 0) {
									t++;     //ƫƧ���֦
								}
							}
						}
					}
					else {
						t = 1;
					}
					if (t == 0)   //ƫƧ
					{
						va = B;
					}
					else {
						p[m][n].state = -1;    //����������ط�
						va = recursion(p, sex + 1, depth - 1, a, b);
						p[m][n].state = 0;      //����
					}
					if (va < b)    //����Сֵ
					{
						b = va;
					}
					if (b < a)
					{
						break;    //b��֦
						br = 1;
					}
				}
			}
		}
		return b; //���ط���
	}
	else if (sex % 2 == 0)     //���Իغ�
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) {   //a��֦
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0)     //Ϊ��
				{
					if (num < 80) {
						t = 0;
						for (i = -1; i < 2; i++) {
							for (j = -1; j < 2; j++) {
								if (p[i + m][j + n].state != 0) {
									t++;     //ƫƧ���֦
								}
							}
						}
					}
					else {
						t = 1;
					}
					if (t == 0)   //ƫƧ
					{
						va = A;
					}
					else {
						p[m][n].state = 1;     //����������ط�
						va = recursion(p, sex + 1, depth - 1, a, b);
						p[m][n].state = 0;     //����
					}
					if (va > a)    //�����ֵ
					{
						a = va;
					}
					if (b < a)
					{
						break;    //a��֦
						br = 1;
					}
				}
			}
		}
		return a;//���ط���
	}
	return 0;
}
//����ִ��
int robot(struct point p[25][25])
{
	int i, j, x = 12, y = 12, m, n, t = 0;
	long double v = -999999999999999999;    //10^18
	for (i = MIN; i < MAX; i++)        //Ѱ��������ӵ�
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)      //Ϊ��
			{
				t = 0;
				for (m = -1; m < 2; m++) {
					for (n = -1; n < 2; n++) {
						if (p[i + m][j + n].state != 0) {
							t++;     //ƫƧ���֦
						}
					}
				}
				if (t != 0)   //��ƫƧ
				{
					p[i][j].state = 1;    //���������������
					if (end(p) == 2)
					{
						play(p, i, j);    //����
						return 0;
					}
					p[i][j].n_value = recursion(p, 1, 2, A, B);
					p[i][j].state = 0;    //����
					if (p[i][j].n_value > v)
					{
						v = p[i][j].n_value;    //�����ֵ
						x = i;
						y = j;     //��ȡ����
					}
				}
			}
		}
	}
	play(p, x, y);    //����
	return 0;
}

int main()
{
	point board[25][25];       //  ���̴�С15*15	�߽�Ϊ5
	initialize(board);      //��ʼ��
	begin(board);   //����
	return 0;
}
