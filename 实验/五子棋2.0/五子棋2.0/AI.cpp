#include"all.h"
extern int Chess[ROW][LINE];

extern int mm ;
extern int	n ;
int box[40][3] = { 0 };
int memory[30] = { 0 };


int monitor[11] = { 0 };




int five[5][7] =  {0,2,2,2,2,2,0,
                   2,2,2,2,2,0,0,
	               2,2,2,2,0,0,0,
                   0,0,2,2,2,2,2,
                   0,0,0,2,2,2,2};
int five2[7] = { 0,1,1,1,1,1,0 };
int five3[7] = { 1,1,1,1,1,0,0 };//10000000


int four[4][7] ={0,2,2,2,2,0,0,
                  2,2,2,2,0,0,0,
	              0,0,2,2,2,2,0,
	              0,0,0,2,2,2,2};
int four2[7] = { 0,1,1,1,1,0,0 };
int four3[7] = { 1,1,1,1,0,0,0 };
int four4[7] = { 0,0,0,1,1,1,1 };//1000000


int cfour[6][7] = {1,2,2,2,2,0,0,
                    0,1,2,2,2,2,0,
	                0,0,1,2,2,2,2,
	                2,2,2,1,0,0,0,
	                2,2,2,2,1,0,0,
	                0,2,2,2,2,1,0 };
int cfour2[7] = { 0,2,1,1,1,1,0 };
int cfour3[7] = { 0,0,2,1,1,1,1 };
int cfour4[7] = { 1,1,1,1,2,0,0 };
int cfour5[7] = { 0,1,1,1,1,2,0 };
int cfour6[7] = { 0,0,1,1,1,1,2 };//10000//后续可以改良为二维数组



int three[3][7] = { 0,2,2,2,0,0,0,
                    0,0,2,2,2,0,0,
	                0,0,0,2,2,2,0};
int three2[7] = { 0,0,1,1,1,0,0 };
int three3[7] = { 0,0,0,1,1,1,0 };//8000


int dthree[6][7] = { 1,2,2,2,0,0,0, 
                     0,1,2,2,2,0,0,
	                 0,0,1,2,2,2,0,
	                 0,0,0,2,2,2,1,
	                 0,0,2,2,2,1,0,
	                 0,2,2,2,1,0,0,};
int dthree2[7] = { 0,2,1,1,1,0,0 };
int dthree3[7] = { 0,0,2,1,1,1,0 };
int dthree4[7] = { 0,0,0,1,1,1,2 };
int dthree5[7] = { 0,0,1,1,1,2,0 };
int dthree6[7] = { 0,1,1,1,2,0,0 };//1000



int two[2][7] = {0,0,0,2,2,0,0,
                 0,0,2,2,0,0,0 };
int two2[7] = { 0,0,1,1,0,0,0 };//800

int dtwo[4][7] = { 0,0,1,2,2,0,0,
                   0,1,2,2,0,0,0 , 
	               0,0,2,2,1,0,0 ,
	               0,0,0,2,2,1,0 };
int dtwo2[7] = { 0,2,1,1,0,0,0 };
int dtwo3[7] = { 0,0,1,1,2,0,0 };
int dtwo4[7] = { 0,0,0,1,1,2,0 };//50

int done[2][7] = { 0,0,0,2,1,0,0,
                   0,0,1,2,0,0,0 };
int done2[7] = { 0,0,2,1,0,0,0 };//10




void turn(int array[][7], int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (array[i][j] == 1)
				array[i][j] = 2;
			else if (array[i][j] == 2)
				array[i][j] = 1;
		}
	}
}




