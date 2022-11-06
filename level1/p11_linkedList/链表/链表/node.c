#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"node.h"

extern int number = 0;
Node* createnode()
{
	Node* head = NULL;
	Node* end, * pnew;
	end = pnew = (Node*)malloc(sizeof(Node));
	printf("please enter data:\n");
	scanf("%d", &pnew->data);
	while (pnew->data != 0)
	{
		number++;
		if (number == 1)
		{
			pnew->next = NULL;
			end = pnew;
			head = pnew;
		}
		else
		{
			pnew->next = NULL;
			end->next = pnew;
			end = pnew;
		}
		pnew = (Node*)malloc(sizeof(Node));
		printf("please enter data:\n");
		scanf("%d", &pnew->data);
	}
	return head;
}

Node* addfirstnode(Node* head, int data2)
{
	number++;
	Node* pnew = (Node*)malloc(sizeof(Node));
	pnew->data = data2;
	pnew->next = head;
	head = pnew;
	return head;
}

void printnode(Node* p)
{
	int num = 1;
	printf("it has %d members\n", number);
	while (p != NULL)
	{
		printf("NO %d is %d\n", num, p->data);
		printf("\n");
		num++;
		p = p->next;
	}
}

void addnode(int location, Node* p, int data2)
{
	if (number < location)
	{
		printf("unknown error!\n\a");
		exit(0);
	}
	else
	{
		Node* p1 = p;
		Node* pnew = (Node*)malloc(sizeof(Node));
		number++;
		for (int a = 1; a < location - 1; a++)
		{
			p1 = p1->next;
		}
		pnew->data = data2;
		pnew->next = p1->next;
		p1->next = pnew;
	}
}

void reversenode(Node* p)
{
	Node* p2 = p, * p3 = p;
	int num = 0;
	for (; p3->next != NULL; p3 = p3->next)
		num++;
	Stack* pdata = createStack(number);
	for (int a = 0; a <= num; a++, p2 = p2->next)
	{
		push(pdata, p2->data);
	}
	for (int a = 0; a <= num; a++)
	{
		p->data = pop(pdata);
		p = p->next;
	}
	freestack(pdata);
}
int findDataNode(Node* p, int data2)
{
	int success = 0;
	for (int count = 1; p != NULL; p = p->next)
	{
		if (p->data == data2)
		{
			printf("No %d is %d!\n", count, data2);
			success = 1;
			return count;
		}
		else
			count++;
	}
	if (success == 0)
	{
		printf("There is no 5!\n\a");
		return -1;
	}
}
void deletenode(Node* p, int location)
{
	if (location > number)
	{
		printf("unknown error!\a\n");
		exit(0);
	}
	else {
		printf("delete No%d node\n", location);
		Node* temp = p;
		Node* pre = p;
		for (int a = 1; a < location; a++)
		{
			pre = temp;
			temp = temp->next;
		}
		pre->next = temp->next;
		free(temp);
		number--;
	}
}