#include<stdio.h>
int Prime() {
	int n;
	scanf_s("%d", &n);
	int i;
	for (i = 2;i < n;i++)
		if (n % i == 0)
			break;
	if (i < n)
		printf("%d不是素数", n);
	else printf("%d是素数", n);
	return 0;
}
