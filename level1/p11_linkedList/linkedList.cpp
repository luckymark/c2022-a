#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode* List;

// 定义链表结构体
struct ListNode
{
    int val;
    // 后驱指针
    List next;
};
// 链表结点的构造方法
List create_node(int val)
{
    // 使用malloc函数分配空间
    List L = (List)malloc(sizeof(struct ListNode));
    L->val = val;
    L->next = NULL;
    return L;
}

List insert_node(List L, int val)
{
    // 首先将该值封装成一个链表结点
    List insert_node = create_node(val);
    // 头插法插入结点
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

    printf("请输入链表长度:");
    scanf_s("%d", &n);
    // 初始化一个链表
    List head = NULL;
    printf("请依次输入链表结点数据(用空格隔开):");
    while (n--)
    {
        scanf_s("%d", &num);
        // 插入到链表后面
        head = insert_node(head, num);
    }
    printf("反序前链表序列:");
    show_list(head);
    head = reverse_list(head);
    printf("反序后链表序列:");
    show_list(head);

    res = find_num(head, 5, 1);
    printf("第一次5出现的位置为:%d\n", res);
    res = find_num(head, 5, 2);
    printf("第二次5出现的位置为:%d\n", res);

    return 0;
}
