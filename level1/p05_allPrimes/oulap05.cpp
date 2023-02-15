#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main()
{
	int count = 0;
	int numbs[1001], prime[1001], i;
	int* p = numbs;
	int n = 100;
	
	for (i = 0; i < 1001; i++)
		numbs[i] = 1;
	p[0] = p[1] = 0;
	float t1 = clock();
	for (i = 2; i < 1001; i++) {
		{
			prime[++count] = i;
			for (int j = 1; j <= count && prime[j] <= 1001 / i; j++)
			{
				numbs[prime[j] * i] = 0;
				if (i % prime[j] == 0)
					break;
			}
		}
	}
	float t2 = clock();
	for (i = 0; i < 1001; i++) {
		if (numbs[i])
			printf("%d\n", i);
	}

	printf("%f", t2 - t1);
	system("pause");
}







