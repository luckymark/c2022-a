#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include"stack.h"

int pop(Stack* stack) {
    return stack->data[--stack->sp];
}

void push(Stack* stack, int item) {
    stack->data[stack->sp++] = item;
}

Stack* createStack(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(0);
    }
    stack->sp = 0;
    stack->data = (int*)malloc(sizeof(int) * size);
    if (stack->data == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(0);
    }
    return stack;
}

void freestack(Stack* stack)
{
    free(stack->data);
    stack->data = NULL;
    free(stack);
    stack = NULL;
}

Queue* createqueue(int size)
{
	Queue* p = (Queue*)malloc(sizeof(Queue));
	if (p == NULL)
	{
		printf("%s", strerror(errno));
		exit(0);
	}
	else
	{
		p->Head = 0;
		p->Tail = 0;
		p->sizeofqueue = size;
		p->data = (int*)malloc(size * sizeof(int));
		if (p->data == NULL)
		{
			printf("%s", strerror(errno));
			exit(0);
		}
	}
	return p;
}

void push2(Queue* p, int num)
{
	p->data[(p->Head++) % (p->sizeofqueue)] = num;
}

int pop2(Queue* p)
{
	return p->data[(p->Tail++) % (p->sizeofqueue)];
}

void freequeue(Queue* p)
{
	free(p->data);
	p->data = NULL;
	free(p);
	p = NULL;
}