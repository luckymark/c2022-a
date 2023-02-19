#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void hanoi(int quantity,char a,char b,char c)
{
	if (quantity == 1)
	{
		printf("from %c to %c\n", a, c);
	}
	else {
		hanoi(quantity - 1, a, c, b);
		printf("from %c to %c\n", a, c);
		hanoi(quantity - 1, b, a, c);
	}
}

int main()
{
	int times;
	printf("please enter the quantity of round plates:\n");
	scanf("%d", &times);
	hanoi(times, 'A', 'B', 'C');
	return 0;
}