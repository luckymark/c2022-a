#pragma once
typedef struct NODE {
	int data;
	struct NODE* next;
}Node;
Node* createnode();
Node* addfirstnode(Node* head, int data2);
void printnode(Node* p);
void addnode(int location, Node* p, int data2);
void reversenode(Node* p);
int findDataNode(Node* p, int data2);
void deletenode(Node* p, int location);