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
			printf("��������");
			return 0;
		}
	}
	printf("��");
	return 0;
}