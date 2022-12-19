#include<stdio.h>


int main() {
	int i;
	int k;
	int t = 0;
	int Prime[25];
	int N;
	int a, b, c;
	const int NUMBER = 24;
	int d=0;
	for (i = 2;i <= 100;i++)
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
			Prime[t] = i;
			t++;
		}
		
	}
	for (N = 6;N <= 100; N++) {
		d = 0;
		for (a = 0;a <= NUMBER;a++) {
			for (b = a;b <= NUMBER;b++) {
				for(c=b;c<=NUMBER;c++)
					if (N == Prime[a] + Prime[b] + Prime[c]) {
						d = 1;
						break;
					}
			}
		}

		if (d != 1)
			printf("error");
		else printf("YES ");

	}
	
		return 0;
	
}