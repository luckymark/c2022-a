#include<stdio.h>
int feibo(int d,int a,int b)
{
	int c;
	
	for(int i=3;i<=d;i++)
	{
		c=a+b;
		b=a;
		a=c;
	}
	return a;
	
}	
int main()
{	
    int time,n;
	scanf("%d",&time);
	int num1=1;
 	int num2=1;
 	n=feibo(time,num1,num2);
 	printf("第%d个斐波那契数是%d",time,n);
 	return 0;
}
