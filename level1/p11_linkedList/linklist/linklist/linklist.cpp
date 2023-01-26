/*题目：单向链表
功能要求：
1. 在 main 函数中创建一个单向链表；
1. 遍历该链表，依次现实各节点的 value；
1. 将该链表所有节点反序；
1. 在该链表中查找第一个值为 5 的节点，如果找到则返回该节点的序号，否则返回－1；
1. 查找下一个值为 5 的节点，返回值同上；*/
//先复制一份链表，再将指针的指向反序

#include <stdio.h>
#include <malloc.h>

int main() {
	const int numOfLinklist = 10;
	//make a linklist
	struct linklist {
		int value;
		struct linklist *next;
	};
	struct linklist head = {0,NULL};
	linklist * temp =&head;
	for (int i = 1; i < numOfLinklist;++i) {
		linklist* p = (linklist*)malloc(sizeof(linklist));
		if (i!=7) {
			p->value = i;
		}
		else {
			p->value = 5;
		}
		p->next = NULL;
		temp->next = p;
		temp = p;
	}
	temp = head.next;
	//copy a linklist
	struct linklist headNew = { 0,NULL };
	linklist* tempNew = &headNew;
	for (int i = 1; i < numOfLinklist; ++i) {
		linklist* p = (linklist*)malloc(sizeof(linklist));
		p->value = (temp->value);
		p->next = NULL;
		tempNew->next = p;
		temp= temp->next;
		tempNew = tempNew->next;
	}
	tempNew = headNew.next;
	struct linklist* last = NULL;
	for (int i = 1; i < numOfLinklist-1;++i) {
		tempNew = tempNew->next;
	}
	last = tempNew;
	for (int i = numOfLinklist; i >1 ;--i) {
		tempNew = headNew.next;
		struct linklist* fanxu=tempNew;
		for (int j = 1; j < i-2;++j) {
			tempNew = tempNew->next;
		}
		fanxu = tempNew;
		(tempNew->next)->next= fanxu;
	}
	//寻找数据
	temp = head.next;
	int count = 0;
	for (int i = 1; i < numOfLinklist;++i) {
		if ((temp->value)==5) {
			count++;
			printf("data=5 : number=%d ; count=%d\n",1+i,count);
		}
		temp = temp->next;
	}
	if (count==0) {
			printf("num is not find\n");
		}
	return 0;
}