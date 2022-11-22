#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

void code()
{
	int n;
	printf("输入字符个数:");
	scanf("%d", &n);
	getchar();
	char* c = (char*)malloc(sizeof(char) * n);
	scanf("%s", c);
	getchar();
	for (int i = 0; i < n; i++)
	{
		c[i] += 4;
	}
	printf("密码为：%s", c);
	free(c);
}



void recode()
{
	int n;
	printf("输入字符个数:");
	scanf("%d", &n);
	getchar();
	char* c = (char*)malloc(sizeof(char) * n);
	scanf("%s", c);
	for (int i = 0; i < n; i++)
	{
		c[i] -= 4;
	}
	printf("原码为：%s", c);
	free(c);
}



int main()
{
	int a;
	printf("输入1为加密，输入2为解码:");
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