#include<stdio.h>
int digit1(int integer1)
{
	return integer1%10;
}
int digit2(int integer2)
{
	return (integer2/10)%10;
}
int digit3(int integer3)
{
	return (integer3/100)%10;
}
int main()
{
	for(int num=100;num<=999;num++)
	{
		int integer1,integer2,integer3;
		integer1=digit1(num);
		integer2=digit2(num);
		integer3=digit3(num);
		if(num==integer1*integer1*integer1+integer2*integer2*integer2+integer3*integer3*integer3)
		printf("%d\t",num);
	}
	return 0;
}