int evaluate(int Chess[][15], int m, int n)
{
	int cpoint = 0;
	if (Chess[m][n] != five[0][3])
	{
		turn(five, 5);
		turn(four, 4);
		turn(cfour, 6);
		turn(three, 3);
		turn(dthree, 6);
		turn(two, 2);
		turn(dtwo, 4);
		turn(done, 2);
	}
	for (int i = 0; i < 7; i++)
	{
		if (m-3+i < 0 || m-3+i>15)//不够，要扩大容量来判断，不然五个的很容易漏掉
			break;
		else
			monitor[i] = Chess[m - 3 + i][n];
	}//0001000
	cpoint = jud(monitor);
	for (int i = 0; i < 7; i++)
	{
		if (n -3 + i < 0 || n - 3+ i>15)
			break;
		else
			monitor[i] = Chess[m ][n-3+i];
	}
	if (cpoint < jud(monitor))
		cpoint = jud(monitor);
	for (int i = 0; i < 7; i++)
	{
		if (n - 3 + i < 0 || n - 3 + i>15|| m - 3 + i < 0 || m - 3 + i>15)
			break;
		else
			monitor[i] = Chess[m-3+i][n - 3 + i];
	}
	if (cpoint < jud(monitor))
		cpoint = jud(monitor);
	for (int i = 0; i < 7; i++)
	{
		if (n + 3 - i < 0 || n + 3 - i>15 || m - 3 + i < 0 || m - 3 + i>15)
			break;
		else
			monitor[i] = Chess[m -  3+ i][n + 3 - i];
	}
	if (cpoint < jud(monitor))
		cpoint = jud(monitor);
	//turn(five, 5);
	//turn(four, 4);
	//turn(cfour, 6);
	//turn(three, 3);
	//turn(dthree, 6);
	//turn(two, 2);
	//turn(dtwo, 4);
	//turn(done, 2);
	return cpoint;
}




int jud(int monitor[])
{
	int cont = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == five[i][j])
				cont++;
			else
				break;
		}
		if (cont == 7)
			return 10000000;
		else
			cont = 0;
    }
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == four[i][j])
				cont++;
			else
				break;
		}
		if (cont == 7)
			return 1000000;
		else
			cont = 0;
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == cfour[i][j])
				cont++;
			else
				break;
		}
		if (cont == 7)
			return 8000;
		else
			cont = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == three[i][j])
				cont++;
			else
				break;
		}
		if (cont == 7)
			return 10000;
		else
			cont = 0;
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == dthree[i][j])
				cont++;
			else
				break;
		}
		if (cont == 7)
			return 5000;
		else
			cont = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == two[i][j])
				cont++;
			else
				break;
		}
		if (cont == 7)
			return 1000;
		else
			cont = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == dtwo[i][j])
				cont++;
			else
				break;//要相应改进一下，不然情况就固定死了
		}
		if (cont >= 5)
			return 500;
		else
			cont = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (monitor[j] == done[i][j])
				cont++;
			else
				break;
		}
		if (cont >= 5)
			return 50;
		else
			cont = 0;
	}
	return 0;
}
//
//
//
//int judge(int num,int block)
//{
//	if (num == 5)
//		return 10000000;
//	if (num == 4 && block == 0)
//		return 1000000;
//	if (num == 4 && block == 1)
//		return 500000;
//	if (num == 3 && block == 0)
//		return 80000;
//	if (num == 3&& block == 1)
//	{
//		return 40000;
//	}
//	if (num == 2 && block == 0)
//	{
//		return 10000;
//	}
//	if (num == 2 && block == 1)
//	{
//		return 5000;
//	}
//	else
//		return 100;
//}
//
//
//
//
//
//
//
//
//
//int evaluate(int Chess[][15], int m, int n)
//{
//	int num = 0;
//	int block =0;
//	int point = 0;
//	int pin = 0;
//		int* sp = &Chess[m][n];
//		int* search = sp;
//		if (search[--pin] == *sp)
//		{
//			for (int i = 0; i < 5; i++)
//			{
//				if (search[pin] == *sp)
//				{
//					pin--;
//					num++;
//				}
//				else
//				{
//					if (search[pin] != 0)
//						block++;
//					break;
//				}
//			}
//		}
//		pin = 0;
//		if(search[++pin]==*sp)
//		{
//			for (int i = 0; i < 5; i++)
//			{
//				if (search[pin] == *sp)
//				{
//					pin++;
//					num++;
//				}
//				else
//				{
//					if (search[pin] != 0)
//						block++;
//					break;
//				}
//			}
//		}
//	point += judge(num, block);
//	num = 0;
//	block = 0;
//	pin = 0;
//	//point = judge(num, block);
//	//num = 0;
//	//block = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	if (m + i < 15&&m - 4>0)
//	//	{
//	//		if(Chess[m+i-4][n]!=Chess[m][n])
//	//		if (Chess[m + i-4][n] == Chess[m][n]&&Chess[m+i-4][n] == Chess[m + i - 3][n])
//	//		{
//	//			num++;
//	//		}
//	//		else
//	//		{
//	//			if (Chess[m + i][n] != 0)
//	//			{
//	//				block++;
//	//				break;
//	//			}
//	//		}
//	//	}
//	//}//先找到相同的，再去循环
//	//point = judge(num,block);
//	//num = 1;
//	//block = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	if (n + i < 15 && n - 4>0)
//	//	{
//	//		if (Chess[m ][n+i-4] == Chess[m][n] && Chess[m][n+i-4] == Chess[m][n + i - 3])
//	//		{
//	//			num++;
//	//		}
//	//		else
//	//		{
//	//			if (Chess[m + i][n] != 0)
//	//				block;
//	//		}
//	//	}
//	//}
//	//point += judge(num, block);
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	if (m + i < 15 && m - 4>0&&n+i<15&&n-4>0)
//	//	{
//	//		if (Chess[m + i - 4][n+i-4] == Chess[m][n] && Chess[m + i - 4][n+i-4] == Chess[m + i - 3][n+i-3])
//	//		{
//	//			num++;
//	//		}
//	//		else
//	//		{
//	//			if (Chess[m + i][n] != 0)
//	//				block++;
//	//			break;
//	//		}
//	//	}
//	//}
//	//point += judge(num, block);
//	//num = 1;
//	//block = 0;
//
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	if (m + i < 15 && m - 4>0 && n + i < 15 && n - 4>0)
//	//	{
//	//		if (Chess[m + i - 4][n +4-i] == Chess[m][n] && Chess[m + i - 4][n +4-i] == Chess[m + i - 3][n +3-i])
//	//		{
//	//			num++;
//	//		}
//	//		else
//	//		{
//	//			if (Chess[m + i][n] != 0)
//	//				block++;
//	//			break;
//	//		}
//	//	}
//	//}
//	//point += judge(num, block);
//	//num = 1;
//	//block = 0;
//	return point;
//}




