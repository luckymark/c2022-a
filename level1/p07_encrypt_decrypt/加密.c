#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

void code()
{
	int n;
	printf("�����ַ�����:");
	scanf("%d", &n);
	getchar();
	char* c = (char*)malloc(sizeof(char) * n);
	scanf("%s", c);
	getchar();
	for (int i = 0; i < n; i++)
	{
		c[i] += 4;
	}
	printf("����Ϊ��%s", c);
	free(c);
}



void recode()
{
	int n;
	printf("�����ַ�����:");
	scanf("%d", &n);
	getchar();
	char* c = (char*)malloc(sizeof(char) * n);
	scanf("%s", c);
	for (int i = 0; i < n; i++)
	{
		c[i] -= 4;
	}
	printf("ԭ��Ϊ��%s", c);
	free(c);
}



int main()
{
	int a;
	printf("����1Ϊ���ܣ�����2Ϊ����:");
	scanf("%d", &a);
	getchar();
	system("cls");
	do
	{
		switch (a)
		{
		case 1:
			code();
			break;
		case 2:
			recode();
			break;
		}
	} while (getchar());
	return 0;
}