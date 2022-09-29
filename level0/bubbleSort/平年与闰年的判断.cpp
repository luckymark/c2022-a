#include<stdio.h>
int main()
{
	int year;
	scanf("%d",&year);
	if(year%400==0||(year%4==0&&year%100!=0))
	{
		printf("%d年为闰年",year);

	}
	else printf("%d年为平年",year); 
	
	return 0;
}
