#include<stdio.h>
#include"sushu.h"
void issushu(int n)                           //�ڶ�����ҵ
{
	if (n == 1)
	{
		printf("1����һ������\n");
	}
	else if (n == 2)
	{
		printf("2��һ������\n");
	}
	else
	{
		if (amsushu(n))
		{
			printf("%d��һ������\n", n);
		}
		else
		{
			printf("%d����һ������\n", n);
		}
	}
	
}
int amsushu(int n)
{
	for (int a = 2; a <= ceil(n / 2.0); a++)
	{
		if (n % a == 0)
			return 0;
	}
	return 1;
}