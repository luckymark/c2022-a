#include <stdio.h>
#include <malloc.h>

typedef struct Link {
    int data;
    struct Link *next;
}list;
int level;

void display(list*m){
    list *node;
    node=m;
    while (node!=NULL){
        if (node->next!=NULL){
            printf_s("%d->",node->data);
        } else {
            printf_s("%d\n", node->data);
        }
        node=node->next;
    }
}

list * insert(int number,list *root);
list * insertTop(list *head,list *root);
int search(list *node);
int search1(list *node);

int main() {
    int i,number;
    list *old,*new;
    old=new=NULL;
    old= malloc(sizeof(*old));
    if(old == NULL){
        return NULL;
    }
    old->next=NULL;
    for (i = 0; i < 5; ++i) {
        printf("输入第%d个节点的数",i+1);
        scanf_s("%d",&number);
        old=insert(number,old);
    }
    display(old);
    new=insertTop(old,new);
    printf_s("链表old的逆序链表是：\n");
    display(new);
    printf("%d\n",search(old));
    level= search(old);
    printf("%d\n", search1(old));
    system("pause");
    return 0;
}

list * insert(int number,list *root){
    list *current,*node;//新节点
    node = (list *)malloc(sizeof(list));
    node->data = number;
    node->next = NULL;
    current = root;
    if(current == NULL){
        //如果是空表，那么新节点就是根节点
        root = node;
    }else{
        //否则，将遍历到链表的最后，将新节点插入在链表尾
        while(current -> next != NULL){
            //如果不是最后一个节点，继续遍历
            current = current -> next;
        }
        current -> next = node;
    }
    return root;
}

list *insertTop(list *head,list *root) {
    list *temp, *node;
    temp = head;
    //将遍历得到的节点插入到root链表的头结点，从而实现逆序
    while (temp != NULL) {
        node = (list *) malloc(sizeof(list));
        node->data = temp->data;
        node->next = NULL;
        if (root == NULL) {
            //如果是空链表，那么新节点就是头结点
            root = node;
        } else {
            //如果不是空链表，那么原来的头结点就在新节点的后面,新节点就是头结点
            node->next = root;
            root = node;
        }
        return root;
    }
}

int search(list *node){
    int i;
    for (i = 0; i < 6; ++i) {
        if(node->data==5) {
            return i + 1;
        }
    node=node->next;
    }
    return -1;
}

int search1(list *node){
    for (int i = 0; i < level; ++i) {
        node=node->next;
    }
    for (int j = 0; j < 6-level; ++j) {
        if(node->data==5) {
            return j + 1;
        }
        node=node->next;
    }
    return -1;
}