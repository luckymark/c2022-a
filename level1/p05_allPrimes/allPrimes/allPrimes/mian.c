#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
int issushu(int n)                                 //第五个作业
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
	printf("2~1000中的所有素数：\n");
	clock_t before, after;
	before = clock();
	for (int a = 2; a <= 1000; a++)
	{
		if (issushu(a))
		{
			printf("%d ", a);
		}
	}
	puts("\n");
	after = clock();
	printf("所用时间为：");
	printf("%d毫秒\n", after - before);
	return 0;
}