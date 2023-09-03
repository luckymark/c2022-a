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
        printf("�����%d���ڵ����",i+1);
        scanf_s("%d",&number);
        old=insert(number,old);
    }
    display(old);
    new=insertTop(old,new);
    printf_s("����old�����������ǣ�\n");
    display(new);
    printf("%d\n",search(old));
    level= search(old);
    printf("%d\n", search1(old));
    system("pause");
    return 0;
}

list * insert(int number,list *root){
    list *current,*node;//�½ڵ�
    node = (list *)malloc(sizeof(list));
    node->data = number;
    node->next = NULL;
    current = root;
    if(current == NULL){
        //����ǿձ���ô�½ڵ���Ǹ��ڵ�
        root = node;
    }else{
        //���򣬽��������������󣬽��½ڵ����������β
        while(current -> next != NULL){
            //����������һ���ڵ㣬��������
            current = current -> next;
        }
        current -> next = node;
    }
    return root;
}

list *insertTop(list *head,list *root) {
    list *temp, *node;
    temp = head;
    //�������õ��Ľڵ���뵽root�����ͷ��㣬�Ӷ�ʵ������
    while (temp != NULL) {
        node = (list *) malloc(sizeof(list));
        node->data = temp->data;
        node->next = NULL;
        if (root == NULL) {
            //����ǿ�������ô�½ڵ����ͷ���
            root = node;
        } else {
            //������ǿ�������ôԭ����ͷ�������½ڵ�ĺ���,�½ڵ����ͷ���
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