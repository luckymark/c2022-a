#include<stdio.h>
void cprime(int a[]);
int main(void) {
	int n[1005];
	int a = 0, b = 0, c = 0;
	n[0] = 2;
	cprime(n);
	for (int i = 6; i <= 1000; ) {
		int sum = 0;
		for (a = 0; a < 250; a++) { 
			for (b = 0; b < 250; b++) {
				for (c = 0; c < 250; c ++) {
					if (i == (n[a] + n[b] + n[c]) ) {
						sum = 1;
						i++;
						break;
					}
				}
			}
		}

		if (sum == 0) {
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;





}
void cprime(int a[]) {
	int x = 3;
	int sum;
	for (int i = 0; i < 250; x++) {
		sum = 1;
		for (int n = 0; n <= i; n++) {
			if (x % a[n] == 0) {
				sum = 0;
				break;
			}
		}
		if (sum == 1) {
			a[++i] = x;
		}
	}
}

