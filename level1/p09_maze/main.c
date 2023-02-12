#include<stdio.h>
#include<Windows.h>

int x = 1, y = 0;

int maze[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {8,0,0,0,1,1,1,0,1,1},
        {1,1,1,0,0,0,0,0,1,1},
        {1,1,1,0,1,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,0,1},
        {1,1,0,1,1,1,0,1,1,1},
        {1,0,0,1,0,1,0,0,0,1},
        {1,1,0,0,0,1,0,1,1,1},
        {1,1,0,1,1,1,0,0,0,9},
        {1,1,1,1,1,1,1,1,1,1}
};
void DrawMaze();
void Move();
int main() {
    DrawMaze();
    Move();
}

void DrawMaze() {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (maze[i][j] == 1)
                printf("��");
            else if (maze[i][j] == 0)
                printf("  ");
            else if (maze[i][j] == 8)
                printf("PL");
            else
                printf("EX");
        }
        printf("\n");
    }
    printf("���� w :����;���� a :����;���� s :����;���� d :����;\nPl:���\nEX:����");
}

void Move() {
    fflush(stdin);
    char order;
    order = getchar();
    if(order=='\n')
        order = getchar();
    fflush(stdin);
    switch (order) {
        case 'a':
            if (y - 1 >= 0 && maze[x][y - 1] == 0) {
                maze[x][y] = 0;
                maze[x][y - 1] = 8;
                y--;
                break;
            }
            else Move();
        case 'w':
            if (x - 1 > 0 && maze[x-1][y ] == 0) {
                maze[x][y] = 0;
                maze[x-1][y ] = 8;
                x--;
                break;
            }
            else Move();
        case 's':
            if (x + 1 > 0 && maze[x+1][y] == 0) {
                maze[x][y] = 0;
                maze[x+1][y]=8;
                x++;
                break;
            }
            else Move();

        case 'd':
            if (y +1 > 0 && maze[x][y +1] == 0) {
                maze[x][y] = 0;
                maze[x][y +1] = 8;
                y++;
                break;
            }
            else Move();
    }
    system("cls");
    DrawMaze();
    fflush(stdin);
    if (x == 8 && y == 8) printf("��ϲ�����յ�!\n");
    else Move();
}