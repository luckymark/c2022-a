#include<stdio.h>
#include<math.h>
int main()
{
	int x,a;
	scanf_s("%d", &x);
	for (int i = 2; i <= sqrt(x); i++)
	{
		if (x % i == 0)
		{
			printf("不是素数");
			return 0;
		}
	}
	printf("是");
	return 0;
}