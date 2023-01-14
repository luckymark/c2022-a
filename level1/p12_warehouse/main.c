#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#pragma warning(disable:4996)
#define BUFSIZE 1000

typedef struct node {
    char name[50];
    char type[50];
    int quantity;
    struct node* next;
}Node;

Node* head;
FILE* fp;
void HomeScreen();
void importdata();
void ShowList();
void Input();
void Output();
void update();
void color(int c);
void gotoxy(int x, int y);

int main() {
    int n;
    while (1) {
        HomeScreen();
        importdata();
        scanf_s("%d", &n);
        fflush(stdin);
        system("cls");
        switch (n) {
            case 1:ShowList(); break;
            case 2:Output(); break;
            case 3:Input(); break;
            case 4:exit(0); break;
        }
        getchar();
    }
    return 0;
}

void HomeScreen() {
    gotoxy(43, 1);
    color(11);
    printf("这是一个进销存程序");
    color(14);
    for (int i = 2; i <= 10; i++) {
        for (int j = 21; j <= 80; j++)
        {
            gotoxy(j, i);
            if (i == 2 || i == 10)
            {
                printf("-");
            }
            else if (j == 21 || j == 80)
            {
                printf("|");
            }
        }
    }
    color(12);
    gotoxy(45, 3);
    printf("显示存货请按1");
    gotoxy(45, 5);
    printf("出库请按2");
    gotoxy(45, 7);
    printf("入库请按3");
    gotoxy(45, 9);
    printf("退出程序请按4\n");
}

void importdata() {
    char buf[BUFSIZE] = { '\0' };
    head = NULL;
    fp = fopen("I:/codeworks/warehouse.txt", "a");
    if (fp == NULL) {
        printf("文件打开失败！\n");
    }
    do {
        Node* p = (Node*)malloc(sizeof(Node));
        p->next = NULL;
        fgets(buf, BUFSIZE, fp);
        sscanf_s(buf, "%s\t%s\t%d", &(p->name), &(p->type), &(p->quantity));
        Node* last = head;
        if (head) {
            while (last->next) {
                last = last->next;
            }
            last->next = p;
        }
        else
            head = p;
    } while (feof(fp));
    fclose(fp);

}

void ShowList() {
    gotoxy(43, 11);
    printf("name  type  quantity\n");
    for (Node* q = head; q; q = q->next) {
        gotoxy(43, 12);
        printf("%s\t%s\t%d\n", q->name, q->type, q->quantity);
    }

}

void Input() {
    int issame = 1;
    Node* p = (Node*)malloc(sizeof(Node));
    p->next = NULL;
    printf("请输入想要入库的“货物名称、货物种类、货物数量");
    scanf("%s%s%d", &(p->name), &(p->type), &(p->quantity));
    fflush(stdin);
    for (Node* q = head; q; q = q->next)
    {
        int x = strcmp(p->name, q->name);
        if (!x);
        {

            q->quantity += p->quantity;
            issame = 0;
            update();
            break;
        }
    }
    if (issame) {
        Node* last = head;
        if (head)
        {
            while (last->next)
            {
                last = last->next;
            }
            last->next = p;
        }
        else {
            head = p;
            printf("%s", p->name);

        }
        update();
    }

}

void Output() {
    char outname[100];
    int outcnt, isfound = 1;
    color(11);
    printf("请输入要出库‘货物名称 货物数量’:\n");
    scanf("%s %d", &outname, &outcnt);
    Node* r;
    Node* q;
    for (q = head, r = NULL; q; q = q->next, r = q) {
        if (!strcmp(outname, q->name)) {
            q->quantity = q->quantity - outcnt;
            if (q->quantity < 0) {
                printf("存货数量不足\n");
                isfound = 0;
            }
            else {
                if (q->quantity = 0) {
                    r = q->next;//此处我有一疑问，是r->next=q->next吗
                    free(q);
                }
                update();
                isfound = 0;
                printf("\n出库成功！\n");
            }
        }
    }
    if (isfound)
        printf("没有该货物的储存记录,无法出库");
}

void update()
{
    fp = fopen("I:/codeworks/warehouse.txt", "a+");
    for (Node* p = head; p; p = p->next) {
        fprintf(fp, "%s\t%s\t%d\n", p->name, p->type, p->quantity);
        fclose(fp);
    }
    printf("更新成功");
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}