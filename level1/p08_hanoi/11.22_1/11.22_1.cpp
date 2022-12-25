#include<stdio.h>
void deducation(int n,char a,char b,char c);
void move(int n, char a, char b);

int main() 
{
	deducation(10, 'a', 'b', 'c');
}
void deducation(int n,char a,char b,char c)
{
	
	if (n == 1)
		move(n,a,c);
	else
	{
		deducation(n - 1, a, b, c);
		move(n, a, c);
		deducation(n - 1, b, c, a);
	}
}
void move(int n,char a,char b) {
	printf(" % c-> % c\n", a, b);
}