#define	_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Cargo.h"

extern int CargoCount;

CargoNode* CreateLinkChain(int number)
{
	CargoNode help;
	//制作货物链表
	FILE* fp = fopen("存货列表.txt", "w");
	CargoNode* Phead = NULL, * Pend = NULL, * Pnew = NULL;
	char p[7];

	for (int a = 0; a < number; a++)
	{
		CargoCount++;
		printf("现在是第%d个节点\n", a + 1);
		if (a == 0)
		{
			Pnew = (CargoNode*)malloc(sizeof(CargoNode));

			printf("请依次输入价格，数量，型号\n");
			scanf("%d", &(Pnew->price));
			printf("价格输入成功！\n");
			scanf("%d", &(Pnew->quantity));
			printf("数量输入成功！\n");
			scanf("%s", p);
			if (!(strcmp(p, "large")))
			{
				Pnew->type = large;
			}
			else if (!(strcmp(p, "middle")))
			{
				Pnew->type = middle;
			}
			else if (!(strcmp(p, "small")))
			{
				Pnew->type = small;
			}
			else
			{
				printf("输入型号错误！\n\a");
				exit(0);
			}
			printf("型号输入成功！\n");
			Pnew->Pnext = NULL;
			Pend = Pnew;
			Phead = Pnew;

			help = *Pnew;
			help.Pnext = NULL;
			fwrite(&help, sizeof(CargoNode), 1, fp);
		}
		else {
			Pnew->Pnext = (CargoNode*)malloc(sizeof(CargoNode));
			Pnew = Pnew->Pnext;
			printf("请依次输入价格，数量，型号\n");
			scanf("%d", &(Pnew->price));
			printf("价格输入成功！\n");
			scanf("%d", &(Pnew->quantity));
			printf("数量输入成功！\n");
			scanf("%s", p);
			if (!(strcmp(p, "large")))
			{
				Pnew->type = large;
			}
			else if (!(strcmp(p, "middle")))
			{
				Pnew->type = middle;
			}
			else if (!(strcmp(p, "small")))
			{
				Pnew->type = small;
			}
			else
			{
				printf("输入型号错误！\n\a");
				return 0;
			}
			printf("型号输入成功！\n");

			Pnew->Pnext = NULL;
			Pend = Pnew;
			help = *Pnew;
			help.Pnext = NULL;
			fwrite(&help, sizeof(CargoNode), 1, fp);
		}
		putchar('\n');
	}
	fclose(fp);
	return Phead;
}

CargoNode* MakeExistChain()
{
	CargoNode help;

	//首先获取货物件数
	FILE* number = fopen("货物件数.txt", "r");
	int Number = 0;
	fscanf(number, "%d", &Number);
	//用以前的信息制作链表
	FILE* fp = fopen("存货列表.txt", "r");
	CargoNode* Phead = NULL, * Pend = NULL, * Pnew = NULL;
	Pend = Pnew = (CargoNode*)malloc(sizeof(CargoNode));

	for (int a = 0; a < Number; a++)
	{
		CargoCount++;
		if (a == 0)
		{
			Pnew->Pnext = NULL;
			Phead = Pnew;
			Pend = Pnew;
			fread(&help, sizeof(CargoNode), 1, fp);
			Phead->price = help.price;
			Phead->quantity = help.quantity;
			Phead->type = help.type;
		}
		else
		{
			Pnew->Pnext = (CargoNode*)malloc(sizeof(CargoNode));
			Pnew = Pnew->Pnext;

			Pnew->Pnext = NULL;
			Pend = Pnew;
			fread(&help, sizeof(CargoNode), 1, fp);
			Pnew->price = help.price;
			Pnew->quantity = help.quantity;
			Pnew->type = help.type;
		}
	}
	fclose(fp);
	return Phead;
}

void addcargo(CargoNode* p2, int price, int quantity, Type type)
{
	CargoNode help;
	CargoNode* p = p2;
	FILE* fp = fopen("存货列表.txt", "a");
	while (p->Pnext != NULL)
	{
		p = p->Pnext;
	}
	p->Pnext = (CargoNode*)malloc(sizeof(CargoNode));
	p = p->Pnext;
	p->price = price;
	p->quantity = quantity;
	p->type = type;
	p->Pnext = NULL;

	help = *p;
	help.Pnext = NULL;
	fwrite(&help, sizeof(CargoNode), 1, fp);

	CargoCount++;
	fclose(fp);
}

void delcargo(CargoNode* p, int number)
{
	CargoNode help;

	CargoNode* p2 = p;
	CargoNode* p3 = p;
	FILE* fp = fopen("存货列表.txt", "w");
	if (number > CargoCount)
	{
		printf("找不到货物，出库失败！\n\a");
		exit(0);
	}
	else
	{
		if (number == 1)
		{
			p3 = p3->Pnext;
			CargoCount--;
		}
		else {
			for (int a = 0; a < number - 1; a++)
			{
				p2 = p;
				p = p->Pnext;
			}
			p2->Pnext = p->Pnext;
			free(p);
			CargoCount--;
		}
	}

	for (int a = 0; a < CargoCount; a++)
	{
		help = *p3;
		help.Pnext = NULL;
		fwrite(&help, sizeof(CargoNode), 1, fp);
		p3 = p3->Pnext;
	}
	fclose(fp);
}

void altercargo(CargoNode* p, int number, CargoNode* information,char*alter)
{
	if (number > CargoCount)
	{
		printf("找不到货物，修改失败！\n\a");
		exit(0);
	}

	CargoNode help;
	FILE* fp = fopen("存货列表.txt", "w");
	CargoNode* p2 = p;
	CargoNode* p3 = p;

	
	for (int a=0;a<number-1;a++)
	{
		p2 = p2->Pnext;
	}
	if (alter[0] == 'y')
	{
		p2->price = information->price;
	}
	if (alter[1] == 'y')
	{
		p2->quantity = information->quantity;
	}
	if (alter[2] == 'y')
	{
		p2->type  = information->type;
	}
	for (int a = 0; a < CargoCount; a++)
	{
		help = *p3;
		help.Pnext = NULL;
		fwrite(&help, sizeof(CargoNode), 1, fp);
		p3 = p3->Pnext;
	}
	fclose(fp);
	return;
}
