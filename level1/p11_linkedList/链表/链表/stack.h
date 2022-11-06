#pragma once
typedef struct {
    int* data;
    int sp;
} Stack;
Stack* createStack(int size);
void push(Stack* stack, int i);
int pop(Stack* stack);
void freestack(Stack* stack);