#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int DataType;
typedef struct List
{
	DataType data;
	 List* next;
}List, * ListNode;
void InitList(ListNode node);
void CreatNode(ListNode node, int val);
void ReverseList(ListNode node);
void ShowList(ListNode node);
int main()
{
	List HeadNode;
	InitList(&HeadNode);
	printf("初始值为:");
	CreatNode(&HeadNode, 1);
	CreatNode(&HeadNode, 2);
	CreatNode(&HeadNode, 3);
	CreatNode(&HeadNode, 4);
	CreatNode(&HeadNode, 5);
	ShowList(&HeadNode);
	printf("逆置后的值为:");
	ReverseList(&HeadNode);
	ShowList(&HeadNode);
	return 0;
}
void InitList(ListNode node)
{
	node->next = NULL;
}
void CreatNode(ListNode node, int val)
{
	 List* NewNode = (struct List*)malloc(sizeof(List));
	NewNode->data = val;
	 List* p = node;
	for (p; p->next != NULL; p = p->next);
	NewNode->next = p->next;
	p->next = NewNode;
}
void ReverseList(ListNode node)
{
	 List* p = node->next;
	node->next = NULL;
	 List* q = p->next;
	while (p != q)
	{
		p->next = node->next;
		node->next = p;
		p = q;
		if (q->next != NULL)
		{
			q = q->next;
		}
	}
	p->next = node->next;
	node->next = p;
}
void ShowList(ListNode node)
{
	 List* p = node->next;
	for (p; p != NULL; p = p->next)
	{
		printf("%d ", p->data);
	}
	printf("\n");
}