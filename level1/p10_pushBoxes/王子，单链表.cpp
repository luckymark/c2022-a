#include <stdio.h>
#include<stdlib.h>
//小王子有一天迷上了排队的游戏，桌子上有标号为 1-101−10 的 1010 个玩具，现在小王子将他们排成一列，可小王子还是太小了，他不确定他到底想把那个玩具摆在哪里，直到最后才能排成一条直线，求玩具的编号。已知他排了 MM 次，每次都是选取标号为 XX 个放到最前面，求每次排完后玩具的编号序列。

//要求一：采用单链表解决

//输入描述
//第一行是一个整数 MM，表示小王子排玩具的次数。

//随后 MM 行每行包含一个整数 XX，表示小王子要把编号为 XX 的玩具放在最前面。

//输出描述
//共 MM 行，第 ii 行输出小王子第 ii 次排完序后玩具的编号序列。
typedef struct Node
{
	int data;
	Node* next;
};
//创建链表
Node* creatlist()
{
	Node* headNode = (Node*)malloc(sizeof(Node));
	if (headNode)
	{
		headNode->data;
	}
	headNode->next = NULL;
	return headNode;
}
//创建节点
Node* creatNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//尾插节点
void tailenter(Node* headNode, int data)
{
	Node* newNode = creatNode(data);
	while (headNode->next != NULL)
	{
		headNode = headNode->next;
	}
	headNode->next = newNode;
}
//打印链表
void printList(Node* headNode)
{
	Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		printf("%d ", pMove->data);
		pMove = pMove->next;
	}
}
//对链表内容进行搜索
void lookfordata(Node* headNode, int data)
{
	Node* newNode = headNode;
	Node* newNodenext = headNode->next;
	Node* posNode = creatNode(data);
	while (newNodenext->data != data)
	{
		newNode = newNodenext;
		newNodenext = newNode->next;
	}
	newNode->next = newNodenext->next;
	free(newNodenext);
	posNode->next = headNode->next;
	headNode->next = posNode;
}

int main()
{
	int M;
	int N[100];
	Node*headNode=creatlist();
	//初始化王子的玩具
	for (int i = 1; i <= 10; i++)
	{
		tailenter(headNode, i);
	}
	lookfordata(headNode, 5);
	scanf_s("%d", &M);
	for (int i = 0; i < M; i++)
	{
		scanf_s("%d", &N[i]);
		lookfordata(headNode, N[i]);
		if (i != M)
		{
			printList(headNode);
			printf(" ");
		}
		else
		{
			lookfordata(headNode, N[i]);
			printf("\n");
		}
	}
}