//int evaluate(int Chess[][15], int m, int n)
//{
//	int point = 10;
//	int v1 = 10, v2 = 10, v3 = 10, v4 = 10, v5 = 10, v6 = 10, v7 = 10, v8 = 10;
//	int score = 10;
//	//左四个
//	int x = 1, y = 0;
//	for (x = 1, y = 1; Chess[m - y][n] == Chess[m][n]||Chess[m-y][n]==0&&m-y>0 && x<6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v1 = 0;
//	}
//	else
//	{
//		v1 = 10;
//		for (x = 1; Chess[m - x][n] == Chess[m][n] && x < 5; x++)
//		{
//			v1 *= score;
//		}
//	}
//	//右四个
//	for (x = 1, y = 1; Chess[m + y][n] == Chess[m][n] || Chess[m + y][n] == 0 && m + y <15 && x < 6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v2 = 0;
//	}
//	else
//	{
//		v2 = 10;
//		for (x = 1; Chess[m + x][n] == Chess[m][n] && x < 5; x++)
//		{
//			v2 *= score;
//		}
//		if (v1 > 10)
//		{
//			v1 *= v2;
//			v2 = 0;
//		}
//	}
//	//上四个
//	for (x = 1, y = 1; Chess[m][n-y] == Chess[m][n] || Chess[m][n-y] == 0 && n - y > 0 && x < 6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v3 = 0;
//	}
//	else
//	{
//		v3 = 10;
//		for (x = 1; Chess[m][n-x] == Chess[m][n] && x < 5; x++)
//		{
//			v3 *= score;
//		}
//	}
//	//下四
//	for (x = 1, y = 1; Chess[m ][n+y] == Chess[m][n] || Chess[m][n+y] == 0 && n+y<15 && x < 6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v4 = 0;
//	}
//	else
//	{
//		v4 = 10;
//		for (x = 1; Chess[m][n+x] == Chess[m][n] && x < 5; x++)
//		{
//			v4 *= score;
//		}
//		if (v3 > 10)
//		{
//			v3 *= v4;
//			v4 = 0;
//		}
//	}
//	//左斜四
//	for (x = 1, y = 1; Chess[m - y][n-y] == Chess[m][n] || Chess[m - y][n-y] == 0 && m - y > 0&&n - y>0 && x < 6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v5 = 0;
//	}
//	else
//	{
//		v5 = 10;
//		for (x = 1; Chess[m - x][n-x] == Chess[m][n] && x < 5; x++)
//		{
//			v5 *= score;
//		}
//	}
//	//右斜四
//	for (x = 1, y = 1; Chess[m + y][n + y] == Chess[m][n] || Chess[m + y][n + y] == 0 && m + y <15 && n +y<15 && x < 6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v6 = 0;
//	}
//	else
//	{
//		v6 = 10;
//		for (x = 1; Chess[m + x][n + x] == Chess[m][n] && x < 5; x++)
//		{
//			v6 *= score;
//		}
//		if (v5 > 10)
//		{
//			v5 *= v6;
//			v6 = 0;
//		}
//	}
//	//左斜
//	for (x = 1, y = 1; Chess[m - y][n + y] == Chess[m][n] || Chess[m - y][n + y] == 0 && m - y > 0 && n +y <15 && x < 6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v7 = 0;
//	}
//	else
//	{
//		v7 = 10;
//		for (x = 1; Chess[m - x][n + x] == Chess[m][n] && x < 5; x++)
//		{
//			v7 *= score;
//		}
//	}
//	//右斜
//	for (x = 1, y = 1; Chess[m + y][n - y] == Chess[m][n] || Chess[m + y][n - y] == 0 && m +y<15 && n - y > 0 && x < 6; x++, y++)
//	{
//	}
//	if (x < 5)
//	{
//		v8 = 0;
//	}
//	else
//	{
//		v8 = 10;
//		for (x = 1; Chess[m + x][n - x] == Chess[m][n] && x < 5; x++)
//		{
//			v8 *= score;
//		}
//		if (v7 > 10)
//		{
//			v7 *= v8;
//			v8 = 0;
//		}
//	}
//	point = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8;
//	if (Chess[m][n] == 1)
//		point = -point;
//	return point;
//}
//
//int evaluate2(int Chess[][15], int m, int n)
//{
//	int x = 1; 
//	int point = 10;
//	int v1 = 10, v2 = 10, v3 = 10, v4 = 10, v5 = 10, v6 = 10, v7 = 10, v8 = 10;
//	int score = 10;
//	if (Chess[m][n] != Chess[m + 1][n] && Chess[m + 1][n] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m + x][n] || Chess[m + x][n] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v1 = 10000000;
//		}
//	}
//	else
//		v1 = 0;
//	if (Chess[m][n] != Chess[m - 1][n] && Chess[m - 1][n] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m - x][n] || Chess[m - x][n] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v2 = 10000000;
//		}
//	}
//	else
//	{
//		v2 = 0;
//	}//上下
//	if (Chess[m][n] != Chess[m][n - 1] && Chess[m][n - 1] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m][n - x] || Chess[m][n - x] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v3 = 10000000;
//		}
//	}
//	else
//		v3 = 0;
//	if (Chess[m][n] != Chess[m][n + 1] && Chess[m][n + 1] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m][n + x] || Chess[m][n + x] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v4 = 10000000;
//		}
//	}
//	else
//		v4 = 0;//左右
//	if (Chess[m][n] != Chess[m + 1][n + 1] && Chess[m + 1][n + 1] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m + x][n + x] || Chess[m + x][n + x] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v5 = 10000000;
//		}
//	}
//	else
//		v5 = 0;
//	if (Chess[m][n] != Chess[m - 1][n - 1] && Chess[m - 1][n - 1] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m - x][n - x] || Chess[m - x][n - x] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v6 = 10000000;
//		}
//	}
//	else
//		v6 = 0;//斜1
//	if (Chess[m][n] != Chess[m + 1][n - 1] && Chess[m + 1][n - 1] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m + x][n - x] || Chess[m + x][n - x] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v7 = 10000000;
//		}
//	}
//	else
//		v7 = 0;
//	if (Chess[m][n] != Chess[m - 1][n + 1] && Chess[m - 1][n + 1] != 0)
//	{
//		for (x = 1; x < 5; x++)
//		{
//			if (Chess[m][n] == Chess[m - x][n + x] || Chess[m - x][n + x] == 0)
//			{
//				break;
//			}
//		}
//		if (x > 2)
//		{
//			v8 = 10000000;
//		}
//	}
//	else
//		v8 = 0;
//	point = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8;
//	if (Chess[m][n] == 1)
//		point = -point;
//	return point;
//}



