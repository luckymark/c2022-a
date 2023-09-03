#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct product
{
	char name[11]; //��Ʒ����
	float dj; //����
	int sl = -1; //����
};
void Input_Data()
{
	FILE* fp;
	struct product sell[100];
	char fname[50];
	printf("  �������Ʒ����¼�ļ�����\n");
	scanf("%s", fname);
	if ((fp = fopen(fname, "rb")) == NULL)
	{
		printf("���ܴ��ļ����ļ������ڣ�\n");
		return;
	}
	fread(sell, sizeof(struct product), 100, fp);
	printf("  ����������Ʒ����:\n");
	int M;
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		printf("  �������%d����Ʒ������¼���ݣ�\n", i + 1);
		printf("  ��Ʒ���ƣ�");
		char name[11];
		scanf("%s", name);
		printf("  ������");
		int num;
		scanf("%d", &num);
		int ret = 1;
		for (int i = 0; i < 100; i++)
		{
			if (strcmp(sell[i].name, name) == 0)
			{
				sell[i].sl += num;
				ret = 0;
				break;
			}
		}
		if (ret == 1)
		{
			printf("  ���ۣ�");
			float money;
			scanf("%f", &money);
			for (int i = 0; i < 100; i++)
			{
				if (sell[i].sl == -1)
				{
					strncpy(sell[i].name, name, 11);
					sell[i].dj = money;
					sell[i].sl = num;
					break;
				}
			}
		}
	}
	fp = fopen(fname, "wb");
	fwrite(sell, sizeof(struct product), 100, fp);
	fclose(fp);
}
void output_Date()
{
	FILE* fp;
	struct product sell[100];
	char fname[50];
	printf("  �������Ʒ�����ļ�����\n");
	scanf("%s", fname);
	if ((fp = fopen(fname, "rb")) == NULL)
	{
		printf("  ���ܴ��ļ����ļ������ڣ�\n");
		return;
	}
	fread(sell, sizeof(struct product), 100, fp);
	int M;
	printf("  ����������Ʒ��������\n");
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		int  num;
		char name[11];
		printf("  �������%d����Ʒ�ĳ����¼���ݣ�\n", i + 1);
		printf("  ��Ʒ���ƣ�");
		scanf("%s", name);
		printf("  ����������");
		scanf("%d", &num);
		int ret = 0;
		for (int i = 0; i < 100; i++)
		{
			if (sell[i].sl != -1 && strcmp(sell[i].name, name) == 0)
			{
				ret = 1;
				if (sell[i].sl - num < 0)
				{
					printf("  �û���ֻʣ%d���������������,������\n", sell[i].sl);
					break;
				}
				else
				{
					sell[i].sl -= num;
					printf("  ����ɹ����û��ﻹʣ%d����\n", sell[i].sl);
				}
			}
		}
		if (ret == 0)
			printf("  û�иû�Ʒ��������\n");
	}
	fp = fopen(fname, "wb");
	fwrite(sell, sizeof(struct product), 100, fp);
	fclose(fp);
}
void Show_Date()
{
	FILE* fp;
	struct product sell[100];
	char fname[50];
	printf("  ����б��ļ�����\n");
	scanf("%s", fname);
	if ((fp = fopen(fname, "rb")) == NULL)
	{
		printf("  �ļ�Ϊ�ջ��ļ�������\n");
		return;
	}
	fread(sell, sizeof(struct product), 100, fp);
	printf("\n����\t����\t����\n");
	for (int i = 0; i < 100; i++)
	{
		if (sell[i].sl != -1)
			printf("%s\t%.2f\t%d\n", sell[i].name, sell[i].dj, sell[i].sl);
	}
	fclose(fp);
}
int main()
{
	int n;
	while (1)
	{

		printf("  1 ��ʾ����б�\n");
		printf("  2 ���\n");
		printf("  3 ����\n");
		printf("  4 �����Ļ\n");
		printf("  5 �˳�����\n");
		printf("���������֣�");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			Show_Date();
			break;
		case 2:
			Input_Data();
			break;
		case 3:
			output_Date();
			break;
		case 4:
			system("cls");
			break;
		case 5:
			return 0;
		}
	}
}