#include<stdio.h>
#include<math.h>
int main()
{
	int n,k,a,b;
	int i = 2;
	scanf("%d",&n);
	a = sqrt((double)n);
	for(i = 2;i <= a;i++)
		{
			if(n%i == 0)
			{
				break;
			}
		}
	if(i == a+1)
	{
		printf("Yes");
	}else printf("No");
	return 0;
 } 
