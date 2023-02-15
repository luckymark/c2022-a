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
	void (*sub)(int* num,int goodNum);  */            //C�����ýṹ������Ҫ�ú���ָ�룻��ʱ����֪��Ϊʲô��
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
	printf("��ѡ����Ҫ���еĲ���\n");
	printf("1.�鿴����б�\n");
	printf("2.���\n");
	printf("3.����\n");
	printf("4.�˳�����\n");
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
		if (op == 1)    //��ʾ
		{
			for (GOODS* p = head; p != NULL; p = p->next)
			{
				printf("%s %d\n", p->good.name, p->good.num);
			}
		}
		else if (op == 2)    //���
		{
			printf("�����������ƺ�����\n");
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
		else if (op == 3)     //��
		{
			printf("�������������ƺ�����\n");
			scanf("%s%d", goodName, &goodNum);
			for (GOODS* p = head; p != NULL; p = p->next)
			{
				if (strcmp(p->good.name, goodName) == 0)
				{
					/*p->good.sub = sub;
					p->good.sub(&(p->good.num), goodNum);*/
					p->good.num -= goodNum;

					if (p->good.num <= 0) //ɾ���ڵ㣻
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
}                  //ѧ��һ�������д��