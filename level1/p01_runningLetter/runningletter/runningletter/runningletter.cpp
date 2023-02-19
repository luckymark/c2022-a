#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int main()                                      //第一个作业
{
	const int left = 0;
	const int right = 20;
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
		Sleep(10);
		system("cls");
	}
	return 0;
}