//void dfs(int *row,int *line)
//{
//	int p = 0;
//	int max = 0, num = 0, max1 = 0;
//	int p1 = 0, p2 = 0;
//	int a = 0, b = 0;
//
//	for (int i = 0; i < 15; i++)
//	{
//		for (int j = 0; j < 15; j++)
//		{
//			if (Chess[i][j] == 0)
//			{
//				Chess[i][j] = 2;
//				p = evaluate(Chess, i, j);
//				Chess[i][j] = 1;
//				p1 = evaluate(Chess, i, j);
//				/*p1 = evaluate1(Chess, i, j);*/
//				if (p + p1>max)
//				{
//					max = p+ p1;
//					*row = i;
//					*line = j;
//				}
//				Chess[i][j] = 0;
//			}
//			if (Chess[i][j] == 2)
//				num++;
//		}
//	}
//	if (num == 0)
//	{
//		srand((unsigned)time(NULL));
//		*row = 7/*rand()%14*/;
//		*line = 7/*rand()%14*/;
//	}
//	Chess[*row][*line] = 2;
//	printf("(%d,%d) %d\n", *row, *line, 2);
//}

void dfs(int* row,int* line)
{
	int p = 0;
	int max = 0, num = 0, max1 = 0;
	int p1 = 0, p2 = 0;
	int a = 0, b = 0;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (Chess[i][j] != 0)
				num++;
		}
	}
	if (num == 0)
	{
		srand((unsigned)time(NULL));
		*row = 7/*rand()%14*/;
		*line = 7/*rand()%14*/;
	}
	else
	{
		memset(memory, 0, sizeof(memory));
		memset(box, 0, sizeof(box));
		dfs1(0,num,0,row,line,0);
	}
	Chess[*row][*line] = 2;
	printf("(%d,%d) %d\n", *row, *line, 2);
}

