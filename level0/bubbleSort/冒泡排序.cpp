#include<stdio.h>
void bubble(int aggre[],int size)
{
	int i=0;
	for(;i<size-1;i++)
	{
		int flag=1;
		int a=0;
		for(;a<size-1-i;a++)
		{
			if(aggre[a]>aggre[a+1])
			{
				int b=aggre[a];
				aggre[a]=aggre[a+1];
				aggre[a+1]=b;
				int flag=0;
			}
		}
		if(flag==1)
		break;
	}
}
int main()
{
	int aggre[]={0,1,2,3,4,5,6,7,8,9};
	int size=sizeof(aggre)/sizeof(aggre[0]);
	bubble(aggre,size);
	for(int i=0;i<size;i++)
	{
		printf("%d",aggre[i]);
	}
	return 0;
}
