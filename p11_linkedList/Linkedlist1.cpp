#include<stdio.h>
#include<stdlib.h>

int arr[21];
int counter;
typedef struct list{
	int num;
	int i;
	struct list *next;
}Ryo;

void linkhead(Ryo**phead, Ryo*pnew)
{
	Ryo*pmove=*phead;
	if(*phead==NULL)
	{
		*phead=pnew;
		pnew->next=NULL;
	}
	else
	{
		while(pmove->next!=NULL)
			pmove=pmove->next;
		pmove->next=pnew;
		pnew->next=NULL;
	}
}
void linkprint(Ryo*head)
{
	Ryo *pmove;
	pmove=head;
	while(pmove!=NULL)
	{
		printf("%d ",pmove->num);
		pmove=pmove->next;
	}
	printf("\n");
}
void linkreverse(Ryo **phead)
{
	Ryo *pnow=*phead,*pwill=NULL,*ppro=NULL;
	while(pnow->next!=NULL)
	{
		ppro=pnow->next;
		pnow->next=pwill;
		pwill=pnow;
		pnow=ppro;
	}
	pnow->next=pwill;
	*phead=pnow;
}
void linkseek(Ryo *head,int num)
{
	Ryo *pmove;
	pmove=head;
	while(pmove!=NULL)
	{
		if(pmove->num==num)
			arr[++counter]=pmove->i;
		pmove=pmove->next;
	}
	if(counter==0)
		arr[++counter]=-1;
}
int main()
{
	Ryo *head=NULL,*pnew=NULL;
	int n;
	scanf_s("%d",&n);
	for(int i=1;i<=n;i++)
	{
		pnew=(Ryo*)malloc(sizeof(Ryo));
		scanf_s("%d", &pnew->num);
		pnew->i=i;
		linkhead(&head,pnew);
	}
	linkprint(head);
	linkreverse(&head);
	linkprint(head);
	linkseek(head,5);
	for (int i = 1;i <= counter;i++)
		printf("%d \n",arr[i]);
	return 0;
} 
