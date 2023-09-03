#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

//������Ĵ洢�ṹ
typedef struct LNode
{
    ElemType data;
    struct LNode* next;
} LNode, * LinkList;

//��ʼ��
Status InitList(LinkList& L)
{
    L = new LNode;
    L->next = NULL;
    return OK;
}
//����
Status DestroyList(LinkList& L)
{
    LinkList p;
    while (L)
    {
        p = L;
        L = L->next;  //һ����ɾ
        delete p;
    }
    return OK;
}
//���
Status ClearList(LinkList L)
{
    LinkList p, q;
    p = L->next;     //pָ���һ�����
    while (p)        //û����β
    {
        q = p->next; delete p; p = q;
    }
    L->next = NULL;  //ͷ���ָ����Ϊ��
    return OK;
}
//�󳤶�
int  ListLength(LinkList L)
{  //����L������Ԫ�ظ���
    LinkList p = L->next; //pָ���һ�����
    int count = 0;
    while (p) {//����������,ͳ�ƽ����
        ++count;
        p = p->next;
    }
    return count;
}
//�ж��Ƿ�Ϊ��
bool ListEmpty(LinkList L)
{//��LΪ�ձ��򷵻�true�����򷵻�false
    if (L->next == NULL)
        return true;
    else
        return false;
}
//ȡֵ
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
//��ֵ����
LNode* LocateElem(LinkList L, ElemType e)
{
    LinkList p = L->next;
    while (p && p->data != e)
        p->next;
    return p;
}
//����
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
//ɾ��
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
//ǰ�巨����������
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
//��巨����������
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
//�����ĸ�Ԫ�ص�ǰ��
Status ListPrior(LinkList L, ElemType cur_e, ElemType* pre_e)
{
    LinkList q = L->next;//��һ�����
    if (!q)//������Ϊ��
        return ERROR;
    LinkList p = q->next;//�ڶ������
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
//�����ĸ�Ԫ�صĺ��
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
//��ʾ���Ա�
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

void Reverse(LinkList L) {    //����ͷ�ڵ�
    if (L->next == NULL) {
        cout << "���ǿձ�" << endl;
        return;
    }
    else if (L->next->next == NULL) {
        cout << "ֻ��һ��Ԫ�أ����跴ת��" << endl;
        return;
    }
    else {
        LinkList p = L->next;//��ͷ�����Ϊ��1��Ԫ�أ���ô�����׽ڵ����Ϊ��2��Ԫ��
        LinkList q;
        /*���ڶ���Ԫ�غ����Ԫ�����β����һ��Ԫ�غ���*/
        while (p->next != NULL) {
            //����p2һֱ�̶���ԭʼ�ĵ�2��Ԫ��
            //����rһֱ����ȡ������ԭʼ�ĵ�2��Ԫ���Ҳ���Ǹ�Ԫ�ص�ַ
            q = p->next;
            p->next = q->next;

            //��r���뵽ͷ������
            q->next = L->next;
            L->next = q;
        }
        //����벻��ͷ���ĵ������������ǣ������޸�ͷָ����
    }
}
   
void show_help()
{
    cout << "******* Data Structure ******" << endl;
    cout << "1----������Ա�" << endl;
    cout << "2----�ж����Ա��Ƿ�Ϊ��" << endl;
    cout << "3----�����Ա���" << endl;
    cout << "4----��ȡ���Ա�ָ��λ��Ԫ��" << endl;
    cout << "5----��ǰ��" << endl;
    cout << "6----����" << endl;
    cout << "7----�����Ա�ָ��λ�ò���Ԫ��" << endl;
    cout << "8----ɾ�����Ա�ָ��λ��Ԫ��" << endl;
    cout << "9----��ʾ���Ա�" << endl;
    cout << "10----����Ԫ��λ��" << endl;
    cout << ".----���Ա���" << endl;
    cout << "     �˳�������0" << endl;

}
int main()
{
    char operate_code;
    show_help();
    LinkList L;       //��һ��ͷ�ڵ�
    InitList(L);
    ElemType e;
    int i;
    while (1)
    {
        cout << "�������������:";
        cin >> operate_code;
        if (operate_code == '1')
        {
            cout << "The list has been cleared." << endl;
            ClearList(L);//���ò�������

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
            cout << "������ָ����λ�ã�" << endl;
            cin >> i;
            if (GetElem(L, i, e) == 1) cout << "���λ�õ������ǣ�" << e << endl;
            else cout << "error" << endl;
        }
        else if (operate_code == '5')
        {
            int n;
            cout << "��������������ĸ�Ԫ�ص�ǰ����" << endl;
            cin >> n;
            if (ListPrior(L, n, &e) == 1) cout << n << "��ǰ��Ϊ��" << e << endl;
            else cout << "error" << endl;
        }
        else if (operate_code == '6')
        {
            int n;
            cout << "��������������ĸ�Ԫ�صĺ�̣�" << endl;
            cin >> n;
            if (ListNext(L, n, &e) == 1) cout << n << "�ĺ��Ϊ��" << e << endl;
            else cout << "error" << endl;
        }
        else if (operate_code == '7')
        {
            cout << "���������Ԫ�ؼ���λ�ã�" << endl;
            cin >> e >> i;
            if (ListInsert(L, i, e) == ERROR) cout << "�������벻�Ϸ�" << endl;

        }
        else if (operate_code == '8')
        {
            cout << "����������Ҫɾ���ĸ�λ�õ�Ԫ�أ�" << endl;
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
            cout << "����������Ҫ���ҵ�Ԫ�أ�" << endl;
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
            cout << "\n��������󣡣���" << endl;
            show_help();
        }
    }
    //�����������Ա�������Destroy_List(L);
    DestroyList(L);
    return 0;
}
