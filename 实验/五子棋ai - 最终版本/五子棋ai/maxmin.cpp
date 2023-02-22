#include"maxmin.h"
#include"Chess.h"


int chessmap[15][15] = {};


int score(int a, int co[size][size], int n)
//评分,a为1表示白棋，为-1表示黑棋,n为1避免递归调用出现死循环
{

	int i, j, k, l;
	int sum = 0, su = 0;
	for (i = 0; i < 20; i++)                //点
		for (j = 0; j < 20; j++)
			if (co[i][j] == a)
			{
				for (k = i - 1; k < i + 2; k++)
					for (l = j - 1; l < j + 2; l++)
						su += co[k][l];
				if (su == a && i != 0 && i != 19 && j != 0 && j != 19)
					sum += 10;
				su = 0;
			}
	su = 0;
	for (i = 0; i < 20; i++)                  //横
		for (j = 0; j < 21; j++)
		{
			if (co[i][j] == a)
				su++;
			else if (su > 1)
			{
				if (co[i][j - su - 1] == 0 && co[i][j] == 0)
				{
					sum += pow(10, su);
				}
				else if (co[i][j - su - 1] != 0 && co[i][j] != 0)
				{
					if (su == 5)
						sum += 100000;
				}
				else
				{
					if (su == 5)
						sum += 100000;
					else
						sum += pow(10, su - 1);

				}
				su = 0;
			}
			else
				su = 0;
		}
	for (su = 0, i = 0; i < 20; i++)              //竖
		for (j = 0; j < 21; j++)
		{
			if (co[j][i] == a)
				su++;
			else if (su > 1)
			{
				if (co[j - su - 1][i] == 0 && co[j][i] == 0)
				{
					sum += pow(10, su);
				}
				else if (co[j - su - 1][i] != 0 && co[j][i] != 0)
				{
					if (su == 5)
						sum += 100000;
				}
				else
				{
					if (su == 5)
						sum += 100000;
					else
						sum += pow(10, su - 1);
				}
				su = 0;
			}
			else
				su = 0;
		}
	for (su = 0, i = -19; i < 20; i++)              //╱
		for (j = i, k = 19; j < 20; j++, k--)
			if (j >= 0 && j < 20 && k >= 0 && k < 20)
			{
				if (co[j][k] == a)
					su++;
				else if (su > 1)
				{
					if (co[j - su - 1][k + su + 1] == 0 && co[j][k] == 0)
					{
						sum += pow(10, su);
					}
					else if (co[j - su - 1][k + su + 1] != 0 && co[j][k] != 0)
					{
						if (su == 5)
							sum += 100000;
					}
					else
					{
						if (su == 5)
							sum += 100000;
						else
							sum += pow(10, su - 1);
					}
					su = 0;
				}
				else
					su = 0;
			}
	for (su = 0, i = -19; i < 20; i++)                    //╲
		for (j = i, k = 0; j < 20; j++, k++)
			if (j >= 0 && j < 20 && k >= 0 && k < 20)
			{
				if (co[j][k] == a)
					su++;
				else if (su > 1)
				{
					if (co[j - su - 1][k - su - 1] == 0 && co[j][k] == 0)
					{
						sum += pow(10, su);
					}
					else if (co[j - su - 1][k - su - 1] != 0 && co[j][k] != 0)
					{
						if (su == 5)
							sum += 100000;
					}
					else
					{
						if (su == 5)
							sum += 100000;
						else
							sum += pow(10, su - 1);
					}
					su = 0;
				}
				else
					su = 0;
			}
	if (n == 1 && a == 1)
		return sum - score(2, co, 2);
	else if (n == 1 && a == -1)
		return sum - score(1, co, 2);
	else if (n == 2)
		return sum;
}


int jdgen(int co[size][size], int x, int y, int n)
//判断x，y坐标是否可生成棋子，可以返回1，否则返回0,n为1，判断内侧，为2，判断外侧
{
	int i, j;
	int sum = 0;
	if (n == 1)
	{
		for (i = x - 1; i < x + 2; i++)
			for (j = y - 1; j < y + 2; j++)
				if ((i > 0 && j > 0 && i < size && j < size) && (co[i][j] == 1 || co[i][j] == -1))
					sum = 1;
	}
	else
	{
		for (i = x - 2; i < x + 3; i += 2)
			for (j = y - 2; j < y + 3; j += 2)
				if ((i > 0 && j > 0 && i < size && j < size) && (co[i][j] == 1 || co[i][j] == -1))
					sum = 1;
	}
	return sum;
}

typedef struct
{
	int data;
	int Alpha;
	int Beta;
	int X;
	int Y;
}Tree;

int minMax(int co[size][size], int deep, int a, int Alpha, int Beta)
//分数传递,a为1表示白棋，为2表示黑棋,调用时Alpha，Beta赋为NGIF,PTIF
{
	int i, j;
	int c[size][size];
	int minmax;
	int n = 1;
	Tree tree;
	tree.data = NGIF;//负无穷
	tree.Alpha = Alpha;
	tree.Beta = Beta;
	tree.X = 0;
	tree.Y = 0;
	
	a = -a;//交换黑白子
	if (deep > 0)
	{
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				if (co[i][j] == 0 && jdgen(co, i, j, 1) && tree.Alpha < tree.Beta)
				{
					memcpy(c, co, sizeof(int) * 15 * 15);
					c[i][j] = a;
					minmax = minMax(c, deep - 1, a, tree.Alpha, tree.Beta);
					if (deep % 2 == 0)
					{
						if (n == 1)
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Alpha < minmax)
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
					else
					{
						if (n == 1)
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Beta > minmax)
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
				}
			}
		for (i = 0; i < size; i++)
			for (j = 0; j <size; j++)
			{
				if (co[i][j] == 0 && jdgen(co, i, j, 2) && tree.Alpha < tree.Beta)
				{
					memcpy(c, co, sizeof(int) * 400);
					c[i][j] = a;
					minmax = minMax(c, deep - 1, a, tree.Alpha, tree.Beta);
					if (deep % 2 == 0)
					{
						if (tree.Alpha < minmax)
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
					else
					{
						if (tree.Beta > minmax)
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
				}
			}
		X1 = tree.X;
		Y1 = tree.Y;
		return tree.data;
	}
	else
	{
		return score(a, co, 1);
	}
}

ChessPos consider() {
	int deep = 4;//AI搜索深度
	chesspos* maxscorepos = {};
	static int n = 0;
	int i, j;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			chessmap[i][j] = 0;
			minMax(chessmap, deep, 2, NGIF, PTIF);
			maxscorepos->x = X1;
			maxscorepos->y = Y1;
			return *maxscorepos;

		}
	}
}
int* computer(int x)
{
	int i, j;
	int* p = (int*)malloc(2 * sizeof(int));
	static int n = 0;
	if (n == 0)
	{
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				n += chessmap[i][j];
		if (n == 0)
		{
			p[0] = 9;
			p[1] = 9;
			return p;
		}
		n++;

	}
	minMax(chessmap, x, 2, NGIF, PTIF);
	p[0] = X1;
	p[1] = Y1;
	return p;
}
