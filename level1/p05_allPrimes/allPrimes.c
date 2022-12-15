#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
int judge(int i)
{
	for (int x = 2; x <= sqrt((double)i); x++)
	{
		if (i % x == 0)
			return 1;
	}
	return 0;
}
int main()
{
	clock_t start, finish;
	start = clock();
	for (int i = 2; i < 1000; i++)
	{
		if (judge(i)==0)
			printf("%d\n", i);
	}
	finish = clock();
	printf("time:%lf secs\n", (double)(finish - start) / CLOCKS_PER_SEC);
	return 0;
}