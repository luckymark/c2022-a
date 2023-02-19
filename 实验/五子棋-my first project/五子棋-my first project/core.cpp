#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include"stack.h"
#include"game.h"
#include"core.h"

Stack* pStackFirst = createStack(3);

int max(int a, int b)
{
	return a > b ? a : b;
}
int min(int a, int b)
{
	return a < b ? a : b;
}

//检测距离较远的点
int JudgeEmpty(int(*p)[15],int y,int x)
{
	int helparr[19][19] = {
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//1
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//2
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//5
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//10
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//15
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} //19
	};
	int count = 0;

	//为了检测距离太远的点做的准备
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			helparr[a + 2][b + 2] = p[a][b];
		}
	}
	for (int a = y; a < 5+y; a++)
	{
		for (int b = x; b < 5+x; b++)
		{
			if (helparr[a][b] == 0 || helparr[a][b] == 3)
			{
				count++;
			}
		}
	}
	//如果周围两圈都没有棋子，则判定为不合适
	if (count >= 24)
		return 1;
	else
		return 0;
}

//电脑先手深度计算(极大极小值搜索)
Stack* SearchFirst(int depth,int p[15][15],Node*CutLeaves)
{
	int Xhelp = 0, Yhelp = 0;
	int help = INT_MIN;
	int MAXgrade = INT_MIN;//传递最大分数值
	int MINgrade = INT_MAX;//传递最小分数值
	int copyarr[15][15];//传递数组值
	
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			copyarr[a][b] = p[a][b];
		}
	}

	switch (depth)
	{
	//奇数层为min层，偶数层为max层
	case 1:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//有棋就跳过
					continue;
				if (JudgeEmpty(copyarr, a, b))//距离太远也要跳过
					continue;
				copyarr[a][b] = 2;
				MINgrade = min(MINgrade, calculation(copyarr, 先手));
				copyarr[a][b] = 0;
			}
		}
		push(pStackFirst, MINgrade);
		return pStackFirst;
	case 2:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//有棋就跳过
					continue;
				if (JudgeEmpty(copyarr, a, b))//距离太远也要跳过
					continue;
				copyarr[a][b] = 1;
				pStackFirst = SearchFirst(depth - 1, copyarr, CutLeaves);
				copyarr[a][b] = 0;
				MAXgrade = max(MAXgrade, pop(pStackFirst));

				//剪枝
				if (MAXgrade > CutLeaves->beta)
					goto Exit;
			}
		}
		Exit:
		push(pStackFirst, MAXgrade);
		return pStackFirst;
	case 3:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//有棋就跳过
					continue;
				if (JudgeEmpty(copyarr, a, b))//距离太远也要跳过
					continue;
				copyarr[a][b] = 2;
				SearchFirst(depth - 1, copyarr, CutLeaves);
				copyarr[a][b] = 0;
				MINgrade = min(MINgrade, pop(pStackFirst));

				//剪枝
				CutLeaves->beta = MINgrade;
				if (MINgrade < CutLeaves->alpha)
					goto exit;
			}
		}
		exit:
		push(pStackFirst, MINgrade);
		return pStackFirst;
	case 4:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//有棋就跳过
					continue;
				if (JudgeEmpty(copyarr, a, b))//距离太远也要跳过
					continue;
				copyarr[a][b] = 1;
				SearchFirst(depth - 1, copyarr, CutLeaves);
				copyarr[a][b] = 0;
				help = pop(pStackFirst);
				if (help > MAXgrade)
				{
					MAXgrade = help;
					Xhelp = b;
					Yhelp = a;
				}

				//剪枝
				CutLeaves->alpha = MAXgrade;
			}
		}
		push(pStackFirst, Xhelp);
		push(pStackFirst, Yhelp);  //先传横坐标x，再传纵坐标y
		return pStackFirst;
	default:
		printf("算力还没有达到这种程度！\a\n");
		exit(0);
	}
}

//电脑后手深度计算(极大极小值搜索)
Stack* SearchSecond(int depth, int(*p)[15],Node*CutLeaves)
{
	int copyarr[15][15];
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			switch (p[a][b])
			{
			case 0:
				copyarr[a][b] = 0;
				break;
			case 1:
				copyarr[a][b] = 2;
				break;
			case 2:
				copyarr[a][b] = 1;
				break;
			default:printf("SearchSecond数组转换错误！\n\a");
				exit(0);
			}
		}
	}
	return SearchFirst(depth, copyarr, CutLeaves);//黑白棋转换
}

Stack* AIcomputer(int (* p)[15], Computertype computertype)
{
	Node alpha_beta = { INT_MIN,INT_MAX };
	Node* CutLeaves = &alpha_beta;
	//前端界面和后端算法的通道
	if (computertype == 1)            //判断电脑先手（玩家后手）
		return SearchFirst(4, p, CutLeaves);
	else                              //判断电脑后手（玩家先手）
		return SearchSecond(4, p, CutLeaves);
}
//电脑下棋