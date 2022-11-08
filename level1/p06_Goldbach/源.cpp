//任一大于2的偶数都可写成两个质数之和
#include <stdio.h>
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
	int flag = 0, x = 1, p[50] = { 0 };
	p[0] = 2;
	for (int i = 3; i < 100; i++) {
		if (isprime(i)) {
			p[x] = i;
			x++;
		}
	}
	for (int k = 4; k <= 100; k += 2) {
		flag = 0;
		for (int i = 0; i < x-1; i++) {
			for (int j = x-1; j >= i; j--) {
				if (p[i] + p[j] < k) break;
				if (p[i] + p[j] == k) {
					//printf("%d=%d+%d\n", k, p[i], p[j]);
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		if (flag == 0) break;
	}
	if (!flag) printf("FALSE");
	else printf("TURE");
	return 0;
}