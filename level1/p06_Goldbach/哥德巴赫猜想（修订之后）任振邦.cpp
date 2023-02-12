#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
int main()
{//哥德巴赫猜想的现代陈述为：任一大于5的整数都可写成三个质数之和。
	//1.把素数存储在一个数组当中
	int sum = 0;
	int sign = 1;
	int test = 0;
	int sushu[50] = { 0 };
	sushu[0] = 2;
	for (int num = 2; num < 100; num++)
	{
		for (int i = 2; i < num; i++)
		{
			if (num % i == 0)
			{
				break;
			}
			if (i == num - 1)
			{
				sushu[sign] = num;
				++sign;
			}

		}
	}
	//2.判断100内有几个素数
	for (int j = 0; j < 100; j++)
	{
		if (sushu[j] == 0)
		{
			break;
		}
		else
		{
			printf("%d\n", sushu[j]);
			sum++;
		}
	}
	printf("%d\n", sum);
	//3.验证5~100时哥德巴赫猜想成立
	for (int i = 6; i <= 100; i++)
	{
		for (int a = 0; a < sum; a++)//定义素数1
		{
			for (int b = 0; b < sum; b++)//定义素数2
			{
				for (int c = 0; c < sum; c++)//定义素数3
				{
					if (sushu[a] + sushu[b] + sushu[c] == i)
					{
						test++;
						goto FLAG;
					}
				}
			}
		}
	FLAG:;
	}
		printf("%d\n", test);
	if (test ==95)
	{
		printf("哥德巴赫猜想在100以内成立");
	}
	else
	{
		printf("哥德巴赫猜想不成立");
	}
	system("pause");
	return 0;
}