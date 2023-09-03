#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

//单链表的存储结构
typedef struct LNode
{
    ElemType data;
    struct LNode* next;
} LNode, * LinkList;

//初始化
Status InitList(LinkList& L)
{
    L = new LNode;
    L->next = NULL;
    return OK;
}
//销毁
Status DestroyList(LinkList& L)
{
    LinkList p;
    while (L)
    {
        p = L;
        L = L->next;  //一个个删
        delete p;
    }
    return OK;
}
//清空
Status ClearList(LinkList L)
{
    LinkList p, q;
    p = L->next;     //p指向第一个结点
    while (p)        //没到表尾
    {
        q = p->next; delete p; p = q;
    }
    L->next = NULL;  //头结点指针域为空
    return OK;
}
//求长度
int  ListLength(LinkList L)
{  //返回L中数据元素个数
    LinkList p = L->next; //p指向第一个结点
    int count = 0;
    while (p) {//遍历单链表,统计结点数
        ++count;
        p = p->next;
    }
    return count;
}
//判断是否为空
bool ListEmpty(LinkList L)
{//若L为空表，则返回true，否则返回false
    if (L->next == NULL)
        return true;
    else
        return false;
}
//取值
Status GetElem(LinkList L, int i, ElemType& e)
{
    LinkList p = L->next;
    int j = 1;
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i) return ERROR;
    e = p->data;
    return OK;
}
//按值查找
LNode* LocateElem(LinkList L, ElemType e)
{
    LinkList p = L->next;
    while (p && p->data != e)
        p->next;
    return p;
}
//插入
Status ListInsert(LinkList& L, int i, ElemType &e)
{
    LinkList p = L;
    int j = 0;
    while (p && (j < i - 1))
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1) 
        return ERROR;
    LinkList s = new LNode;      //?
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
//删除
Status ListDelete(LinkList& L, int i)
{
    LinkList p = L;
    int j = 0;
    while ((p->next) && (j < i - 1))
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || (j > i - 1)) 
        return ERROR;
    LinkList q = p->next;
    p->next = q->next;
    delete q;
    return OK;
}
//前插法创建单链表
void CreateList_H(LinkList& L, int n)
{
    L = new LNode;
    L->next = NULL;
    for (int i = 0; i < n; ++i)
    {
        LinkList p = new LNode;
        cin >> p->data;
        p->next = L->next;
        L->next = p;
    }
}
//后插法创建单链表
void CreateList_R(LinkList& L, int n)
{
    L = new LNode;
    L->next = NULL;
    LinkList r = L;
    for (int i = 0; i < n; ++i)
    {
        LinkList p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}
//查找哪个元素的前驱
Status ListPrior(LinkList L, ElemType cur_e, ElemType* pre_e)
{
    LinkList q = L->next;//第一个结点
    if (!q)//若链表为空
        return ERROR;
    LinkList p = q->next;//第二个结点
    while (p)
    {
        if (p->data == cur_e)
        {
            *pre_e = q->data;
            return OK;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }
    return ERROR;
}
//查找哪个元素的后继
Status ListNext(LinkList L, ElemType cur_e, ElemType* next_e)
{
    LinkList p = L->next;
    while (p)
    {
        if (p->data == cur_e && p->next)
        {
            *next_e = p->next->data;
            return OK;
        }
        else
            p = p->next;
    }
    return ERROR;
}
//显示线性表
void DisplayList(LinkList L)
{
    LinkList p = L->next;
    while (p)
    {
        cout << p->data << "  ";
        p = p->next;
    }
    cout << endl;
    return;
}

void Reverse(LinkList L) {    //带有头节点
    if (L->next == NULL) {
        cout << "这是空表！" << endl;
        return;
    }
    else if (L->next->next == NULL) {
        cout << "只有一个元素，无需反转！" << endl;
        return;
    }
    else {
        LinkList p = L->next;//将头结点视为第1个元素，那么数据首节点就视为第2个元素
        LinkList q;
        /*将第二个元素后面的元素依次插入第一个元素后面*/
        while (p->next != NULL) {
            //由于p2一直固定在原始的第2个元素
            //所以r一直都是取紧接着原始的第2个元素右侧的那个元素地址
            q = p->next;
            p->next = q->next;

            //将r插入到头结点后面
            q->next = L->next;
            L->next = q;
        }
        //最后与不带头结点的单链表的区别就是，不用修改头指针了
    }
}
   
void show_help()
{
    cout << "******* Data Structure ******" << endl;
    cout << "1----清空线性表" << endl;
    cout << "2----判断线性表是否为空" << endl;
    cout << "3----求线性表长度" << endl;
    cout << "4----获取线性表指定位置元素" << endl;
    cout << "5----求前驱" << endl;
    cout << "6----求后继" << endl;
    cout << "7----在线性表指定位置插入元素" << endl;
    cout << "8----删除线性表指定位置元素" << endl;
    cout << "9----显示线性表" << endl;
    cout << "10----查找元素位置" << endl;
    cout << ".----线性表反序" << endl;
    cout << "     退出，输入0" << endl;

}
int main()
{
    char operate_code;
    show_help();
    LinkList L;       //创一个头节点
    InitList(L);
    ElemType e;
    int i;
    while (1)
    {
        cout << "请输入操作代码:";
        cin >> operate_code;
        if (operate_code == '1')
        {
            cout << "The list has been cleared." << endl;
            ClearList(L);//调用操作函数

        }
        else if (operate_code == '2')
        {
            if (ListEmpty(L))
                cout << "The list is empty." << endl;
            else
                cout << "The list is not empty." << endl;

        }
        else if (operate_code == '3')
        {
            cout << "The length of list is:" << ListLength(L) << endl;

        }
        else if (operate_code == '4')
        {
            cout << "请输入指定的位置：" << endl;
            cin >> i;
            if (GetElem(L, i, e) == 1) cout << "这个位置的数据是：" << e << endl;
            else cout << "error" << endl;
        }
        else if (operate_code == '5')
        {
            int n;
            cout << "请输入你想查找哪个元素的前驱：" << endl;
            cin >> n;
            if (ListPrior(L, n, &e) == 1) cout << n << "的前驱为：" << e << endl;
            else cout << "error" << endl;
        }
        else if (operate_code == '6')
        {
            int n;
            cout << "请输入你想查找哪个元素的后继：" << endl;
            cin >> n;
            if (ListNext(L, n, &e) == 1) cout << n << "的后继为：" << e << endl;
            else cout << "error" << endl;
        }
        else if (operate_code == '7')
        {
            cout << "请输入插入元素及其位置：" << endl;
            cin >> e >> i;
            if (ListInsert(L, i, e) == ERROR) cout << "您的输入不合法" << endl;

        }
        else if (operate_code == '8')
        {
            cout << "请输入你想要删除哪个位置的元素：" << endl;
            cin >> i;
            if (ListDelete(L, i) == ERROR)  cout << "error" << endl;

        }
        else if (operate_code == '9')
        {
            cout << "The contents of the list are:" << endl;
            DisplayList(L);

        }
        else if (operate_code == '10')
        {
            cout << "请输入你想要查找的元素：" << endl;
            cin >> i;
            LocateElem(L,i);
        }
        else if (operate_code == '.')
        {
            cout << "The new contents of the list are:" << endl;
            Reverse(L);
            DisplayList(L);
        }
        else if (operate_code == '0')
        {
            break;
        }
        else
        {
            cout << "\n操作码错误！！！" << endl;
            show_help();
        }
    }
    //调用销毁线性表函数，如Destroy_List(L);
    DestroyList(L);
    return 0;
}
