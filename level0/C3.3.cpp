#include<stdio.h> 
int f(int n)
{
	int i = 1;
	int k;
	int a1,a2;
	if(n >= 1 && n <= 2)
	{
		return 1;
	}else
	{
		for(a1 = 1,a2 = 1;i <= n-2;i++)
		{
			k = a1 +a2;
			a1 = a2;
			a2 = k;
		}
		return k;
	}
}
