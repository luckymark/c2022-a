#include<stdio.h>
#include<math.h>

void prime(int n);
 
int main()
{
	int n,k,a,b;
	int i = 2;
	scanf("%d",&n);
	prime(n);
	return 0;
}

void prime(int n)
{
	int a,i;
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
}
