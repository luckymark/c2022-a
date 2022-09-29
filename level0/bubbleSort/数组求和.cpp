#include<stdio.h>
int sum( int aggre[],int num)
{	int sum1=0;
	for(int time=0;time<num;time++)
	{
		scanf("%d",&aggre[time]);
		printf("%d",aggre[time]);
	}
	for(int time=0;time<num;time++)
	{
		sum1+=aggre[time];
	}
	return sum1;
}
int main()
{
	int Sum,num;
	scanf("%d",&num);
	int aggre[num];
	Sum=sum(aggre,num);
	printf("数组元素的和为%d",Sum);
	return 0;
}
