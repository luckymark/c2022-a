#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>

int cal = 0,cal2=0;

int main(void)
{
	printf("All primes between 2 and 1000 are:\n");
	SYSTEMTIME time1, time2;
	GetLocalTime(&time1);

	for (int num=2;num<=1000;num++)
	{
		int i = 2;
		for (i = 2; i <= float(sqrt(num)); i++)
		{
			if (num % i == 0)
			{
				break;
			}
		}
		if (i > float(sqrt(num)))
		{
			printf("%d\n", num);
		}
	}

	GetLocalTime(&time2);
	cal = time2.wMilliseconds - time1.wMilliseconds;
	cal2= time2.wSecond - time1.wSecond;
	if (cal2 == 1)
	{
		cal += 1000;
	}
	printf("\n计算时间为%dms\n", cal);

	return 0;
}

//欧拉筛？