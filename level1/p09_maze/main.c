#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int inx=0,iny=1;
int maze[7][8] = {
        0, 2, 0, 0, 0,3,1,0,
        0, 1, 1, 1, 0,0,1,0,
        0, 0, 0, 1, 1,1,1,0,
        0, 1, 1, 1, 0,1,0,0,
        0, 0, 0, 1, 0,1,1,0,
        0, 1, 1, 1, 1,1,0,0,
        0, 0, 0, 0, 0,0,0,0,
};

void test(){
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            if(maze[i][j]==2){
                inx=i;
                iny=j;}
        }
    }
}

int print_map(void) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            printf_s("%d  ", maze[i][j]);
        }
        printf_s("\n");
    }
    printf_s("*********************\n");
}

int main() {
    print_map();
    char lt;
    while (maze[0][5]!=2){
        if(kbhit()){
        lt=getch();
        switch (lt) {
            case 's':
                if (maze[inx+1][iny]!=0){
                    maze[inx][iny]=1;
                    maze[inx+1][iny]=2;
                    break;} else
                    break;
            case 'a':
                if(maze[inx][iny-1]!=0){
                    maze[inx][iny]=1;
                    maze[inx][iny-1]=2;
                    break;} else
                    break;
            case 'w':
                if(maze[inx-1][iny]!=0){
                    maze[inx][iny]=1;
                    maze[inx-1][iny]=2;
                    break;} else
                    break;
            case 'd':
                if(maze[inx][iny+1]!=0){
                    maze[inx][iny]=1;
                    maze[inx][iny+1]=2;
                    break;} else
                    break;
        }
        system("cls");
        print_map();
        test();}
    }
    printf_s("µ½´ïÖÕµã\n");
    system("pause");
    return 0;
}
