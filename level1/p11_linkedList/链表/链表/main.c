#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"node.h"

int main()
{
	Node* p = createnode();
	addnode(2, p, 100);
	printnode(p);
	return 0;
}