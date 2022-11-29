#define	_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
	large=1,middle,small
}Type;

typedef struct cargonode{
	int price;
	int quantity;
	Type type;
	struct cargonode* Pnext;
}CargoNode;

int CargoCount = 0;

char* change(Type type)
{
	switch (type)
	{
	case large:return "large";
	case middle:return "middle";
	case small:return "small";
	default:return "error!";
	}
}

int menu()
{

	int choice = 0;
	printf("欢迎进入仓库,请选择你的操作：\n");
	printf("1.显示存货列表\n");
	printf("2.入库\n");
	printf("3.出库\n");
	printf("4.退出程序\n");
	scanf("%d", &choice);
	return choice;
}
void initcargo()
{
	FILE* fp = fopen("存货列表.txt", "w");
	fprintf(fp,"价格：5/数量：5/型号：small\n");
	fprintf(fp, "价格：6/数量：6/型号：middle\n");
	fprintf(fp, "价格：7/数量：7/型号：large\n");

	fclose(fp);
}

CargoNode* createlinkchain(int number)
{
	FILE* fp = fopen("存货列表.txt", "w");
	CargoNode* Phead=NULL ,* Pend = NULL,*Pnew=NULL;
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
			scanf("%s",p);
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
			fprintf(fp, "价格：%d/数量：%d/型号：%s\n", Pnew->price, Pnew->quantity, change(Pnew->type));
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
				exit(0);
			}
			printf("型号输入成功！\n");

			Pnew->Pnext = NULL;
			Pend = Pnew;
			fprintf(fp, "价格：%d/数量：%d/型号：%s\n", Pnew->price, Pnew->quantity, change(Pnew->type));

		}
		putchar('\n');
	}
	fclose(fp);
	return Phead;
}
void addcargo(CargoNode* p, int price,int quantity,Type type)
{
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
	fprintf(fp, "价格：%d/数量：%d/型号：%s\n", p->price, p->quantity, change(p->type));
	CargoCount++;
	fclose(fp);
}
void delcargo(CargoNode*p,int number)
{
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
		fprintf(fp, "价格：%d/数量：%d/型号：%s\n", p3->price, p3->quantity, change(p3->type));
		p3 = p3->Pnext;
	}
	fclose(fp);
}

int main()
{
	//initcargo();
	int choice=0;
	char helperarr[40];
	char getfromflie[40];
	FILE* fp=NULL ;
	CargoNode* phead = createlinkchain(2);
	CargoNode helper = {0,0,small,NULL};
	while (1) {
		switch (menu())
		{
		case 1:
			system("cls");
			fp = fopen("存货列表.txt", "r");
			rewind(fp);
			for (int a = 0; a < CargoCount; a++)
			{
				printf("%d. ", a + 1);
				fgets(getfromflie, 40, fp);
				printf("%s\n", getfromflie);
			}
			fclose(fp);
			break;
		case 2:
			printf("请依次输入价格，数量，型号\n");
			scanf("%d", &helper.price);
			printf("价格输入成功！\n");
			scanf("%d", &helper.quantity);
			printf("数量输入成功！\n");
			scanf("%s", helperarr);
			if (!(strcmp(helperarr, "large")))
			{
				helper.type = large;
			}
			else if (!(strcmp(helperarr, "middle")))
			{
				helper.type = middle;
			}
			else if (!(strcmp(helperarr, "small")))
			{
				helper.type = small;
			}
			else
			{
				printf("输入型号错误！\n\a");
				exit(0);
			}
			printf("型号输入成功！\n");
			addcargo(phead,helper.price,helper.quantity,helper.type );
			break;
		case 3:
			if(CargoCount!=2)
			fclose(fp);
			printf("请输入你要删除第几批货物：\n");
			scanf("%d", &choice);
			delcargo(phead, choice);
			printf("已成功出库！\n");
			break;
		case 4:
			printf("你已成功退出！\n");
			exit(0);
			break;
		default:
			printf("无效输入！请重新输入！\n");
			break;
		}
	}
	fclose(fp);
	return 0;
}