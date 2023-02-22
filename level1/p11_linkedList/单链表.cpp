#include<stdio.h>
#include<stdlib.h>


typedef struct Node
{
	int data;
	struct Node* next;
} Node_a;

//创建链表
Node* createList()
{
	Node* headNode = (struct Node*)malloc(sizeof(Node));
	//headNode:链表表头
	//结构指针变成结构体变量
	if(headNode)
		headNode->data;//先不初始化，保留可变性
	headNode->next = NULL;
	return headNode;
}

//创建结点
Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode)
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//打印链表
void printList(Node* headNode)
{
	Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		printf("%d\n", pMove->data);
		pMove = pMove->next;
	}
}

//向链表表头插入数据
void insertNode_byhead(struct Node* headNode, int data)
{
	Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}


//向链表表尾插入数据
void insertNode_bytail(Node* headNode, int data)
{
	Node* newNode = createNode(data);
	while ((headNode->next)!=NULL)
	{
		headNode = headNode->next;
	}
	headNode->next = newNode;

}

//向链表第二个结点插入结点
void insertNode_bysecond(Node* headNode, int data)
{
	Node* newNode = createNode(data);

	newNode->next = headNode->next->next;
	headNode->next->next = newNode;
}

//反转链表
void up_and_down()
{

}


//向链表删除数据
void deleteNode_bypoint(Node* headNode, int posdata)
{
	Node* posNode = headNode->next;
	Node* posNodedront = headNode;
	if (posNode == NULL) {
		printf("error,链表为空");
	}

}

int main() {
	struct Node* headNodee = createList();
	printf("%d\n", sizeof(Node));
	insertNode_byhead(headNodee, 4);
	insertNode_byhead(headNodee, 451);
	insertNode_byhead(headNodee, 11);


	insertNode_bytail(headNodee, 123);
	insertNode_bytail(headNodee, 456);
	insertNode_bytail(headNodee,789);

	insertNode_bysecond(headNodee, 3);
	insertNode_bysecond(headNodee, 14);
	insertNode_bysecond(headNodee, 15926);

	printList(headNodee);

	return 0;
}