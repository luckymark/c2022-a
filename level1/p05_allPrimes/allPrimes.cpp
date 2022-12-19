#include<stdio.h>
#include<time.h>
int main() {
	int i;
	for (i = 2;i <= 1000;i++)
	{
		int isPrime = 1;
		int k;
		for (k = 2;k < i - 1;k++) {
			if (i % k == 0) {
				isPrime = 0;
				break;
			}
		}
		if (isPrime) {
			printf("%d ", i);
		}
	}
	printf("\nTime used = %.2f\n", (double)clock() / CLOCKS_PER_SEC);
	return 0;
}

