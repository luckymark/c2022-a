#include<stdio.h>
int main()
{
	int year;
	scanf("%d",&year);
	if(year%400==0||(year%4==0&&year%100!=0))
	{
		printf("%d��Ϊ����",year);

	}
	else printf("%d��Ϊƽ��",year); 
	
	return 0;
}
