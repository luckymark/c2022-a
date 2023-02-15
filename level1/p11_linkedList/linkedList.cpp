#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode* List;

// ��������ṹ��
struct ListNode
{
    int val;
    // ����ָ��
    List next;
};
// ������Ĺ��췽��
List create_node(int val)
{
    // ʹ��malloc��������ռ�
    List L = (List)malloc(sizeof(struct ListNode));
    L->val = val;
    L->next = NULL;
    return L;
}

List insert_node(List L, int val)
{
    // ���Ƚ���ֵ��װ��һ��������
    List insert_node = create_node(val);
    // ͷ�巨������
    insert_node->next = L;
    L = insert_node;
    return L;
}

List reverse_list(List L) {
    List temp = NULL;
    List pHead = NULL;

    while (L != NULL) {
        temp = L;
        L = L->next;
        temp->next = pHead;
        pHead = temp;
    }

    return pHead;
}

void show_list(List L)
{
    while (L != NULL) {
        printf("%d ", L->val);
        L = L->next;
    }
    printf("\n");
}

int find_num(List L, int num, int cnt) {
    int res = 0;
    while (L != NULL) {
        if (L->val == num) {
            cnt--;
            if (cnt == 0) {
                return res;
            }
        }
        res++;
        L = L->next;
    }
    return -1;
}

int main(void)
{
    int n, num, res;

    printf("������������:");
    scanf_s("%d", &n);
    // ��ʼ��һ������
    List head = NULL;
    printf("��������������������(�ÿո����):");
    while (n--)
    {
        scanf_s("%d", &num);
        // ���뵽�������
        head = insert_node(head, num);
    }
    printf("����ǰ��������:");
    show_list(head);
    head = reverse_list(head);
    printf("�������������:");
    show_list(head);

    res = find_num(head, 5, 1);
    printf("��һ��5���ֵ�λ��Ϊ:%d\n", res);
    res = find_num(head, 5, 2);
    printf("�ڶ���5���ֵ�λ��Ϊ:%d\n", res);

    return 0;
}
