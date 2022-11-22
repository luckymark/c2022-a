#include<stdio.h>
int main()
{
	int num=1,sum=0;
	for(;num<=100;num++)
	{
		if(num%7==0||num%10==7)
		printf("%d\t",num);
		sum=sum+num;
	}
	printf("%d",sum);
	return 0;
}
