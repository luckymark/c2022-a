#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
    int data;
    LinkNode* next;
}*Node;

void TravelsalLinklist(int n, Node headNode) {
    Node temp = headNode;

    for (int i = 1; i <= n; i++) {
        headNode = headNode->next;
        printf("第%d个节点元素为%d\n", i, temp->data);
        temp = temp->next;
    }
}

Node ReverseLinklist(int n, Node headNode) {
    Node front = (Node)malloc(sizeof(struct LinkNode));
    Node temp = (Node)malloc(sizeof(struct LinkNode));
    Node behind = headNode->next;
    front = headNode;

    while (!behind) {
        if (headNode == NULL || headNode->next == NULL) {
            return headNode;
        }
        else {
            temp = behind;
            behind = temp->next;
            temp->next = front;
            front->next = NULL;
            front = temp;
        }
        headNode = temp;
        return headNode;
    }
}

int FindInLinklist(int m, Node headNode) {
    Node temp = headNode;
    int i = 1;

    while (temp->next) {
        temp = temp->next;
        if (temp->data == m) {
            return i;
        }
        i++;
    }
    return -1;
}

int main()
{
    Node headNode = NULL;
    Node tail = NULL;
    int n, i;

    printf("The length of the linklist：\n");
    scanf_s("%d", &n);
    for (i = 0; i <= n; i++) {
        Node p = (Node)malloc(sizeof(struct LinkNode));
        p->data = i;
        if (i == 0) {
            tail = p;
            headNode = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
    }

    TravelsalLinklist(n, headNode);
    ReverseLinklist(n, headNode);
    FindInLinklist(5, headNode);

    return 0;
}