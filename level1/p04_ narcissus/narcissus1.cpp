#include<stdio.h>
# define _CRT_SECURE_NO_WARNINGS 1
int main()
{
	int num = 0,sum=0,bp=0;
	for (num = 100; num < 1000; num++)
	{
		bp = num;
		while (bp > 0)
		{
			sum += (bp % 10) * (bp % 10) * (bp % 10);
			bp /= 10;
		}
		if (num == sum)
			printf("%d是水仙花数\n", num);
		sum = 0;
	}
	return 0;
}