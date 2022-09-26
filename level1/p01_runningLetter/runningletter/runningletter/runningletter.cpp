#include<stdio.h>
#include<stdlib.h>
int main()                                      //第一个作业
{
	const int left = 0;
	const int right = 120;
	int a = 1, b = 0;
	while (1)
	{
		b += a;
		if (b == left || b == right)
		{
			a = -a;
		}
		for (int c = 0; c < b; c++)
		{
			putchar(' ');
		}
		puts("$$$$");
		system("cls");
	}
	return 0;
}