//栈的操作，实现撤回功能
/*

typedef struct
{
	char str[1000];//最多支持1000步回退
	int top;
} Stack;
//判断栈是否为空
int IsEmpty(Stack& S)
{
	return (S.top == -1 ? 1 : 0);
}
//进栈
void Push(Stack& S, char ch)
{
	S.top++;
	S.str[S.top] = ch;
}
//出栈
int Pop(Stack& S, char& x)
{
	if (IsEmpty(S) == 1)
		return 0;
	x = S.str[S.top];
	S.top--;
	return 1;
}
//以上是栈的操作

//目的地的坐标
typedef struct node
{
	int x, y;
}Date;
typedef struct
{
	Date d[10];//最多十个目的地。
	int num;//个数。
}Destination;
//以上是目的地坐标的结构体

Destination D;

//找目的地
void des(int a[13][13])
{
	int i, j, k = 0;
	D.num = 0;
	for (i = 0; i < 13; i++)
		for (j = 0; j < 13; j++)
			if (a[i][j] == 3)
			{
				D.num++;
				D.d[k].x = i;
				D.d[k++].y = j;
			}
}
//以上找目的地坐标


//可以用结构体数组实现多个关卡
#include <conio.h>
struct MAP
{
	int x;
	int y;
};
struct MAP map[];

//怎么实现重来
//用easyx?

//动作制造 
int action(int a[13][13], Stack& S)
{
	char ch, x;
	/*找出人5或者8（）的位置*/
	
/*
int i, j;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (a[i][j] == 5 || a[i][j] == 8)
				break;
		}
		if (a[i][j] == 5 || a[i][j] == 8)
			break;
	}

	ch = _getch();
	switch (ch)
	{
		//撤回前一步
	case 'R':
		if (Pop(S, x) == 1)
		{
			//若上一步是向上 
			if (x == 'W' || x == 'w')
			{
				if (x == 'W')
				{
					a[i + 1][j] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i - 1][j] -= 4;
					a[i + 1][j] += 5;
					a[i][j] -= 1;
				}
			}
			//若上一步是向下 
			if (x == 'S' || x == 's')
			{
				if (x == 'S')
				{
					a[i - 1][j] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i + 1][j] -= 4;
					a[i - 1][j] += 5;
					a[i][j] -= 1;
				}
			}
			//若上一步是向左 
			if (x == 'A' || x == 'a')
			{
				if (x == 'A')
				{
					a[i][j + 1] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i][j - 1] -= 4;
					a[i][j + 1] += 5;
					a[i][j] -= 1;
				}
			}
			//若上一步是向右
			if (x == 'D' || x == 'd')
			{

				if (x == 'D')
				{
					a[i][j - 1] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i][j + 1] -= 4;
					a[i][j - 1] += 5;
					a[i][j] -= 1;
				}
			}
		}break;
		//以上是撤回功能 

*/