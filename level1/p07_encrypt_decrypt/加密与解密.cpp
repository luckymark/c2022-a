#include<stdio.h>
#include<stdlib.h>
int main()
{	int num;
	scanf("%d",&num);
	char code1[num];
	char code2[num];
	printf("�뱣��һ��%dλ������\n",num);
	for(int i=0;i<=num;i++)
	{
		scanf("%c",code1+i);
	}
	
	system("cls");
	
	printf("������һ��%dλ������\n",num);
	
	for(int i=0;i<=num;i++)
		{
			scanf("%c",code2+i);
		}
	for(int i=0;i<=num;i++)
	{
		if(code1[i]!=code2[i])
		{
			printf("�������������\n");
					break;
		}
	}
	return 0;
}
