#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void Hanio(int n, char A, char B, char C)
{
	if (1 == n)
		printf("%c->%c\n", A, B);
	else
	{
		Hanio(n - 1, A, C, B);
		printf("%c->%c",A , B);
		Hanio(n - 1, B, A, C);
	}
}
int main()
{
	int n = 0;
	scanf_s("%d", &n);
	Hanio(n, 'A', 'B', 'C');
	return 0;
}
