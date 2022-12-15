#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int data;
	struct Node* next;
}Node;

typedef struct {
	int* data;
	int sp;
} Stack;


static int n = 9;
static int arr[] = { 1,2,3,4,5,6,7,8,9 };

void inh(Node* node,int i);
void inb(Node* node,int i);
int search(Node* node, int i);









void turn(Node* node);
int pop(Stack* stack);
void push(Stack* stack, int item);
Stack* createStack(int size);//Õ»Çø·´×ª