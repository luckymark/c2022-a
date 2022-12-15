#include"Á´±í.h"
void inh(Node* node,int i)
{
	Node* no = (Node*)malloc(sizeof(Node));
	no->data = i;
	no->next = node->next;
	node->next = no;
}

void inb(Node* node,int i)
{
	Node* no = (Node*)malloc(sizeof(Node));
	no->data = i;
	while (node->next != NULL)
	{
		node = node->next;
	}
	node->next = no;
	no->next = NULL;
}

int search(Node* node, int i)
{
	int a = 0;
	while (node->next != NULL)
	{
		node = node->next;
		a++;
		if (node->data == i)
		{
			return a;
		}
	}
	return -1;
}

