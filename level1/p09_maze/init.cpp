//
// Created by XuanCheng on 2022/12/4.
//

#include <cstdio>
#include "init.h"
#include <windows.h>
#include <conio.h>

const int map[17][24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0,
                         0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0,
                         0, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, 0, -1, 0, -1, -1, -1, -1, -1, -1, -1, 0, 0,
                         0, -1, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 0,
                         0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, 0, 0, -1, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1, 0, -1, -1, 0,
                         0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, -1, 0, 0,
                         0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0,
                         0, 0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8,
                         0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void MapInit()
{
    for (int i = 0;i < 17;++i) {
        for (int j = 0;j < 24;++j) {
            if (map[i][j] == 0)
                printf("■");
            else if(map[i][j] == -1)
            {
                printf(" ");
            }else if(map[i][j] == 9){
                printf("^");
            }else if(map[i][j] == 8){
                printf("Win");
            }
            if(j == 23){
                printf("\n");
            }
        }
    }
}

void ConsoleCursorHiden() {
    HANDLE hOut;
    CONSOLE_CURSOR_INFO cur;    /* 定义了一个结构体变量 cur*/

    cur.dwSize = 50;            /*  光标大小设置为100 */
    cur.bVisible = false;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);    /* 获取标注输出句柄 */
    SetConsoleCursorInfo(hOut, &cur);    /* 设置控制台光标信息 */
    //CloseHandle(hOut);
}

void Init() {
    ConsoleCursorHiden();
    MapInit();
}

void clear(short x, short y) {
    COORD pos = { x, y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    printf(" ");
    //CloseHandle(hOut);
}

void move(short x,short y){
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    printf("^");
}

void usermove() {
    short x = 1,y = 1;
    int  input;
    while(true){
        input = getch();
        if((input == 0x57||input == 0x77 )&&(map[y-1][x] != 0)){
            clear(x,y);
            y = (short)(y-1);
            move(x,y);
        }else if((input == 0x53||input == 0x73)&&(map[y+1][x] != 0)){
            clear(x,y);
            y = (short)(y+1);
            move(x,y);
        }else if((input == 0x41||input == 0x61)&&(map[y][x-1] != 0)){
            clear(x,y);
            x = (short)(x-1);
            move(x,y);
        }else if((input == 0x44||input == 0x64)&&(map[y][x+1] != 0)){
            clear(x,y);
            x = (short)(x+1);
            move(x,y);
        }
        if(map[y][x] == 8){
            system("cls");
            printf("YOU WIN\n");
            break;
        }
    }
}

