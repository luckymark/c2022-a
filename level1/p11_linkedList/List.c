#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

typedef struct ListNode
{
	ElementType Data;
	struct ListNode* Next;
}Node, * PNode;

PNode CreateList();
void TraverseList(PNode List);



int main()
{
	PNode List = CreateList();
	TraverseList(List);
	return 0;
}

PNode CreateList()
{
	PNode PHead, PTail;
	PHead = (PNode)malloc(sizeof(Node));
	if (PHead == NULL)
	{
		printf("头节点内存空间开辟失败\n");
		exit(-1);
	}
	
	PTail = PHead;
	PTail->Next = NULL;
	int i = 0;
	int len = 0;
	printf("请输入待存放结点个数:");
	scanf_s("%d", &len);
	for (i = 0; i < len; i++)
	{
		PNode PNew = (PNode)malloc(sizeof(Node));
		if (PNew == NULL)
		{
			printf("新结点创建失败\n");
			exit(-1);
		}
		printf("请输入第%d个数:", i + 1);
		scanf_s("%d", &(PNew->Data));
		PNew->Next = NULL;
		PTail->Next = PNew;
		PTail = PNew;
	}
	printf("链表创建成功\n");
	return PHead->Next;
}

void TraverseList(PNode List)
{
	PNode P = List;
	printf("遍历链表的值为:");
	if (P == NULL)
	{
		printf("链表为空\n");
	}
	while (P != NULL)
	{
		printf("%d ", P->Data);
		P = P->Next;
	}
	printf("\n");
}


//到这里是创建和遍历
