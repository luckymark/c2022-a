#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int value;
    struct node* next;
}Node,*pNode;

pNode creatlist();
void travellist(pNode List);
pNode reverselist(pNode List);
int search(pNode List);
int searchagain(pNode List, int isfound);
int main() {
    pNode List1;
    pNode List2;
    int isfound;
    List1=creatlist();
    travellist(List1);
    List2 = reverselist(List1);
    travellist(List2);
    isfound=search(List2);
    if (isfound != -1) {
        searchagain(List2, isfound);
    }
}

pNode creatlist() {
    pNode phead, ptail;
    phead = (pNode)malloc(sizeof(Node));
    if (phead == NULL)
    {
        printf("ͷ�ڵ��ڴ�ռ俪��ʧ��\n");
        exit(-1);
    }
    int n;
    ptail=phead;
    ptail->next = NULL;
    printf("�������Ž��ĸ���");
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        pNode p = (pNode)malloc(sizeof(Node));
        if (p == NULL)
        {
            printf("�½ڵ㴴��ʧ��\n");
            exit(-1);
        }
        printf("�������%d����", i + 1);
        scanf_s("%d", &(p->value));
        p->next = NULL;
        ptail->next = p;
        ptail = p;
    }
    ptail = ptail->next;
    printf("�������ɹ�\n");
    return phead->next;
}

void travellist(pNode List) {
    pNode p;
    p = List;
    if (p == NULL) {
        printf("����Ϊ��");
    }
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

pNode reverselist(pNode List) {
    pNode pre, cur, nex;
    pre = NULL;
    cur = List;
    nex = cur->next;
    while (1) {
        cur->next = pre;
        if (nex == NULL) {
            break;
        }
        pre = cur;
        cur = nex;
        nex = nex->next;
    }
    List = cur;
    return List;
}

int search(pNode List) {
    pNode p = List;
    if (p == NULL)
        p = p->next;
    int isfound=0;
    while (p) {
        isfound++;
        if (p->value == 5) {
            printf("Ŀ��ֵ5�Ľڵ�Ϊ%d", isfound);
            return isfound;
        }
        p = p->next;
    }
    return -1;
}
int searchagain(pNode List,int isfound) {
    pNode p;
    p = List;
    if (p == NULL)
        p = p->next;
    for (int i = 0; i < isfound; i++) {
        p = p->next;
    }
    while (p) {
        isfound++;
        if (p->value == 5) {
            printf("��һ��Ŀ��ֵΪ5�Ľڵ�Ϊ%d", isfound);
            return isfound;
        }
        p = p->next;
    }
    return -1;
}