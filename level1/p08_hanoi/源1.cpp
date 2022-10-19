#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
void hanoi(char a, char b, char c, int n)
{
	if (n == 1)
	{
		printf("%c>>>>>%c\n", a, c);
	}
	else
	{
		hanoi(a, c, b, n - 1);
		hanoi(a, b, c, 1);
		hanoi(b, a, c, n - 1);
	}
}

int main()
{
	char a = 'A', b = 'B', c = 'C', d;
	hanoi(a, b, c, 3);

}