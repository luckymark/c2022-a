/*��Ŀ�����ܵ���ĸ

 ����Ҫ��

1. ��console�����һ����ĸ���򵥴ʣ�
1. ʹ����ĸ�򵥴ʣ���һ���ٶȴ��������˶�
1. ��������Ļ�߽�ʱ�����˶�*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
	int i,j;
	while (1)
	{
		for (i = 1; i <= 100; i++)
		{
			j = i;
			while (j--)
			{
				printf(" ");
			}
			printf("ɵ��");
			Sleep(0.01);
			system("cls");
		}
		for (i = 100; i >= 1; i--)
		{
			j = i;
			while (j--)
			{
				printf(" ");
			}
			printf("ɵ��");
			Sleep(0.01);
			system("cls");
		}
	}
	return 0;
}

