#include <stdio.h>
#include <stdlib.h>
struct listNode
{
	int val;
	struct listNode* next;
};

void printListnode(struct listNode*);

struct listNode* createList()
{
	struct listNode* p = NULL, * tail = NULL, * head = NULL;
	int num;                       
	scanf("%d", &num);
	while (num != -1) 
	{
		p = (struct listNode*)malloc(sizeof(struct listNode));
		if (p == NULL)
		{
			printf("错误\n");
		}
		p->val = num;
		p->next = NULL;
		if (head == NULL)
		{
			head = p;
		}
		else
		{
			tail->next = p;
		}
		tail = p;
		scanf("%d", &num);  
	}
		tail->next = NULL;
		return head;
}

struct listNode* reverse(struct listNode* head)
{
	struct listNode* beg, *end;
	if (head == NULL || head->next == NULL)
	{ 
		return head;
	}
	beg = head;
	end = head->next;
	while (end != NULL)
	{		
		beg->next = end->next;
		end->next = head;
		head = end;
		end = beg->next;
	}
	return head;
}


void printListnode(struct listNode* head)
{
	struct listNode* p;
	int count = 1;
	p = head;
	while (p != NULL)
	{
		printf("第%d个 是%d\n", count, p->val);
		p = p->next;
		count++;
	}
}
void releas(struct listNode** head)
{
	struct listNode* temp;
	if (*head != NULL)
	{
		temp = *head;
		*head = (* head)->next;
		free(temp);
	}
}

int check(struct listNode* head)
{
	struct listNode* p;
	int count = 1;
	p = head;
	while (p != NULL)
	{
		if (p->val== 5)
		{
			return count;
		}
		p = p->next;
		count++;
	}
	return -1;
}


int recheck(struct listNode* head)
{
	struct listNode* p;
	int count = 1;
	int index = 0;
	p = head;
	while (p != NULL)
	{
		if (p->val == 5)
		{
			index++;
		}
		p = p->next;
		if (index == 2)
	    {
		return count;
	    }
	    count++;
	}

	return -1;
}
int main()
{
	int serialnumb;
	struct listNode* list, *relist;
	list=createList();     
	printListnode(list);
	relist=reverse(list);
	printListnode(relist);
	recheck(relist);
	serialnumb=check(relist);
	printf("第一个 %d\n", serialnumb);
	printf("第二个 %d\n", recheck(relist));
	system("pause");
}
