#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;
#define MaxLevel 5
typedef struct SkipListNode {
    int value;
    int key;
    int level;
    SkipListNode* forward[MaxLevel];
} SkipListNode;

typedef struct SkipList {
    SkipListNode* head;
    int level;
    int length;
} SkipList;

SkipListNode* CreatNode(int level, int key, int value)
{
    SkipListNode* pNode = (SkipListNode*)malloc(sizeof(SkipListNode));
    if (!pNode) {
        return NULL;
    }
    pNode->key = key;
    pNode->value = value;
    pNode->level = level;
    for (int i = 0; i < MaxLevel; ++i)
        pNode->forward[i] = NULL;

    return pNode;
}
void initSkipList(SkipList* pSkipList)
{
    if (!pSkipList)
        return;
    SkipListNode* head = CreatNode(0, 0, 0);
    if (!head)
        return;
    pSkipList->head = head;
    pSkipList->length = 0;
    pSkipList->level = 1;

    for (int i = 0; i < MaxLevel; i++)
        pSkipList->head->forward[i] = NULL;
}
int randomLevel()
{
    int newLevel = 1;
    while ((rand() & 0xFFFF) < (0.5 * 0xFFFF))
        ++newLevel;
    return newLevel < MaxLevel ? newLevel : MaxLevel;
}

bool AddNode(SkipList* pSkipList, int searchKey, int newValue)
{
    SkipListNode* update[MaxLevel];
    if (!pSkipList)
        return false;

    SkipListNode* pNode = pSkipList->head;
    if (!pNode) {
        return false;
    }
    for (int i = pSkipList->level - 1; i >= 0; i--) {
        while (pNode->forward[i] && pNode->forward[i]->key < searchKey)
            pNode = pNode->forward[i];
        update[i] = pNode;
    }
    pNode = pNode->forward[0];
    if (pNode && pNode->key == searchKey) {
        pNode->value = newValue;
    }
    else {
        int level = randomLevel();
        if (level > pSkipList->level) {
            for (int i = pSkipList->level; i < level; i++) {
                update[i] = pSkipList->head;
            }
            pSkipList->level = level;
        }
        pNode = CreatNode(level, searchKey, newValue);
        if (!pNode) {
            return false;
        }
        for (int i = 0; i < pSkipList->level; ++i) {
            pNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = pNode;
        }
        pSkipList->length++;
    }
    return true;
}

SkipListNode* searchNode(SkipList* pSkipList, int searchKey) {
    if (!pSkipList)
        return NULL;
    SkipListNode* pNode = pSkipList->head;
    if (!pNode)
        return NULL;
    for (int i = pSkipList->level - 1; i >= 0; --i) {
        while (pNode->forward[i] && pNode->forward[i]->key < searchKey)
            pNode = pNode->forward[i];
    }
    pNode = pNode->forward[0];
    if (pNode && pNode->key == searchKey)
        return pNode;
    return NULL;
}
bool deleteNode(SkipList* pSkipList, int searchKey) {
    if (!pSkipList)
        return false;
    SkipListNode* pNode = pSkipList->head;
    SkipListNode* update[MaxLevel];
    for (int i = pSkipList->level - 1; i >= 0; i--) {
        while (pNode->forward[i] && pNode->forward[i]->key < searchKey) {
            pNode = pNode->forward[i];
        }
        update[i] = pNode;
    }
    pNode = pNode->forward[0];
    if (pNode && pNode->key == searchKey) {
        for (int i = 0; i < pSkipList->level; ++i) {
            if (update[i] && update[i]->forward[i] != pNode) {
                break;
            }
            update[i]->forward[i] = pNode->forward[i];
        }
        free(pNode);
        while (pSkipList->level > 1 &&
            pSkipList->head->forward[pSkipList->level - 1] == NULL) {
            pSkipList->level--;
        }
        pSkipList->length--;
        return true;
    }
    return false;
}
void travelList(SkipList* pSkipList)
{
    SkipListNode* pNode = pSkipList->head;
    if (!pNode)
        return;
    while (pNode->forward[0]) {
        cout << pNode->forward[0]->value << " " << pNode->forward[0]->level << endl;
        pNode = pNode->forward[0];
    }
}
int main()
{
    SkipList list;
    initSkipList(&list);
    AddNode(&list, 10, 10);
    AddNode(&list, 2, 2);
    AddNode(&list, 5, 5);
    travelList(&list);
    SkipListNode* pNode = searchNode(&list, 2);
    cout << pNode->value << endl;
    pNode = searchNode(&list, 10);
    cout << pNode->value << endl;
    deleteNode(&list, 2);
    travelList(&list);
    deleteNode(&list, 10);
    travelList(&list);
    deleteNode(&list, 7);
    travelList(&list);
    return 0;
}