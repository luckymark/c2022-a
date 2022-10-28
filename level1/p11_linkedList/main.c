#include <stdio.h>
#include "LINKEDLIST.h"

int main() {
    int length;
    LinkedList *head;
    scanf("%d",&length);
    getchar();

    head = CreatLinked(length);

    AddValue(head,3,2);

    DelValue(head,2);

    AddValue(head,3,2);

    int a[length];

    int same = FindOneValue(head,5);
    printf("%d\n",same);

    FindAllValue(head,5,a);
    for (int i = 0; i < length; ++i) {
        printf("%d ",a[i]);
    }

    TransNum(head,length);

    PrintLinked(head);

    FreeLinked(head);

    return 0;
}