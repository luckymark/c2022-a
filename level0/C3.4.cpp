#include<stdio.h>
#include<math.h> 
void RTs(double a,double b,double c)
{
	scanf("%lf %lf %lf",&a,&b,&c);
	if(a>0&&b>0&&c>0)
	{	
		if( (pow(a,2)+pow(b,2))==pow(c,2) || (pow(b,2)+pow(c,2))==pow(a,2) || (pow(a,2)+pow(c,2))==pow(b,2) )
		{
			printf("Yes");
		}else printf("No");
	}else printf("error");
}
