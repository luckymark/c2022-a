#include<stdio.h>
int main()
{
	int num;
	scanf("%d",&num);
	if(num!=0&&num%13)
	{
		printf("���������Ϊ13�ı���");
	}else{
		if(num==0){
			printf("���������Ϊ13�ı���");
		}else{
			printf("�������Ϊ13�ı���");
		}
	}
	return 0;
}
