#include<stdio.h>
int main()
{
	int num1=1,num2=1,time=1;
	
	for(;num1<=9;num1++)
	{
		for(;num2>=1&&num2<=9;num2++)
		
		{
			int answer=num1*num2;
			printf("%d*%d=%d\t",num1,num2,answer);
		
		}
		
		printf("\n");
		time++;
		num2=time;
		
	}
	
	return 0;//没作出想要的结果（标准的九九乘法表格式），还请老师指点
}
