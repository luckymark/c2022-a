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
	tree.Y = 0;//��ʼ������
	if (2 == cur_color)//����ǵ���
		next_color = 1;
	else
		next_color = 2;
	if (2 == depth)//�ݹ�Ľ�������
	{
		return score(cur_color, Chess, 1);//�����渳ֵ����Ҷ��
	}
	else
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < LINE; j++)
			{
				if (Chess[i][j] == 0 && tree.Alpha < tree.Beta)//��֦������
				{
					memcpy(copy,Chess, sizeof(int) * ROW * LINE);
					copy[i][j] = cur_color;
					minmax = Minmax(copy, tree.Alpha, tree.Beta, next_color, depth+1);
					if (0 == depth % 2)//max��
					{
						if (0 == n)//ÿһ����ֻ��һ����Ҷ��ʱ��ֱ�ӶԽڵ㸳ֵ
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Alpha < minmax)//�Ƚ����ֵalpha�����и���
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;//�Ƚ�ÿһ������õĵ㣬���ص����ʼ
						}
					}
					else//��min�����ͬ������
					{
						if (0 == n)//ÿһ����ֻ��һ����Ҷ��ʱ��ֱ�ӶԽڵ㸳ֵ
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Beta > minmax)//�Ƚ���Сֵ�²����и���
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;//�Ƚ�ÿһ������õĵ㣬���ص����ʼ
						}
					}
				}
			}
		}
	}
	X = tree.X;
	Y = tree.Y;
	return tree.data;
}//��֦�㷨���������Ǵ���Ҷ�еõ������������������ݣ���󽫲����������ĵط���֦������֮ǰ��ai˼·��һ����֮ǰ�Ƕ�ÿһ�����ӽ�������������Ƕ����������������


int score(int a, int co[ROW][LINE], int n)
//����,aΪ1��ʾ�ˣ�Ϊ2��ʾ����,nΪ1����ݹ���ó�����ѭ��
{
	int i, j, k, l;
	int sum = 0, su = 0;
	for (i = 0; i < 20; i++)                //��
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
	for (i = 0; i < 20; i++)                  //��
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
	for (su = 0, i = 0; i < 20; i++)              //��
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
	for (su = 0, i = -19; i < 20; i++)              //�u
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
	for (su = 0, i = -19; i < 20; i++)                    //�v
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
}//������ñ��˵ľ�����������