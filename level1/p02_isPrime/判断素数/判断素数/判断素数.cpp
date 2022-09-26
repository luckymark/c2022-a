#include<stdio.h>
#include<math.h>
int issushu(int n)                           //第二个作业
{
	for (int a = 2; a <= ceil(n / 2.0); a++)
	{
		if (n % a == 0)
			return 0;
	}
	return 1;
}
int main()
{
	int n;
	printf("请输入一个正整数\n");
	scanf_s("%d", &n);
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
		if (issushu(n))
		{
			printf("%d是一个素数\n", n);
		}
		else
		{
			printf("%d不是一个素数\n", n);
		}
	}
	return 0;
}