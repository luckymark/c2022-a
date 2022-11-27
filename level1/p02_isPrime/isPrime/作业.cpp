#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int n,i=3;
	scanf_s("%d", &n);
	if (n <= i)
		printf("error");
	while (i <= sqrt((double)n))
	{
		if (n % i == 0)
		{
			printf("no");
			break;
		}
		i++;
	}
	if (i > sqrt((double)n))
		printf("yes");
	return 0;

}