#include<stdio.h> 
int main()
{
	int n = 100;
	int a1,a2,a3;
	for(;n<1000;n++)
	{
		a1 = n/100;
		a2 = n/10%10;
		a3 = n%10;
		if(n == a1*a1*a1 + a2*a2*a2 + a3*a3*a3)
		{
			printf("%d ",n);
		}
	}
	return 0;
}