void dfs1(int deepth, int num, int step, int* m, int* n, int turn)//修改问题：一开始传入了一个二维数组，运算时发现数组是新的，地址和传进来的都不一样，原因猜想应该是Chess数组已经被常定义了
{
	int point;
	int all = 0;
	int max = 0;
	int point1,point2;
	if (deepth == 1)
	{
		all = memory[0] + memory[1] + memory[2];
		max = memory[3];
		if (max < all)
		{
			*m = box[0][0];
			*n = box[0][1];
			memory[3] = all;
		}
		return;
	}
	else
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (Chess[i][j] == 0)
				{
					if (num % 2 == 0)
					{
						Chess[i][j] = 2;
						point1 = evaluate(Chess, i, j);
						Chess[i][j] = 1;
						point2 = evaluate(Chess, i, j);
					}
					else
					{
						Chess[i][j] = 1;
					    point1 = evaluate(Chess, i, j);
					    Chess[i][j] = 2;
					    point2 = evaluate(Chess, i, j);
				    }
					point = point1 + point2;//进攻
					//point2 = evaluate2(Chess, i, j);//防守
					box[step][0] = i;
					box[step][1] = j;
					memory[step] = point;
					dfs1( deepth+1, num+1,step+1,m,n,turn+1);
					Chess[i][j] = 0;
				}
			}
		}
	}
	return;
}
