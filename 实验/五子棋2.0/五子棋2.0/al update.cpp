#include "all.h"
extern int Chess[ROW][LINE];
extern int X;
extern int Y;

typedef struct 
{
	int X;
	int Y;
	int Beta;
	int Alpha;
	int data;
}Tree;


int Minmax(int Chess[ROW][LINE], int Alpha, int Beta, int cur_color, int depth)
{
	int n = 0;
	int minmax = 0;
	int copy[ROW][LINE];
	int next_color;
	Tree tree;
	tree.Alpha = Alpha;
	tree.Beta = Beta;
	tree.data = NGIF;
	tree.X = 0;
	tree.Y = 0;//初始化数据
	if (2 == cur_color)//如果是电脑
		next_color = 1;
	else
		next_color = 2;
	if (2 == depth)//递归的结束条件
	{
		return score(cur_color, Chess, 1);//将局面赋值到子叶上
	}
	else
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < LINE; j++)
			{
				if (Chess[i][j] == 0 && tree.Alpha < tree.Beta)//剪枝的条件
				{
					memcpy(copy,Chess, sizeof(int) * ROW * LINE);
					copy[i][j] = cur_color;
					minmax = Minmax(copy, tree.Alpha, tree.Beta, next_color, depth+1);
					if (0 == depth % 2)//max层
					{
						if (0 == n)//每一层在只有一个子叶的时候直接对节点赋值
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Alpha < minmax)//比较最大值alpha并进行更新
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;//比较每一层中最好的点，最后回到最后开始
						}
					}
					else//对min层进行同样操作
					{
						if (0 == n)//每一层在只有一个子叶的时候直接对节点赋值
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Beta > minmax)//比较最小值β并进行更新
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;//比较每一层中最好的点，最后回到最后开始
						}
					}
				}
			}
		}
	}
	X = tree.X;
	Y = tree.Y;
	return tree.data;
}//剪枝算法自我理解就是从子叶中得到数据依次往父辈传递，最后将不满足条件的地方剪枝，和我之前的ai思路不一样，之前是对每一个落子进行评估，这个是对整个局面进行评估


int score(int a, int co[ROW][LINE], int n)
//评分,a为1表示人，为2表示电脑,n为1避免递归调用出现死循环
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
	else if (n == 1 && a == 2)
		return sum - score(1, co, 2);
	else if (n == 2)
		return sum;
}//这个是用别人的局面评估函数