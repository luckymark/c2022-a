#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct product
{
	char name[11]; //产品名称
	float dj; //单价
	int sl = -1; //数量
};
void Input_Data()
{
	FILE* fp;
	struct product sell[100];
	char fname[50];
	printf("  请输入产品入库记录文件名：\n");
	scanf("%s", fname);
	if ((fp = fopen(fname, "rb")) == NULL)
	{
		printf("不能打开文件，文件不存在！\n");
		return;
	}
	fread(sell, sizeof(struct product), 100, fp);
	printf("  请输入入库产品数量:\n");
	int M;
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		printf("  请输入第%d个产品的入库记录数据：\n", i + 1);
		printf("  产品名称：");
		char name[11];
		scanf("%s", name);
		printf("  数量：");
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
			printf("  单价：");
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
	printf("  请输入产品出库文件名：\n");
	scanf("%s", fname);
	if ((fp = fopen(fname, "rb")) == NULL)
	{
		printf("  不能打开文件，文件不存在！\n");
		return;
	}
	fread(sell, sizeof(struct product), 100, fp);
	int M;
	printf("  请输入出库产品种类数量\n");
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		int  num;
		char name[11];
		printf("  请输入第%d个产品的出库记录数据：\n", i + 1);
		printf("  产品名称：");
		scanf("%s", name);
		printf("  出库数量：");
		scanf("%d", &num);
		int ret = 0;
		for (int i = 0; i < 100; i++)
		{
			if (sell[i].sl != -1 && strcmp(sell[i].name, name) == 0)
			{
				ret = 1;
				if (sell[i].sl - num < 0)
				{
					printf("  该货物只剩%d个，库存数量不够,请重试\n", sell[i].sl);
					break;
				}
				else
				{
					sell[i].sl -= num;
					printf("  出库成功，该货物还剩%d个。\n", sell[i].sl);
				}
			}
		}
		if (ret == 0)
			printf("  没有该货品，请重试\n");
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
	printf("  存货列表文件名：\n");
	scanf("%s", fname);
	if ((fp = fopen(fname, "rb")) == NULL)
	{
		printf("  文件为空或文件不存在\n");
		return;
	}
	fread(sell, sizeof(struct product), 100, fp);
	printf("\n名称\t单价\t数量\n");
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

		printf("  1 显示存货列表\n");
		printf("  2 入库\n");
		printf("  3 出库\n");
		printf("  4 清空屏幕\n");
		printf("  5 退出程序\n");
		printf("请输入数字：");
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