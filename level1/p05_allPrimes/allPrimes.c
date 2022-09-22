#include<stdio.h>
#include<time.h>
int main()
{
	int prime[1001];
	int maxNum = 1000, primeLen = 0;
	clock_t t1, t2;
	t1 = clock();
	for (int i = 2; i <= maxNum; i++)
	{
		int isPrime = 1;
		for (int j = 0; j < primeLen; j++) {
			if (i % prime[j] == 0) {
				isPrime = 0;
				break;
			}
		}
		if (isPrime) {
			printf("%d ", i);
			prime[primeLen] = i;
			primeLen++;
		}
	}
	t2 = clock();
	printf("\n%dms", t2 - t1);
	return 0;
}