#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#define MAX 126

typedef struct GOOD
{
	char* name;
	int num;
	/*void (*add)(int* num,int goodNum);
	void (*sub)(int* num,int goodNum);  */            //C语言用结构仿类需要用函数指针；暂时还不知道为什么；
}GOOD;

typedef struct GOODS
{
	GOOD good;
	struct GOODS* next, * pre;
}GOODS;

GOODS* tail=NULL, * head=NULL;

void newGOOD();     
void add(int* num, int goodNum);
void sub(int* num, int goodNum);

int main()
{
	int op;
	char goodName[MAX];
	int goodNum;
	printf("####################\n");
	printf("请选择需要进行的操作\n");
	printf("1.查看存货列表\n");
	printf("2.入库\n");
	printf("3.出库\n");
	printf("4.退出程序\n");
	printf("####################\n");
	FILE* fp = fopen("house.txt", "r");
	if (fp == NULL)
		printf("open error\n");
	while (fscanf(fp, "%s%d", goodName, &goodNum) != EOF)
	{
		newGOOD();
		tail->good.name = (char*)malloc(sizeof(char) * (strlen(goodName) + 1));
		strcpy(tail->good.name, goodName);
		tail->good.num = goodNum;
	}
	fclose(fp);
	while (1)
	{
		scanf("%d", &op);
		if (op == 1)    //显示
		{
			for (GOODS* p = head; p != NULL; p = p->next)
			{
				printf("%s %d\n", p->good.name, p->good.num);
			}
		}
		else if (op == 2)    //存货
		{
			printf("请输入存货名称和数量\n");
			scanf("%s%d", goodName, &goodNum);
			bool isFind=false;
			for (GOODS* p = head; p != NULL; p = p->next)
			{
				if (strcmp(p->good.name, goodName) == 0)
				{
					/*p->good.add = add;
					p->good.add(&(p->good.num),goodNum);*/
					p->good.num += goodNum;
					isFind = true;
					break;
				}
			}
			if (!isFind)
			{
				newGOOD();
				tail->good.name = (char*)malloc(sizeof(char) * (strlen(goodName) + 1));
				strcpy(tail->good.name, goodName);
				tail->good.num = goodNum;
			}

		}
		else if (op == 3)     //销
		{
			printf("请输入销货名称和数量\n");
			scanf("%s%d", goodName, &goodNum);
			for (GOODS* p = head; p != NULL; p = p->next)
			{
				if (strcmp(p->good.name, goodName) == 0)
				{
					/*p->good.sub = sub;
					p->good.sub(&(p->good.num), goodNum);*/
					p->good.num -= goodNum;

					if (p->good.num <= 0) //删除节点；
					{
						if (p->pre != NULL)
						{
							(* (p->pre)).next = p->next;
						}
						if (p->next != NULL)
						{
							(* (p->next)).pre = p->pre;
						}
						if (p == head)
						{
							head = p->next;
						}
						if (p == tail)
						{
							tail = p->pre;
						}
						free(p);
					}
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	fp = fopen("WAREHOUSE.txt", "w");
	for (GOODS* p=head; p != NULL; p = p->next)
	{
		fprintf(fp, "%s %d\n", p->good.name, p->good.num);
	}
	fclose(fp);
	return 0;
}

void add(int *num,int goodNum)
{
	num +=goodNum;
}
void sub(int* num,int goodNum)
{
	num -= goodNum;
}
void newGOOD()
{
	GOODS* p = tail;
	if (tail == NULL)
	{
		head = tail = (GOODS*)malloc(sizeof(GOODS));
	}
	else
	{
		tail->next = (GOODS*)malloc(sizeof(GOODS));
		tail = tail->next;
	}
	tail->pre = p;
	tail->next = NULL;
}                  //学了一个大神的写法