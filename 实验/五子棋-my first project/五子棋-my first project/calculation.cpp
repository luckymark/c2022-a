#include<stdio.h>
#include"core.h"
//主要是分数的计算（先尝试使用六元组）
int sixpart[6] = { 0,0,0,0,0,0 };
int fivepart[5] = { 0,0,0,0,0 };

//做评估函数
int calculation(int arr[15][15], Computertype computertype)
{
	int helparr[15][15] ;
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			helparr[a][b] = arr[a][b];
		}
	}
	if (computertype == 1)
	{
		int grade = 1;
		//横向搜索
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 10; b++)
			{
				int d = b;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[a][d++];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//纵向搜索
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 10; b++)
			{
				int d = b;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[d++][a];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//斜向搜索
		for (int b = 0; b < 10; b++)
		{
			for (int a = b; a < 10; a++)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d++];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		for (int a = 0; a < 10; a++)
		{
			for (int b = a; b < 10; b++)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d++];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//两次中间重复算了对角线，需要减去
		for (int a = 0; a < 10;a++)
		{
			for (int c = 0, d = a; c < 6; c++,d++)
			{
				sixpart[c] = helparr[d][d];
			}
			grade -= judge_sixBlack(sixpart);
			grade += judge_sixWhite(sixpart);
		}
		//次斜向搜索
		for (int b = 14; b > 4; b--)
		{
			for (int a = 14-b; a < 10; a++)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d--];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		for (int a = 0; a < 10; a++)
		{
			for (int b = 14-a; b > 4; b--)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d--];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//两次中间重复算了对角线，需要减去
		for (int a = 0; a <10; a++)
		{
			for (int c = 0, d = a; c < 6; c++, d++)
			{
				sixpart[c] = helparr[d][14 - d];
			}
			grade -= judge_sixBlack(sixpart);
			grade += judge_sixWhite(sixpart);
		}
		//开始写单独的四条棋链
		//第一条
		fivepart[0] = helparr[0][4];
		fivepart[1] = helparr[1][3];
		fivepart[2] = helparr[2][2];
		fivepart[3] = helparr[3][1];
		fivepart[4] = helparr[4][0];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);
		//第二条
		fivepart[0] = helparr[10][0];
		fivepart[1] = helparr[11][1];
		fivepart[2] = helparr[12][2];
		fivepart[3] = helparr[13][3];
		fivepart[4] = helparr[14][4];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);
		//第三条
		fivepart[0] = helparr[0][10];
		fivepart[1] = helparr[1][11];
		fivepart[2] = helparr[2][12];
		fivepart[3] = helparr[3][13];
		fivepart[4] = helparr[4][14];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);
		//第四条
		fivepart[0] = helparr[10][14];
		fivepart[1] = helparr[11][13];
		fivepart[2] = helparr[12][12];
		fivepart[3] = helparr[13][11];
		fivepart[4] = helparr[14][10];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);

		return grade;
	}
	else 
	{
		//黑白棋交换，直接套用代码就行了
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (helparr[a][b] == 0)
					continue;
				else if (helparr[a][b] == 1)
				{
					helparr[a][b] = 2;
				}
				else {
					helparr[a][b] = 1;
				}
			}
		}
		return calculation(helparr, 先手);
	}
}
//黑棋为1，白棋为2

//接下来开始判断棋形
int judge_sixBlack(int six[6])//判断黑色棋形
{
	//棋形有很多种，相信大家都能看懂英文，就不一一解释了
	if (six[0] == 1 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1||
		six[5] == 1 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1)
	{
		return linkfive;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1 && six[5] == 0)
	{
		return livefour;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1 && six[5] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1 && six[5] == 0)
	{
		return dashfour+1;
	}
	else if (six[0] == 1 && six[1] == 0 && six[2] == 1 && six[3] == 1 && six[4] == 1 ||
		six[0] == 1 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 ||
		six[0] == 1 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1)
	{
		return dashfour;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 0)
	{
		return livethree;
	}
	else if (six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 2||
		six[0] == 1 && six[1] == 0 && six[2] == 0 && six[3] == 1 && six[4] == 1||
		six[0] == 1 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 && six[5] == 2||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1 && six[5] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 2 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1 && six[5] == 0)
	{
		return sleepthree;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 0)
	{
		return livetwo;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 0||
		six[0] == 2 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1 && six[5] == 2)
	{
		return sleeptwo;
	}
	else if (six[0] == 0 && six[1] == 0 && six[2] == 1 && six[3] == 0 && six[4] == 0)
	{
		return one;
	}
	else
	{
		return 0;
	}
}

int judge_sixWhite(int six[6])//判断白色棋形
{
	for (int a = 0; a < 6; a++)
	{
		if (six[a] == 1)
		{
			six[a] = 2;
		}
		else if (six[a] == 2)
		{
			six[a] = 1;
		}
		else continue;//这里只剩下等于0一种情况，让它不变就行了
	}
	//黑白棋转换，直接套用前面代码
	return judge_sixBlack(six);
}

//斜边有四条棋链六元组搜索不到，故单独判断
int judge_fiveBlack(int five[5])
{
	if (five[0] == 0 && five[1] == 0 && five[2] == 0 && five[3] == 0 && five[4] == 0)
	{
		return 0;
	}
	else if (five[0]==2||five[1]==2 || five[2] == 2 || five[3] == 2 || five[4] == 2)
	{
		return deadspot;
	}
	else if (five[0] == 1 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 1)
	{
		return linkfive;
	}
	else if (five[0] == 0 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 1 ||
		five[0] == 1 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 0)
	{
		return dashfour;
	}
	else if (five[0] == 0 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 0||
		five[0] == 1 && five[1] == 1 && five[2] == 1 && five[3] == 0 ||
		five[1] == 0 && five[2] == 1 && five[3] == 1 && five[4] == 1)
	{
		return sleepthree;
	}
	//其实在这个特殊位置我觉得如果不是连五的话意义不大，后面就不写了
	else
	{
		return 0;
	}
}
//如法炮制，函数嵌套调用
int judge_fiveWhite(int five[5])
{
	for (int a = 0; a < 5; a++)
	{
		if (five[a] == 0)
		{
			continue;
		}
		else if (five[a] == 1)
		{
			five[a] = 2;
		}
		else
		{
			five[a] = 1;
		}
	}
	return judge_fiveBlack(five);
}
