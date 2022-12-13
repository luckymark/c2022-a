/*题目：奔跑的字母

 功能要求：

1. 在console上输出一个字母（或单词）
1. 使该字母或单词，按一定速度从左至右运动
1. 当遇到屏幕边界时反向运动*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
	int i,j;
	while (1)
	{
		for (i = 1; i <= 100; i++)
		{
			j = i;
			while (j--)
			{
				printf(" ");
			}
			printf("傻逼");
			Sleep(0.01);
			system("cls");
		}
		for (i = 100; i >= 1; i--)
		{
			j = i;
			while (j--)
			{
				printf(" ");
			}
			printf("傻逼");
			Sleep(0.01);
			system("cls");
		}
	}
	return 0;
}

