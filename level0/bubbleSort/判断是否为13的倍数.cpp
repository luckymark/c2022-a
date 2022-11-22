#include<stdio.h>
int main()
{
	int num;
	scanf("%d",&num);
	if(num!=0&&num%13)
	{
		printf("输入的数不为13的倍数");
	}else{
		if(num==0){
			printf("输入的数不为13的倍数");
		}else{
			printf("输入的数为13的倍数");
		}
	}
	return 0;
}
