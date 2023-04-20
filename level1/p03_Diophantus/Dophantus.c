#include<stdio.h>
int main()
{
	for (double i = 0; i < 100; i++)
	{
		if (i / 6 + i / 12 + i / 7 + 5 + 4 == i / 2)
		{
			printf("%.2lf", i);
			break;
		}
	}
	return 0;
}