#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstdlib>
typedef struct data {
	int num;
};
typedef struct List {
	data*information;
	List* next;
}LinkList;

LinkList* create_list(int n) {
	LinkList* head, * normal, * end;
	head = (LinkList*)malloc(sizeof(LinkList));
	head -> information = (data*)malloc(sizeof(data));

	end = head;
	for (int i = 0; i < n; i++) {
		normal = (LinkList*)malloc(sizeof(LinkList));
		normal->information = (data*)malloc(sizeof(data));
		printf("plz enter the val for list\n");
		scanf_s("%d", &normal->information->num);
		end->next = normal;
		end = normal;
	}
	end->next = NULL;
	return head;
}

LinkList*reverse (LinkList* head) {
	LinkList* p;
	LinkList* pn;
	p = head->next;
	pn = p->next;
	head->next = NULL;
	while (pn != NULL) {
		p->next = head;
		head = p;
		p = pn;
		pn = pn->next;
	}
	p->next = head;
	return p;
}
void find(LinkList* head,int val, int contin) {//if contin == 1 it will be continue to find next point that equal val
	int res = 0,index = 0;
	while (head != NULL) {
		if (res == 1 && contin != 1) break;
		if (head->information->num == val) {
			printf("%d ", index);
			res = 1;
		}
		head =  head->next;
		index++;
	}
	if (res == 0) printf("-1");
}
int main() {
	LinkList *head;
	int n;
	printf("plz enter the size of LinkList\n");
	scanf_s("%d", &n);
	head = create_list(n);
	head = reverse(head);
	find(head, 5, 1);
	return 0;
}
