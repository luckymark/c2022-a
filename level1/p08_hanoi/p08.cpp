#include <stdio.h>
#include <stdlib.h>

void hanio(int, int, int, int);
void hanio(int n, int frome, int by, int to)
{
	if (n == 1)
		printf("%c->%c\n", frome, to);
	else
	{
		hanio(n - 1, frome, to, by);
		printf("%c->%c\n", frome, to);
		hanio(n - 1, by, frome,to);
	}
}
int main()
{
	int n = 64;
	hanio(n, 'A', 'B', 'C');
	system("pause");
}