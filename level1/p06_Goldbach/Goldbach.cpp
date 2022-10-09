#include<stdio.h>
#include<math.h>
# define _CRT_SECURE_NO_WARNINGS 1
int isprime(int num)
{
	int i = 0, est = 1;
	for (i = 2; i < num; i++)
	{
		if (num % i == 0)
		{
			est = 0;
			break;
		}
	}
	if (est == 1)
		return 1;
	else
		return 0;
}
void goldbach( int input)
{
	int num1 = 0, num2 = 0;
	for (num1=2;num1 < input; num1++)
	{
		if (isprime(num1))
		{
			num2 = input - num1;
			if (isprime(num2))
			{
				printf("%d=%d+%d", input, num1, num2);
				break;
			}
		}
	}
}
	int main()
	{
		int input = 0, est1 = 0;
		printf("����һ�����ڶ���С�ڵ���100��ż��\n");
		while (1)
		{
			scanf("%d", &input);
			if ((input > 2 && input <= 100) && input % 2 == 0)
			{
			    goldbach( input);
				break;
			}
			else
				printf("����������\n");
		}
		return 0;
	}