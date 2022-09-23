#include <stdio.h>
#include <math.h>
int main() {
	int n, flag = 1;
	scanf_s("%d",&n);
	if (n == 1) {
		flag = 0;
	}else {
		if (n == 2) flag = 1;
		else {
			for (int i = 2; i <= sqrt((double)n); i++) {
				if (n % i == 0)flag = 0;
				if (!flag) break;
			}
		}
	}
	if (flag==1) printf("%d是质数", n);
	else printf("%d不是质数",n);
	return 0;
}