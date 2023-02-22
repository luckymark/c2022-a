#include<stdio.h>
#include<stdlib.h>


typedef struct Node
{
	int data;
	struct Node* next;
} Node_a;

//��������
Node* createList()
{
	Node* headNode = (struct Node*)malloc(sizeof(Node));
	//headNode:�����ͷ
	//�ṹָ���ɽṹ�����
	if(headNode)
		headNode->data;//�Ȳ���ʼ���������ɱ���
	headNode->next = NULL;
	return headNode;
}

//�������
Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode)
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//��ӡ����
void printList(Node* headNode)
{
	Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		printf("%d\n", pMove->data);
		pMove = pMove->next;
	}
}

//�������ͷ��������
void insertNode_byhead(struct Node* headNode, int data)
{
	Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}


//�������β��������
void insertNode_bytail(Node* headNode, int data)
{
	Node* newNode = createNode(data);
	while ((headNode->next)!=NULL)
	{
		headNode = headNode->next;
	}
	headNode->next = newNode;

}

//������ڶ�����������
void insertNode_bysecond(Node* headNode, int data)
{
	Node* newNode = createNode(data);

	newNode->next = headNode->next->next;
	headNode->next->next = newNode;
}

//��ת����
void up_and_down()
{

}


//������ɾ������
void deleteNode_bypoint(Node* headNode, int posdata)
{
	Node* posNode = headNode->next;
	Node* posNodedront = headNode;
	if (posNode == NULL) {
		printf("error,����Ϊ��");
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