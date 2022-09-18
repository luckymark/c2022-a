#include <stdio.h>
#include<time.h>
#include<math.h>
int main()
{
	clock_t start,end;
	int n,k,a,b;
	double time;
	int i = 2;
	start = clock();
	for(n = 2;n < 1000;n++)
	{
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
			printf("%d ",n);
		}
	}
	end = clock();
	printf("\n");
	time = (double)(end - start);
	printf("%f",time);
	return 0;
 } 
