#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main()
{
	int num,i;

	printf("请输入一个正整数：");
	scanf_s("%d", &num);

	while (num <= 0)
	{
		printf("请输入一个正整数：");
		scanf_s("%d", &num);
	}
		
	if (num == 1) 
	{
		printf("1不是一个素数");
		exit(0);
	}

	for (i = 2; i <= float(sqrt(num)); i++)
	{
			if (num % i == 0)
			{
				printf("%d不是一个素数\n", num);
				break;
			}
	}
	if (i > float(sqrt(num)))
	{
			printf("%d是一个素数\n", num);
	}

	exit(0);
}