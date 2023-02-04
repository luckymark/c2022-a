#pragma once
#include<errno.h>
typedef struct {
    int* data;
    int sp;
} Stack;
Stack* createStack(int size);
void push(Stack* stack, int i);
int pop(Stack* stack);
void freestack(Stack* stack);
typedef struct QUEUE {
	int* data;
	int Tail, Head;
	int sizeofqueue;
}Queue;
Queue* createqueue(int size);
void push2(Queue* p, int num);
int pop2(Queue* p);
void freequeue(Queue* p);