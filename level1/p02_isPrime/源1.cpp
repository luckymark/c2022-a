#include<stdio.h>
#include<math.h>
int zhishu(int b, int i) {
	i = 2;
	for (i; i <= sqrt(float(b)); i++) {
		if (b % i == 0) {
			break;
		}
		else
			continue;
	}
	if (i < sqrt(float(b))) {
		printf("no");
	}
	else
		printf("yes");
	return 0;
}
int main() {
	int a, n = 2, c;
	c = scanf_s("%d", &a);
	if (a == 0)
	{
		printf("error");
	}
	else if (a <= 3) {
		printf("error");
	}
	else
	{
		zhishu(a, n);
	}
}

