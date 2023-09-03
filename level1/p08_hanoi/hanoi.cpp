#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void move(int from, int to);
void hanoi(int n, int from, int by, int to)
{
	if (n == 1)
	{
		move(from, to);
	}
	else
	{
		hanoi(n - 1, from, to, by);
		move(from, to);
		hanoi(n - 1, by,from, to);
	}
}
void move(int from, int to)
{
	printf("%c->%c\n", from, to);
}
int main()
{
	int n = 0;
	int A = 65, B=66, C=67;
	scanf_s("%d", &n);
	hanoi(n,A,B,C);


	system("pause");
	return 0;
}