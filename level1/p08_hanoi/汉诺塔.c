#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int n;
char a = 'A', b = 'B', c = 'C';
void move(char x, char y)
{
	printf("%c->%c\n", x, y);
}
void step(int m, char x, char y, char z)//x�ǳ�ʼ��y�Ǹ�����z������
{
	if (m == 1)
	{
		move(x, z);
	}
	else
	{
		step(m - 1, x, z, y);
		move(x, z);
		step(m - 1 , y, x, z);
	}
}




int main()
{
	printf("���뺺ŵ���Ĳ���:");
	scanf("%d", &n);
	step(n, a,b,c);
	return 0;
}