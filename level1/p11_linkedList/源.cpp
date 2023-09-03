#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;           
    struct Node* next;   
} Node;

int main() {

    Node* head = (Node*)malloc(sizeof(Node));
    head->value = 0;
    head->next = NULL;

  
    Node* tail = head;
    for (int i = 1; i <= 10; i++) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->value = i;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

   
    Node* current = head->next;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    
    Node* prev = NULL;
    current = head->next;
    while (current != NULL) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head->next = prev;

    current = head->next;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    current = head->next;
    int index = 1;
    while (current != NULL) {
        if (current->value == 5) {
            printf("�ҵ���ֵΪ 5 �Ľڵ㣬���Ϊ %d\n", index);
            break;
        }
        current = current->next;
        index++;
    }
    if (current == NULL) {
        printf("δ�ҵ�ֵΪ 5 �Ľڵ�\n");
        index = -1;
    }

  
    while (current != NULL) {
        current = current->next;
        index++;
        if (current != NULL && current->value == 5) {
            printf("�ҵ�����һ��ֵΪ 5 �Ľڵ㣬���Ϊ %d\n", index);
            break;
        }
    }
    if (current == NULL) {
        printf("δ�ҵ���һ��ֵΪ 5 �Ľڵ�\n");
        index = -1;
    }


    current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
