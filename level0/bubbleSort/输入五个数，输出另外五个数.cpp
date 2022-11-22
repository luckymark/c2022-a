#include<stdio.h>
int main()
{
	int aggre[5];
	
	for(int a=0;a<5;a++)
	{
		scanf("%d",&aggre[a]);
		if(aggre[a]<=9)
		{
			continue;
		}else
		{
			printf("你输入的数不符合要求，请再输一遍");
			a--;
		}
	}
	
	int num=0;
	for(;num<10;num++)
	{

		
			if(aggre[0]!=num&&aggre[1]!=num&&aggre[2]!=num&&aggre[3]!=num&&aggre[4]!=num)
			printf("%d\t",num);
			
		
	}
	return 0;
}
