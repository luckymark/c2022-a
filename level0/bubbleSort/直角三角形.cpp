#include<stdio.h>
int Rt(int ras1,int ras2,int hypot)
{
	if(hypot*hypot==ras1*ras1+ras2*ras2)
	{return 1;}
	else
	{return 0;}
	
}
int main()
{
	int ras1,ras2,hypot;
	scanf("%d%d%d",&ras1,&ras2,&hypot);
	if(int answer=Rt(ras1,ras2,hypot))
	{
		printf("��������Ϊֱ��������");
	}
	else
	{
		printf("�������β�Ϊֱ��������");
	}
}
