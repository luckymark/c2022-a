#include "Á´±í.h"


void turn(Node* node)
{
    Stack* stack = createStack(n);
    Node* sp = node;
    while (sp->next != NULL)
    {
        sp = sp->next;
        push(stack,sp->data);
    }
    sp = node;
    while (sp->next != NULL)
    {
        sp = sp->next;
        sp->data = pop(stack);
    }
    free(stack);
}

int pop(Stack* stack) 
{
    return stack->data[--stack->sp];
}

void push(Stack* stack, int item)
{
    stack->data[stack->sp++] = item;
}

Stack* createStack(int size) 
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->sp = 0;
    stack->data = (int*)malloc(sizeof(int) * size);
    return stack;
}