#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

struct Goods
{
	int num;
	struct Goods* next;
};

typedef struct Goods Goods;
Goods* Head, * ptr, * p;

void menu();
void TraversalLinkNode(Goods* ptr);
struct Goods* CreatLinkNode();
void PushNode(Goods* Head, Goods* ptr);
void PopNode(Goods* Head);
Goods* DeleteNode(Goods* ptr, int* pcount);
void Down();
void Stop();

int main()
{
	srand((unsigned)time(0));
	Head = CreatLinkNode();
	menu();
}

void menu()
{
	int choice;
	printf("*****************************************\n");
	printf("-----------------------------------------\n");
	printf("   通过输入以下数字来访问该系统的功能：  \n");
	printf("           1.显示存货列表                \n");
	printf("           2.入库                        \n");
	printf("           3.出库                        \n");
	printf("           4.退出程序                    \n");
	printf("-----------------------------------------\n");
	printf("*****************************************\n");
	printf("\n");
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		TraversalLinkNode(Head);
		break;
	case 2:
		PushNode(Head, ptr);
		break;
	case 3:
		PopNode(Head);
		break;
	case 4:
		Down();
		break;
	}
}

Goods* CreatLinkNode()
{
	int i;
	Head = (Goods*)malloc(sizeof(Goods));
	if (!Head)
	{
		printf("Wrong distribution!");
		exit(1);
	}
	Head->num = rand() % 500;
	Head->next = NULL;
	ptr = Head;
	for (i = 2; i <= 100; i++)
	{
		p = (Goods*)malloc(sizeof(Goods));
		if (!p)
		{
			printf("Wrong distribution!");
			exit(1);
		}
		p->num = rand() % 500;
		p->next = NULL;
		ptr->next = p;
		ptr = ptr->next;
	}
	return Head;
}

void TraversalLinkNode(Goods* ptr)
{
	system("cls");
	int time = 1;
	while (ptr != NULL)
	{
		printf("%d.%d", time, ptr->num);
		time++;
		ptr = ptr->next;
		printf("\n");
	}
	printf("即将进入尾界面\n");
	system("pause");
	Down();
}

void PushNode(Goods* Head, Goods* ptr)
{
	system("cls");
	int NewGoods;
	Goods* NewNode = (Goods*)malloc(sizeof(Goods));
	printf("请输入您想要入库的货物的数据：");
	scanf_s("%d", &NewGoods);
	NewNode->num = NewGoods;
	NewNode->next = NULL;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = NewNode;
	printf("当前库里的货物数据如下：");
	TraversalLinkNode(Head);
	Down();
}

void PopNode(Goods* Head)
{
	int count = 0;
	int* pcount = &count;
	system("cls");
	Goods* ptr;
	ptr = Head;
	int PopGoods;
	printf("请输入您想要出库的货物的数据：");
	scanf_s("%d\n", &PopGoods);
	while (ptr->next != NULL)
	{
		if (ptr->num == PopGoods)
		{
			ptr = DeleteNode(ptr, pcount);
		}
		if (ptr->next == NULL)
		{
			break;
		}
		ptr = ptr->next;
	}
	if (ptr->next == NULL && ptr->num == PopGoods)
	{
		free(ptr);
	}
	if (count == 0)
	{
		printf("Sorry,I don't find the data you want to delete\n");
	}
	printf("当前库里的货物数据如下：\n");
	system("pause");
	TraversalLinkNode(Head);
	Down();
}

Goods* DeleteNode(Goods* ptr, int* pcount)
{
	Goods* PreNode;
	PreNode = Head;
	while (PreNode->next != ptr)
	{
		PreNode = PreNode->next;
	}
	PreNode->next = ptr->next;
	free(ptr);
	*pcount++;
	return PreNode->next;
}

void Down()
{
	system("cls");
	int i = 0;
	printf("*****************************************\n");
	printf("-----------------------------------------\n");
	printf("\n");
	printf("      如果您想返回主菜单，请输入1        \n");
	printf("      如果您想结束程序，请输入任意字符   \n");
	printf("\n");
	printf("-----------------------------------------\n");
	printf("*****************************************\n");
	printf("\n");
	scanf_s("%d", &i);
	switch (i)
	{
	case 1:
		menu();
		break;
	default:
		Stop();
	}
}
void Stop()
{
	system("cls");
	printf("Byebye（- V -）~~");
	printf("\n");
	printf("\n");
	printf("\n");
}
