#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int main()
{
	int step = 0,a = 1;
	while (1)
	{
		step += a;
		if (step == 100||step == 0)//120一般是屏幕最右端坐标
		{
			a = -a;
		}//反向
		for (int i = 0; i <= step; i++)//循环次数增加，每次输出空格变多，字母向左或右移动
		{
			printf(" ");
		}
		printf("hallo world");
		Sleep(20);
		system("cls");//清屏，
	}
	return 0;
}