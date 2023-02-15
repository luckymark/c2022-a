#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int inx=0,iny=1;
int maze[7][7];
typedef struct position{int x,y;};

struct position cave(struct position lc){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if(maze[i][j]==4){
                lc.x=i;
                lc.y=j;
                return lc;
            }
        }
    }
}


struct position ctest(struct position lc){
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if(maze[i][j]==3){
                lc.x=i;
                lc.y=j;
                return lc;
            }
        }
    }
}

void tpr(){
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if(maze[i][j]==2){
                inx=i;
                iny=j;}
        }
    }
}

void Map() {
    FILE *fp = NULL;
    char c;
    int buff[255];
    int i,level = 0;
    printf_s("请选择要游玩的地图");
    scanf_s("%d", &level);
    switch (level) {
        case 1:
            fp = fopen("F:/Map/map1.txt", "r");
            break;
        case 2:
            fp = fopen("F:/Map/map2.txt", "r");
            break;
        case 3:
            fp = fopen("F:/Map/map3.txt", "r");
            break;
        default:
            printf_s("不存在该地图，请在1~3中选择");
            return;
    }
        i=0;
        while(1) {
            while(1) {
                fscanf(fp, "%d", &buff[i]);
                c = fgetc(fp);
                if (c == '\n' || c == EOF) {
                    break;
                }
                i++;
            }
            if (c == EOF) {
                break;
            }
        }
    for(int j=0; j<=i; j++)
    {
        maze[i][j]=buff[j];
    }
}

int print_map(void) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            switch (maze[i][j]) {
                case 0:
                    printf_s("墙");
                    break;
                case 1:
                    printf_s("  ");
                    break;
                case 2:
                    printf_s("人");
                    break;
                case 3:
                    printf_s("箱");
                    break;
                case 4:
                    printf_s("洞");
                    break;
            }

        }
        printf_s("\n");
    }
    printf_s("*********************\n");
}

void move(){
    char lt;
    lt=getch();
    switch (lt) {
        case 's':
            if (maze[inx+1][iny]==3&&maze[inx+2][iny]!=0){
                maze[inx+1][iny]=2;
                maze[inx+2][iny]=3;}
            if (maze[inx+1][iny]!=0){
                maze[inx][iny]=1;
                maze[inx+1][iny]=2;
                break;} else
                break;
        case 'a':
            if (maze[inx][iny-1]==3&&maze[inx][iny-2]!=0){
                maze[inx][iny-1]=2;
                maze[inx][iny-2]=3;}
            if(maze[inx][iny-1]!=0){
                maze[inx][iny]=1;
                maze[inx][iny-1]=2;
                break;} else
                break;
        case 'w':
            if (maze[inx-1][iny]==3&&maze[inx-2][iny]!=0){
                maze[inx-1][iny]=2;
                maze[inx-2][iny]=3;}
            if(maze[inx-1][iny]!=0){
                maze[inx][iny]=1;
                maze[inx-1][iny]=2;
                break;} else
                break;
        case 'd':
            if (maze[inx][iny+1]==3&&maze[inx][iny+2]!=0){
                maze[inx][iny+1]=2;
                maze[inx][iny+2]=3;}
            if(maze[inx][iny+1]!=0){
                maze[inx][iny]=1;
                maze[inx][iny+1]=2;
                break;} else
                break;
    }
    system("cls");
    print_map();
    tpr();
}

int main() {
    struct position e1,c1;
    while(1) {
        Map();
        cave(c1);
        print_map();
        while (e1.x != c1.x || e1.y != c1.y) {
            ctest(e1);
            if (kbhit()) {
                move();
            }
        }
        printf_s("到达终点\n");
        memset(maze, 0, sizeof(int));
    }
    return 0;
}
