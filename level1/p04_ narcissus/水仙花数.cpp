#include<stdio.h>
#include<math.h>
int main()
{
	int a,n1,n2,n3;
	for(int i=1;i<1000;i++)
	{
		n1=i%10;
		n2=(i-n1)%100/10;
		n3=(i-n1-n2*10)/100;
		if(pow(n1,3)+pow(n2,3)+pow(n3,3)==n1+n2*10+n3*100)
		{
			printf("%d ",n1+n2*10+n3*100);
		}
		
	}
	
	return 0;
}
