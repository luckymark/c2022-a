# define RATE 7.21
#include<stdio.h>
double exchange(double money)
{
	double yuan=0;
	yuan=RATE*money;
	return yuan;
	
}

 int main()
{
	double money,yuan;
	scanf("%lf",&money);
	yuan=exchange(money);
	printf("%.2f��Ԫ���Զһ�%.2fԪ�����",money,yuan);
	return 0;
}
