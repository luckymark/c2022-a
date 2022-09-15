#include<stdio.h>
int main()
{
	int n,k;
	int i = 2;
	scanf("%d",&n);
	for(;i <= n;i++)
	{
		if(n%i == 0)
		{
			break;
		}
	}
	if(i == n)
	{
		printf("Yes");
	}else printf("No");
	return 0;
 } 
