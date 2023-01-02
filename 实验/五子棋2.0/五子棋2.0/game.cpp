#include"all.h"
int Chess[ROW][LINE] = { 0 };

int mm = 0;
int	n = 0;

//长宽约19.6  左上（17，7）

void board()
{
	initgraph(900, 900);
	for (int i = 0; i < 16; i++)
	{
		line(900/15*i, 0, 900/15*i, 900);
		line(0, 900 / 15 * i, 900, 900 / 15 * i);
	}
	/*loadimage(NULL, _T("C:\\Users\\麦克斯韦\\Desktop\\偷跑代码库\\五子棋\\f11f3a292df5e0fe62dc27035e6034a85fdf72e81.jpg"));*/
}







void player()
{
	setfillcolor(BLACK);
	MOUSEMSG m;
	int line, row;
	while (true)
	{
		flag:
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
				row = m.x;
				line = m.y;
				chess(&row, &line);
				if (Chess[mm][n] == 0)
				{
					Chess[mm][n] = 1;
					printf("(%d,%d) %d\n", mm, n, 1);
					solidcircle(row, line, 10);
				}
				else
					goto flag;
		//case WM_MOUSEMOVE:
		//	char s[12];
		//	setfillcolor(BLACK);
		//	solidrectangle(0, 0, 75, 20);
		//	sprintf(s, "[%d,%d]", m.x, m.y);
		//	outtextxy(0, 0, s);
		}
		if (m.uMsg == WM_LBUTTONUP)
			break;
	}
}





void chess(int *row,int *line)
{
		*row = *row - OROW;
		*line = *line - OLINE;
		for (int i = 0; i < 15; i++)
		{
			if (i * S - S / 2 < *row && i * S + S / 2 > *row)
			{
				*row = S * i + OROW;
				mm = i;
				break;
			}

		}
		for (int i = 0; i < 15; i++)
		{
			if (i * S - S / 2 <*line && i * S + S / 2 > *line)
			{
				*line = S * i + OLINE;
				n = i;
				break;
			}
		}
}

void computer()
{
	setfillcolor(WHITE);
	int row = 7, line = 7;
	dfs(&row,&line);
	solidcircle(60*row, 60*line, 10);
}

//void computer()
//{
//	MOUSEMSG m;
//	int line, row;
//	while (true)
//	{
//	flag1:
//		setfillcolor(WHITE);
//		m = GetMouseMsg();
//		switch (m.uMsg)
//		{
//		case WM_LBUTTONDOWN:
//			row = m.x;
//			line = m.y;
//			chess(&row, &line);
//			if (Chess[mm][n] ==0)
//			{
//				Chess[mm][n] = 2;
//				printf("(%d,%d) %d\n", mm, n, 2);
//				solidcircle(row, line, 10);
//			}
//			else
//				goto flag1;
//		//case WM_MOUSEMOVE:
//		//	char s[12];
//		//	setfillcolor(WHITE);
//		//	solidrectangle(0, 0, 75, 20);
//		//	sprintf(s, "[%d,%d]", m.x, m.y);
//		//	outtextxy(0, 0, s);
//		}
//		if (m.uMsg == WM_LBUTTONUP)
//			break;
//	}
//}



int judge1()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int y = 0; y < LINE - 5; y++)
		{
			if (Chess[i][y] == Chess[i][y + 1] && Chess[i][y] == Chess[i][y + 2] && Chess[i][y] == Chess[i][y + 3] && Chess[i][y] == Chess[i][y + 4] && Chess[i][y] != 0)
			{
				return 1;
			}
			if (Chess[y][i] == Chess[y + 1][i] && Chess[y][i] == Chess[y + 2][i] && Chess[y + 3][i] == Chess[y][i] && Chess[y][i] == Chess[y + 4][i] && Chess[y][i] != 0)
			{
				return 1;
			}
		}
	}
	return 0;
}



//int judge12()
//{
//	int num = 1;
//	for (int i = 1; i <5; i++)
//	{
//		if (mm - i >= 0 && mm - i < 15 && n - i >= 0 && n - i < 15)
//		{
//			if (Chess[mm - i][n - i] == Chess[mm][n] && Chess[mm][n] != 0)
//				num++;
//		}
//		if (mm + i > 0 && mm - i < 15 && n + i>0 && n + i < 15)
//		{
//			if (Chess[mm + i][n + i] == Chess[mm][n] && Chess[mm][n] != 0)
//				num++;
//		}
//	}
//	if (num==5)
//		return 1;
//	return 0;
//}








//int judge21()
//{
//	int num = 1;
//	for (int i = 1; i < 5; i++)
//	{
//		if (mm - i >= 0 && mm - i < 15 && n + i >= 0 && n + 1 < 15)
//		{
//			if (Chess[mm - i][n + i] == Chess[mm][n] && Chess[mm][n] != 0)
//			{
//				num++;
//			}
//		}
//		if (mm + i >= 0 && mm + i < 15 && n - i >= 0 && n - i < 15)
//		{
//			if (Chess[mm + i][n - i] == Chess[mm][n] && Chess[mm][n] != 0)
//				num++;
//		}
//	}
//	if (num==5)
//		return 1;
//	return 0;
//}
int judge12()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int y = 0; y < LINE - 5; y++)
		{
			if (Chess[i][y] == Chess[i +1][y + 1] && Chess[i][y] == Chess[i + 2][y + 2] && Chess[i][y] == Chess[i + 3][y + 3] && Chess[i][y] == Chess[i + 4][y + 4] && Chess[i][y] != 0)
			{
				return 1;
			}
			if (i - 4 < 0 || y - 4 < 0)
				continue;
			if (Chess[y][i] == Chess[y -1][i - 1] && Chess[y][i] == Chess[y - 2][i - 2] && Chess[y - 3][i - 3] == Chess[y][i] && Chess[y][i] == Chess[y - 4][i - 4] && Chess[y][i] != 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

int judge21()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int y = 0; y < LINE - 5; y++)
		{
			if (i - 4 < 0&&y+4<15)
			{
				if (Chess[i][y] == Chess[i - 1][y + 1] && Chess[i][y] == Chess[i - 2][y + 2] && Chess[i][y] == Chess[i - 3][y + 3] && Chess[i][y] == Chess[i - 4][y + 4] && Chess[i][y] != 0)
				{
					return 1;
				}
				if (Chess[y][i] == Chess[y + 1][i - 1] && Chess[y][i] == Chess[y + 2][i - 2] && Chess[y + 3][i - 3] == Chess[y][i] && Chess[y][i] == Chess[y + 4][i - 4] && Chess[y][i] != 0)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}





int judge2()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int y = 0; y < LINE - 5; y++)
		{
			if (Chess[i][y] == Chess[i][y + 1] && Chess[i][y] == Chess[i][y + 2] && Chess[i][y] == Chess[i][y + 3] &&Chess[i][y]== Chess[i][y + 4] && Chess[i][y] != 0)
			{
				return 1;
			}
			if (Chess[y][i] == Chess[y + 1][i] && Chess[y][i] == Chess[y + 2][i] && Chess[y + 3][i] == Chess[y][i]&& Chess[y][i] == Chess[y+4][i] && Chess[y][i] != 0)
			{
				return 1;
			}
		}
	}
	return 0;
}





int game()
{


	//目录


	board();



	//开始
	while (1)
	{

		computer();
		if (judge1()==1||judge12()==1||judge21()==1)
		{
			printf("computer win");
			break;
		}
		player();
		if (judge2() == 1||judge12()==1||judge21()==1)
		{
			printf("player win");
			break;
		}


	}





	return 0;
}