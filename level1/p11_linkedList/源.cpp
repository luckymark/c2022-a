#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
	int value;
	struct _node *next;
}Node;
typedef struct {
	Node* head;
	Node* tail;
}List;

void creatLinkedlist(List *list) {
	int x=0;
	while (1) {
		scanf_s("%d", &x);
		if (x == -1) break;
		Node* p = (Node*)malloc(sizeof(Node));
		if (p) {
			p->value = x;
			p->next = NULL;
		}
		if (list->tail) {
			while ((list->tail)->next) {
				list->tail = (list->tail)->next;
			}
			(list->tail)->next = p;
		}
		else {
			list->head = p;
			list->tail = p;
		}
	} 
}
void reverse(List *list) {
	Node* p1 = list->head;
	Node* p2 = p1->next;
	Node* p3 = NULL;
	while (p2) {
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	list->tail = list->head->next = NULL;
	list->head = p1;
}
int searchFirst(List list,int target) {
	Node* p = list.head;
	int n = 1;
	while (p) {
		if (p->value == target) {
			return n;
		}
		p = p->next;
		n++;
	}
	return -1;
}
int searchSecond(List list, int target) {
	Node* p = list.head;
	int n = 1, flag = 0;
	while (p) {
		if (p->value == target) {
			flag++;
			if(flag==2) return n;
		}
		p = p->next;
		n++;
	}
	return -1;
}
int main() {
	List list;
	list.tail = list.head = NULL;
	
	creatLinkedlist(&list);
	Node* p1 = list.head;
	while (p1) {
		printf("%d ", p1->value);
		p1 = p1->next;
	}
	printf("\n");

	reverse(&list);
	Node* p2 = list.head;
	while (p2) {
		printf("%d ", p2->value);
		p2 = p2->next;
	}
	printf("\n");

	/*printf("%d\n", searchFirst(list, 5));
	printf("%d\n", searchSecond(list, 5));*/
	return 0;
}