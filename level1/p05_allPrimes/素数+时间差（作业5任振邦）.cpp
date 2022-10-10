#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
int main()
{
	//第五题
	double time = 0;
	clock_t start, end;
	start = clock();
	printf("2\n");
	for (int num = 2; num < 1000; num++)
	{
		for (int i = 2; i < num; i++)
		{
			if (num % i == 0)
			{
				break;
			}
			if (i == num - 1)
			{
				printf("%d\n", num);
			}

		}
	}
	end = clock();
	time = end - start;
	printf("花费的时间为%lf", time);
	system("pause");
	return 0;
}
