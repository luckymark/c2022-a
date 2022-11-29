#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
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
    free(stack);
}