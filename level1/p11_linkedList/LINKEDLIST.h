//
// Created by XuanCheng on 2022/10/28.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

typedef struct LinkedList{
    int number;
    int data;
    struct LinkedList *next;
}LinkedList;

LinkedList * CreatLinked(int length);//创建链表，length为链表长度.
void PrintLinked(LinkedList * head);//打印链表的值，用作测试.
int FindOneValue(LinkedList * head,int value);//查询节点的值，返回数字相同的节点序号，未查找到则返回-1.
void TransNum(LinkedList * head,int length);//反序链表.
void FindAllValue(LinkedList * head,int value,int * a);//查询节点的值，将所有匹配序号储存在数组中.
LinkedList * FindNum(LinkedList * head,int number);//Used for AddValue&DelValue.
void AddValue(LinkedList * head,int CurrentData,int BeforeNumber);//在链表中某一项之后插入值.
void DelValue(LinkedList * head,int BeforeNumber);//删除链表某一项的下一项.
void FreeLinked(LinkedList * head);//释放空间.

#endif //LINKEDLIST_LINKEDLIST_H
