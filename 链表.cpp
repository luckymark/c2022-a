#include<stdio.h>
#include<stdlib.h>
struct Node {
	int value;
	int sequence;
	Node* next;
};

Node*pa;//如果要找两个的话这个指针会停在第一个5那个位置，但也只能在这种作业里面这样搞
Node *head = NULL;
Node*tail = NULL;
int FindaValue(int want);
void diandao(Node* p);



int main() {
	int sequence = 0;

	head = (Node*)malloc(sizeof(Node));
	pa = head;
	scanf("%d", &head->value);
	head->sequence = ++sequence;
	head->next = NULL;


	Node *last = (Node*)malloc(sizeof(Node));
	last = head;
	while (1) {
		Node *p = (Node*)malloc(sizeof(Node));
		scanf("%d", &p->value);
		p->sequence = ++sequence;
		p->next = NULL;
		if (p->value == -1) {
			break;
		}
		last->next = p;
		last = last->next;
	}
	tail = last;

	diandao(head);
	for (Node *p = head; p; p = p->next) {
		printf("%d ", p->value);
	}
	

	int want = 5;
	for (int haveleft = 1; haveleft == 1;) {
		int sequence = FindaValue(want);
		printf("%d ", sequence);
		if (sequence == -1) {
			haveleft = 0;
		}
	}


}


int FindaValue(int want) {
	for (; pa; pa = pa->next) {
		if (pa->value == want) {
			int a = pa->sequence;
			pa = pa->next;
			return a;
		}

	}
	return -1;
}

void diandao(Node* p) {
	Node* p2 = p;
	Node* newhead;
	Node* last = (Node*)malloc(sizeof(Node));
	newhead=last;
	int count = 0, sequence = 0;
	for (Node*p1 = p2; p1; p1 = p1->next) {
		count++;
	}//计算链接个数
	for (int i = 0; i < count; i++) {
		for (Node*p1 = p2; p1; p1 = p1->next) {//遍历的次数有点多，或许可以加一个连到上一个的变量 
			if (p1->sequence == count - sequence) {
				Node*p4 = (Node*)malloc(sizeof(Node));
				p4->value=p1->value;
				p4->sequence = ++sequence;
				p4->next = NULL;
				last->next = p4;
				last = last->next;
			}
		}
	}
	newhead=newhead->next;
	for (Node *p = newhead; p; p = p->next) {
			printf("%d ", p->value);
		}
	
}
