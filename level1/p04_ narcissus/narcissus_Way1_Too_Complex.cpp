#include<stdio.h>
#include<math.h>
int main()
{	
	int i,j,k;
	i = 1;j = 0;k = 0;
	int a[4] = {i,j,k};
	int n,x;
	
	for(;i<=9;i++)
	{
		a[0] = i;
		for(;j<=9;j++)
		{
			a[1] = j;
			for(;k<=9;k++)
			{
				a[2] = k;
				n = a[0]*100 + a[1]*10 + a[2];
				x = pow ((double) a[0],3) + pow((double) a[1],3) + pow((double) a[2],3);
				if(n == (int)x)
				{
					printf("%d ",n);
				}
			}
			if(k == 10)
			{
				k = 0;
			}
		}
		if(j == 10)
		{
			j = 0;
		}
	}
 }
