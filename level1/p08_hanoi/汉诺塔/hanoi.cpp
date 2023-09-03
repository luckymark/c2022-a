#include<stdio.h>
void hanoi(int n, char ch1, char ch2, char ch3);//��ch1�ϵ�ͨ��ch2�ƶ���ch3
void move(char ch4, char ch5);//��ch4�ƶ���ch5
#define number 3
int main()
{
	char ch1 = 'A', ch2 = 'B', ch3 = 'C';
	hanoi(number, ch1, ch2, ch3);
	return 0;
}
void hanoi(int n, char ch1, char ch2, char ch3)
{
	if (1 == n)
		move(ch1, ch3);
	else
	{
		hanoi(n - 1, ch1, ch3, ch2);
		move(ch1, ch3);
		hanoi(n - 1, ch2, ch1, ch3);
	}
}
void move(char ch4, char ch5)
{
	printf("%c -> %c\n", ch4, ch5);
}