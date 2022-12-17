#include <stdio.h>
#include <stdlib.h>
struct listNode
{
	int val;
	struct listNode* next;
};

void printListnode(struct listNode*);

//创建链表 
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
			printf("内存分配失败\n");
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
		scanf("%d", &num);  //wei
	}
	 
		/*while (num != -1)
		{
			p=(struct listNode*)malloc(sizeof(struct listNode));
			if (p == NULL)
		{
			printf("内存分配失败\n");
		}
			p->val=num;
		if(head==NULL)
			{
			head=p;
			}
			else
		    {
	       p->next=head;
	       head=p;	
		}
		} */
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
		printf("第%d个节点的val是%d\n", count, p->val);
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
	list=createList();      //不用一个指针来接creat的返回值，可在外面定义一个head，将**head作为参数传进去；
	printListnode(list);
	relist=reverse(list);
	printListnode(relist);
	recheck(relist);
	serialnumb=check(relist);
	printf("第一个出现5的节点序号是 %d\n", serialnumb);
	printf("第二个出现5的节点序号是 %d\n", recheck(relist));
	system("pause");
}