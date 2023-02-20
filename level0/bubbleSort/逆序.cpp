#include<stdio.h>
int main()
{
	int num;
	
	scanf("%d\t",&num);
	
	int aggre[num];
	
	for(int time=1;time<=num;time++)
	
	{
		scanf("%d",&aggre[time]);
	}
	
	printf("\n");
	
	for(int time=num;time>=1;time--)
	
	{
		printf("%d\t",aggre[time]);
	}
	
	return 0;
}
