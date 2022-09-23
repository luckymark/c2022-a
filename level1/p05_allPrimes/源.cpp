#include <stdio.h>
#include <time.h>
int isprime(int x) {
	int flag = 1;
	if (x > 2) {
		for (int i = 2; i < x; i++) {
			if (x % i == 0) flag = 0;
			if (!flag) break;
		}
	}
	return flag;
}
int main() {
	int start, end;
	start = clock();
	printf("2 ");
	for (int i = 3; i <= 1000; i+=2) {
		if (isprime(i)) printf("%d ", i);
	}
	end = clock();
	printf("\nthe time you used:%d", end - start);
	return 0;
}