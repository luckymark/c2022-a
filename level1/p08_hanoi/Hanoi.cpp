# define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

void move(char A, char C, int n)
{
	printf("把第%d个圆盘从%c--->%c\n", n, A, C);
}

void HanoiTower(char A, char B, char C, int n)
{
	if (n == 1)
	{
		move(A, C, n);
	}
	else
	{
		HanoiTower(A, C, B, n - 1);
		move(A, C, n);
		HanoiTower(B, A, C, n - 1);
	}
}

int main()
{
	int n = 0;
	printf("输入A柱子上的圆盘个数：");
	scanf("%d", &n);
	HanoiTower('A', 'B', 'C', n);
	return 0;
}