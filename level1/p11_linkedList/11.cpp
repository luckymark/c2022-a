#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int value;
	struct node* next;
	int cnt;
}node;
node* makeEmpty(){
	node* head=(node*)malloc(sizeof(node));
	head->next=NULL;
	head->cnt=0;
	return head;
}
node* findEnd(node* list){//返回末尾结点
	while(list->next){
		list=list->next;
	}
	return list;
}
node* findEndFa(node* list){//返回末尾结点的父结点
	while(list->next->next){
		list=list->next;
	}
	return list;
}
void add(node* list,int num){
	if(!list->next){//空链表首次add
	node* nnode=(node*)malloc(sizeof(node));
	list->next=nnode;
	nnode->next=NULL;
	nnode->value=num;
	nnode->cnt=1;
	}else{
	node* nnode=(node*)malloc(sizeof(node));
	node* end=findEnd(list);
	end->next=nnode;
	nnode->next=NULL;
	nnode->value=num;
	nnode->cnt=end->cnt+1;
	}
}
void findNum(node* list,int num){//遍历链表，打印值为num的结点序号，打印-1表示结束
	if(list){
		if(list->value==num){
			printf("%d\n",list->cnt);
		}
		findNum(list->next,num);
	}else{
		printf("-1\n");
		return;
	}
}
void reverse(node* list){//从末尾结点倒退修改回来
	node* newstart=findEnd(list);
	node* fa=findEndFa(list);
	node* end=newstart;
	end->cnt=1;
	while(fa!=list){
		end->next=fa;
		fa->next=NULL;
		fa->cnt=end->cnt+1;
		end=findEnd(list);
		fa=findEndFa(list);
	}
	list->next=newstart;
}
int main(){
	node* list=makeEmpty();
	add(list,1);
	add(list,2);
	add(list,3);
	add(list,5);
	add(list,9);
	add(list,7);
	add(list,5);
	findNum(list,5);
	reverse(list);
	findNum(list,5);
	return 0;
}
