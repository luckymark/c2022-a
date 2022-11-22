#include<stdio.h>

void print(char x, char y)
{
	printf("%c------>%c\n", x, y);
}

void hanoi(int n, char a, char b, char c)
{
	if (n == 1)
	{
		print(a, c);
	}
	else
	{
		hanoi(n - 1, a, c, b);
		print(a, c);
		hanoi(n - 1, b, a, c);
	}
}

int main()
{
	int n;
	printf("Input n:");
	scanf("%d", &n);
	hanoi(n, 'A', 'B', 'C');
}
