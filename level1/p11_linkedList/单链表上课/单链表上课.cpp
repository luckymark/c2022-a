#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int data;
	struct node* next;
}node;
node* search(node* pnode, int num);

int main()
{
	int num;
	
	node* head = (node*)malloc(sizeof(node));
	head = NULL;
	
	do
	{
		
		scanf_s("%d", &num);
		node*pnew = (node*)malloc(sizeof(node));
		pnew->next = NULL;
		pnew->data = num;
		if (head)
		{
			pnew->next = head;
			head = pnew;
		}
		else
		{
			head = pnew;
		}
		
		
	} while (num > 0);
	
	int i = 1;
	node* p = NULL;
	for (p = head; p; p = p->next,i++)
	{
		if (p->data == 5)
		{
			printf("第%d节是5\n", i);
			break;
		}
	}
	if (!p)
		printf("-1\n");
	for (node* p = head; p; p = p->next)
		printf("%d\n", p->data);
	
	free(head);
	return 0;
}
node* search(node* pnode, int num)
{
	node* p = NULL;
	for (p = pnode; p; p = p->next)
	{
		if (p->data == num);
			break;
	}
	return p;
}