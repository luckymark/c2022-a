#include"Á´±í.h"

int main()
{
	Node*header = (Node*)malloc(sizeof(Node));
	Node* sp = (Node*)malloc(sizeof(Node));
	sp = header;
	for (int i = 0; i < n; i++)
	{
		Node*node = (Node*)malloc(sizeof(Node));
		sp->next = node;
		node->data = arr[i];
		node->next = NULL;
		sp = node;
	}
	sp = header;
	while (sp->next != NULL)
	{
		sp = sp->next;
		printf("%d", sp->data);
	}
	printf("\n");
	sp = header;
	inh(header,6);
	sp = header;
	inb(header,6);
	sp = header;
	while (sp->next != NULL)
	{
		sp = sp->next;
		printf("%d", sp->data);
	}
	printf("\n");
	sp = header;
	printf("%d\n", search(sp, 5));
	sp = header;
	turn(sp);
	while (sp->next != NULL)
	{
		sp = sp->next;
		printf("%d", sp->data);
	}
	printf("\n");
	return 0;
}


