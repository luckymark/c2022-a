#include<stdio.h>
#include"sushu.h"
void issushu(int n)                           //第二个作业
{
	if (n == 1)
	{
		printf("1不是一个素数\n");
	}
	else if (n == 2)
	{
		printf("2是一个素数\n");
	}
	else
	{
		if (amsushu(n))
		{
			printf("%d是一个素数\n", n);
		}
		else
		{
			printf("%d不是一个素数\n", n);
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