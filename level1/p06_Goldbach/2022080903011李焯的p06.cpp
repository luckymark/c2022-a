#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int numbs[101];

void isPrime();


int main()
{
	int son;
	isPrime();
	for (int i = 4; i < 101; i += 2)
	{
		for (son = 2; son <= i / 2; son++)
		{
			if (numbs[son] && numbs[i - son])
			{
				printf("%d=%d+%d\n", i, son, i - son);
				//break;   根据是否需要所有结果删减
			}
		}
	}
	system("pause");

}void isPrime()
{
	int count = 0;
	int prime[101], i;
	int n = 100;
	for (i = 0; i < 101; i++)
		numbs[i] = 1;
	numbs[0] = numbs[1] = 0;
	float t1 = clock();
	for (i = 2; i < 101; i++) {
		{
			prime[++count] = i;
			for (int j = 1; j <= count && prime[j] <= 101 / i; j++)
			{
				numbs[prime[j] * i] = 0;
				if (i % prime[j] == 0)
					break;
			}
		}
	}
}
