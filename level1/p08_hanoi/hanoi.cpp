#include<stdio.h>

void layer(int n,char A,char B,char C)
{
	if (n == 1)
	{
		printf("%c -> %c\n", A, C);
	}
	else
	{
		layer(n - 1, A, C, B);
		printf("%c -> % c\n",A, C);
		layer(n-1,B,A,C);
	}
}

int main()
{
	char A = 'A', B = 'B', C = 'C';
	int N;
	scanf_s("%d", &N);
	layer(N,A,B,C);

	return 0;
}