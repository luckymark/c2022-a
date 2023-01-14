#include<stdio.h>
#include<Windows.h>
#pragma warning(disable:4996)

#define len 10
int x = 0, y = 0;
int map[len][len] = { 0 };
int lel;
int walk = 0;
int score = 0;
void drawmap();
void getmap(FILE* fp);
void choosemap();
void CursorGoto(int x, int y);
void moveup();
void moveleft();
void movedown();
void moveright();
int findplayer();
void home();
int grade(int score);
void savegrade();
void end();
int total();
int done();

int main() {
    int n, m;
    system("title Sokoban");
    system("color F1");
    choosemap();
    getchar();
    system("cls");
    n = total();
    while (1) {
        system("cls");
        drawmap();
        m = done();
        walk++;
        switch (getchar())
        {
            case 'w':
            case'W': {
                moveup();
                break;
            }
            case 'a':
            case'A': {
                moveleft();
                break;
            }
            case 's':
            case'S': {
                movedown();
                break;
            }
            case 'd':
            case'D': {
                moveright();
                break;
            }
            default:
            {
                printf("请重新输入"); break;
            }
        }
        if (n == m)
        {
            walk = walk / 2;
            end();
            savegrade();
            return 0;
        }
    }

}

void moveup() {
    findplayer();
    switch (map[x - 1][y]) {
        case 0: {
            map[x - 1][y] = 3;
            map[x][y] = 0;
            break;
        }
        case 1: break;
        case 2: {
            if (map[x - 2][y] == 0) {
                map[x - 2][y] = 2;
                map[x - 1][y] = 3;
                map[x][y] = 0;
            }
            else {
                if (map[x - 2][y] == 4) {
                    map[x - 2][y] = 5;
                    map[x - 1][y] = 3;
                    map[x][y] = 0;
                }
            }
            break;
        }
    }
}

void moveleft() {
    findplayer();
    switch (map[x][y-1]) {
        case 0: {
            map[x ][y-1] = 3;
            map[x][y] = 0;
            break;
        }
        case 1: break;
        case 2: {
            if (map[x ][y-2] == 0) {
                map[x ][y-2] = 2;
                map[x ][y-1] = 3;
                map[x][y] = 0;
            }
            else {
                if (map[x ][y-2] == 4) {
                    map[x ][y-2] = 5;
                    map[x ][y-1] = 3;
                    map[x][y] = 0;
                }
            }
            break;
        }
    }
}

void movedown() {
    findplayer();
    switch (map[x + 1][y]) {
        case 0: {
            map[x + 1][y] = 3;
            map[x][y] = 0;
            break;
        }
        case 1: break;
        case 2: {
            if (map[x +2][y] == 0) {
                map[x + 2][y] = 2;
                map[x + 1][y] = 3;
                map[x][y] = 0;
            }
            else {
                if (map[x + 2][y] == 4) {
                    map[x + 2][y] = 5;
                    map[x + 1][y] = 3;
                    map[x][y] = 0;
                }
            }
            break;
        }
    }
}

void moveright() {
    findplayer();
    switch (map[x ][y+1]) {
        case 0: {
            map[x ][y+1] = 3;
            map[x][y] = 0;
            break;
        }
        case 1: break;
        case 2: {
            if (map[x ][y+2] == 0) {
                map[x ][y+2] = 2;
                map[x ][y+1] = 3;
                map[x][y] = 0;
            }
            else {
                if (map[x ][y+2] == 4) {
                    map[x][y+2] = 5;
                    map[x ][y+1] = 3;
                    map[x][y] = 0;
                }
            }
            break;
        }
    }
}

void choosemap() {
    FILE* fp;
    fp = NULL;
    while (1) {
        system("cls");
        home();
        rewind(stdin);
        scanf_s("%d", &lel);
        if (lel!=1&&lel!=2&&lel!=3&&lel!=0 ) {
            CursorGoto(34, 18);
            printf("请重新输入\n");
            CursorGoto(34, 19);
            system("pause");
        }
        else {
            switch (lel) {
                case 0:
                {
                    system("cls");
                    CursorGoto(34, 12);
                    printf("欢迎下次游玩！");
                    exit(0);
                }
                case 1:
                {
                    system("cls");
                    fp = fopen("I:/codeworks/boxespush/maps/map1.txt", "a+");
                    getmap(fp);
                    break;
                }
                case 2:
                {
                    system("cls");
                    fp = fopen("I:/codeworks/boxespush/maps/map2.txt", "a+");
                    getmap(fp);
                    break;
                }
                case 3:
                {
                    system("cls");
                    fp = fopen("I:/codeworks/boxespush/maps/map3.txt", "a+");
                    getmap(fp);
                    break;
                }
            }
            break;
        }
    }
    fclose(fp);
}

void getmap(FILE*fp) {
    int i, j;
    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            fscanf_s(fp, "%d", &map[i][j]);
        }
    }
}

void drawmap() {
    int i, j = 0;
    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            if (map[i][j] == 1)
                printf("■");
            if (map[i][j] == 3)
                printf("♀");
            if (map[i][j] == 2)
                printf("□");
            if (map[i][j] == 4)
                printf("☆");
            if (map[i][j] == 0)
                printf("  ");
            if (map[i][j] == 5)
                printf("★");
        }
        printf("\n");
    }
}

int findplayer() {
    for( x=0;x<len;x++)
        for ( y = 0; y < len; y++) {
            if (map[x][y] == 3)return 0;
        }

}

void CursorGoto(int x, int y) //光标定位
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void home() {
    system("cls");
    CursorGoto(39, 8);
    printf("欢迎来玩推箱子游戏");
    CursorGoto(34, 10);
    printf("以下是游玩方法");
    CursorGoto(34, 12);
    printf("w:向上移动 a:向左移动 s:向下移动 d:向右移动\n(输入需要需采用回车键！！！)");
    CursorGoto(34, 14);
    printf("输入0可以退出游戏");
    CursorGoto(34, 16);
    printf("输入1/2/3来选择地图");
    CursorGoto(34, 17);
}

void end() {
    system("cls");
    CursorGoto(39, 8);
    printf("游戏胜利");
    CursorGoto(39, 10);
    printf("您走过的步数为%d\n", walk);
    score = grade(score);
    CursorGoto(39, 12);
    printf("您关卡%d得分为%d\n",lel,score);
    system("pause");
}

void savegrade() {
    FILE* fp;
    fp = NULL;
    fp = fopen("I:/codeworks/boxespush/maps/grade.txt", "a+");
    fprintf(fp, "\n您关卡%d得分为%d\n", lel,score);
    fprintf(fp, "%s\r\t", __DATE__);
    fprintf(fp, "%s\r\t", __TIME__);
    fclose(fp);
}

int grade(int score) {
    score = 1000 / walk;
    return score;
}

int total() {
    int n = 0;
    for (x = 0; x < len; x++)
        for (y = 0; y < len; y++) {
            if (map[x][y] == 4)
                n++;
        }
    return n;
}

int done() {
    int n = 0;
    for (x = 0; x < len; x++)
        for (y = 0; y < len; y++) {
            if (map[x][y] == 5)
                n++;
        }
    return n;
}