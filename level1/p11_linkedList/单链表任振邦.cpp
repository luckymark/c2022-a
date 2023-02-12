#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int Datatype;
typedef struct Node
{
	Datatype value;
	Node* Next;
	int num;
}ListNode;
int main()
{
	int sum = 0, part = 1, sign = 0;
	Node* head = NULL;
	Node* tail = NULL;
	Node* flag = NULL;
	Node* p = NULL;
	do//创建长度为5的链表
	{
		ListNode* node =(Node*)malloc(sizeof(Node));
		int number = 0;
		scanf_s("%d", &number);
		node->value = number;
		node->Next = NULL;
		node->num = part;
		part++;
		if (head == NULL)
		{
			head = node;
		}
		else
		{
			tail = head;
			while (tail->Next)
			{
				tail = tail->Next;
			}
			tail->Next = node;
		}
		sum++;
	} while (sum < 5);
	flag = head;
	do//输出链表1-5的值
	{
		printf("%d", flag->value);
		flag = flag->Next;
	} while (flag);
	for (p = head; p&&sign<=2; p = p->Next)//search两遍功能
	{
		if (p->value == 5)
		{
			printf("%d", p->num);
			sign++;
		}
		else
		{
			printf("-1");
		}
	}


	system("pause");
	return 0;
}