#include<stdio.h>
int main()
{
	int i = 1;
	int sum = 0;
	while(i <= 100)
	{
		if((i%7 == 0)|| (i%10 == 7))
		{
			printf("%d ",i);
			sum = sum + i;
		}
		i++;
	} 
	printf("%d",sum);
	return 0;
}
