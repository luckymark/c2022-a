#include<stdio.h>
int prime(const int integer)
{
	int num=0;
	for(int i=2;i<integer;i++)
	{
		if(integer%i==0)
		num++;
	}
	if(num==0)
	return 1;
	else
	return 0;
}
int main()
{
	int integer=0,num=0;
	scanf("%d",&integer);
	if(num=prime(integer))
	printf("��%dΪ����",integer);
	else
	printf("��%d��Ϊ����",integer);
	return 0;
}
