/*迷宫小游戏（基于console）
1. 在控制台上显示一个迷宫，包括：墙、玩家、出口等；
2. 通过上下左右键，控制玩家行走；
3. 当玩家到达出口，则显示玩家赢得了游戏；
*/

#include <stdio.h>
#include <stdlib.h>
char map[10][10] = {
    {'#','#','#','#','#','#','#','#','#','#'},
    {'#','I','#','#','#','#','#','#','#','#'},
    {'#',' ',' ','#','#','#','#','#','#','#'},
    {'#','#',' ','#','#',' ',' ',' ','#','#'},
    {'#','#',' ','#','#',' ','#',' ','#','#'},
    {'#',' ',' ','#','#',' ','#',' ','#','#'},
    {'#',' ','#','#','#',' ','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ','#','#','#','#'},
    {'#','#','#','#','#',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','X','#'}
};
int meX = 1, meY = 1;
void drawMap() {
    int i, j;
    system("cls");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
int isWall(int x, int y) {
    return map[y][x] == '#';
}
int isExit(int x, int y) {
    return map[y][x] == 'X';
}
int move(int offsetX, int offsetY) {
    if (isExit(meX + offsetX, meY + offsetY)) {
        return 1;
    }
    if (!isWall(meX + offsetX, meY + offsetY)) {
        map[meY][meX] = ' ';
        meX += offsetX;
        meY += offsetY;
        map[meY][meX] = 'I';
        drawMap();
    }
    return 0;
}
int main()
{
    int successed;
    drawMap();
    while (1) {
        switch (getchar()) {
        case 'w':
            successed = move(0, -1);
            break;
        case 's':
            successed = move(0, 1);
            break;
        case 'a':
            successed = move(-1, 0);
            break;
        case 'd':
            successed = move(1, 0);
            break;
        case 'q':
            return 0;
        }
        if (successed) {
            printf("Congratulations! You Win!!!");
            break;
        }
    }
    return 0;
}