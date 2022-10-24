//将n个盘子借助B，从A移到C

#include<stdio.h>
void move(char a, char b);
void hanoi(int n, char x, char y, char z);

int main()
{
	int n;
	printf("请输入盘子的个数：");
	scanf_s("%d", &n);
	hanoi(n, 'A', 'B', 'C');
	return 0;
}

void move(char a, char b)
{
	printf("%c -> %c\n", a, b);
}

void hanoi(int n, char x, char y, char z)
{
	if (n == 1)
	{
		move(x, z);
	}
	else
	{
		hanoi(n - 1, x, z, y);
		move(x, z);
		hanoi(n - 1, y, x, z);
	}
}
