#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
int num = 1;
struct LinkNode
{
	int data;
	LinkNode* next;
};
LinkNode* CreatNewNode()
{
	LinkNode* Head, * ptr, * p;
	Head = (LinkNode*)malloc(sizeof(LinkNode));
	if (Head == NULL)
	{
		printf("Fake distribution!");
	}
	else {
		printf("Your data in single linked list is showed:\n");
		Head->data = rand() % 100;
	}
	ptr = Head;
	for (int i = 1; i < 100; i++)
	{
		p = (LinkNode*)malloc(sizeof(LinkNode));
		if (p == NULL)
		{
			printf("Fake distribution!\n");
		}
		else
		{
			p->data = rand()%100;
			p->next = NULL;
			ptr->next = p;
			ptr = ptr->next;
		}
	}
	return Head;
}
void TraversalLinkNode(LinkNode *ptr)
{
	while (ptr != NULL)
	{
		printf("%d", ptr->data);
		ptr = ptr->next;
		printf("\t");
	}
}
LinkNode* FindLinkNode_1(LinkNode* Head,int data,int *pcount)
{
	int count = *pcount;
	LinkNode* ptr;
	ptr = Head;
	if (ptr == NULL)
	{
		printf("Error!\n");
	}
	while (ptr ->next != NULL)
	{
		if (ptr->data == data)
		{
			return ptr;
		}
		ptr = ptr->next;
		count++;
		*pcount = count;
	}
	return ptr;
}
LinkNode* PushNode( LinkNode* ptr)
{

	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return ptr;
}
void ReverseNode(LinkNode* Head)
{
	LinkNode* ptr; 
	ptr = Head;
	int num_box[100] = { 0 };
	for (int time = 0; time < 100; time++)
	{
		num_box[time] = ptr->data;
		ptr = ptr->next;
	}
	ptr = Head;
	for (int time = 99; time >= 0; time--)
	{
		ptr->data = num_box[time];
		ptr = ptr->next;
	}
}
LinkNode* FindLinkNode_2(LinkNode* ptr, int data, int* pcount)
{
	ptr = ptr->next;
	int count = *pcount;
	if (ptr == NULL)
	{
		printf("Error!\n");
	}
	while (ptr->next != NULL)
	{
		if (ptr->data == data)
		{
			return ptr;
		}
		ptr = ptr->next;
		count++;
		*pcount = count;
	}
	return ptr;
}
int main()
{
	srand((unsigned)time(NULL));
	int data,count=1;
	LinkNode* Head, * ptr;
	Head = CreatNewNode();
	TraversalLinkNode(Head);
	printf("\n");
	printf(" Please input the data that you want to find\n");
	scanf("%d", &data);
	ptr = FindLinkNode_1(Head, data,&count);
	if (ptr ->next== NULL)
	{
		printf("Sorry,your data,have not been found\n");
	}
	else
	{
		while (ptr ->next!= NULL)
		{
			printf("Your data have been found!\n");
			printf("This node's number is %d\n", count);
			ptr = FindLinkNode_2(ptr, data, &count);
			if (ptr->next == NULL)
			{
				goto out;
			}
		}
		
	}
	out:
	ptr = PushNode( ptr);
	ReverseNode(Head);
	printf("If your single linked list is reversed,your data will like this:\n");
	TraversalLinkNode(Head);
	return 0;
}
