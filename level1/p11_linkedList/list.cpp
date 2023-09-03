# define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
# include<malloc.h>

typedef struct Linklist {
	int data;
	struct  Linklist* next;
}Linklist;

Linklist* linklistcreate(int n) {
    Linklist* head, * node, * end;
    head = (Linklist*)malloc(sizeof(Linklist));
    end = head;
    for (int i = 0; i < n; i++) {
        node = (Linklist*)malloc(sizeof(Linklist));
        printf("请逐个输入数值(输入一个后按回车键)");
        scanf("%d", &node->data);
        end->next = node;
        end = node;
    }
    end->next = NULL;
    return head;
}
void ptintflist(Linklist* head)
{
    Linklist* t = head;
    while (t->next != NULL) {
        t = t->next;
        printf("   %d ", t->data);
    }
    printf("\n");
}
void insert(Linklist* head, int n,int da)
{
    int i = 0;
    Linklist* t = head;
    Linklist* node;
    node= (Linklist*)malloc(sizeof(Linklist));
    node->data = da;
    while (t->next != NULL && i < n) {
        t = t->next;
        node->next = t->next;
        t->next = node;
        i++;
    }
}
void reverselist(Linklist* head,int n)
{
    int i = 0;
    Linklist* t = head;
    while (t->next != NULL) {
        t = t->next;
    }
    while (n)
    {
        Linklist* z = head;
        Linklist* y = head;
        if (n >= 2)
        {
            int x = 0;
            while (x < n) {
                z = z->next;
                x++;
            }
            int w = 0;
            while (w < n-1) {
                y = y->next;
                w++;
            }
            z->next = y;
            if (n == 2)
                y->next= NULL;
        }
        n--;
    }
    head->next = t;
}
Linklist* lookfor5(Linklist* head)
{
    Linklist* z = head;
    while (z->next!=NULL) {
        z = z->next;
        if((z->data)==5)
        break;
    }
    if (z->data == 5)
        return z;
    else
    return NULL;
}
Linklist* lookfor5still(Linklist* head)
{
    Linklist* z = head;
    while (z->next != NULL) {
        z = z->next;
        if ((z->data) == 5)
            break;
    }
    if (z->data == 5)
        return z;
    else
        return NULL;
}
int main()
{
    int n,num=1;
    Linklist* head=NULL ,*median= NULL,*t=NULL;
    printf("输入个数\n");
    scanf("%d", &n);
    head = linklistcreate(n);
    ptintflist( head);
    reverselist(head,n);
    ptintflist(head);
   median= lookfor5(head);
   t = head;
   if (median != NULL) {
       while (t->next != median)
       {
           t = t->next;
           num++;
       }
       printf("该节点序号为%d\n", num);
   }
   else
       printf("没找到\n");
   while (t->next != NULL)
   {
       t=lookfor5still(median);
       if (t != NULL) {
         num += 1;
           while (median->next != t)
           {
               median = median->next;
               num++;
           }
           printf("该节点序号为%d\n", num);
           median = median->next;
       }
       else
           printf("没有5了");
   }

    return 0;
}