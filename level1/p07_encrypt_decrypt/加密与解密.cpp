#include<stdio.h>
#include<stdlib.h>
int main()
{	int num;
	scanf("%d",&num);
	char code1[num];
	char code2[num];
	printf("请保存一个%d位的密码\n",num);
	for(int i=0;i<=num;i++)
	{
		scanf("%c",code1+i);
	}
	
	system("cls");
	
	printf("请输入一个%d位的密码\n",num);
	
	for(int i=0;i<=num;i++)
		{
			scanf("%c",code2+i);
		}
	for(int i=0;i<=num;i++)
	{
		if(code1[i]!=code2[i])
		{
			printf("您的密码输错了\n");
					break;
		}
	}
	return 0;
}
