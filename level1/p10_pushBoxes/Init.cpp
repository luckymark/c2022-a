//
// Created by XuanCheng on 2022/12/13.
//
#include <cstdio>
#include <cstdlib>
#include "Init.h"
#include <windows.h>
#include <conio.h>

int map[17][24];
short bpos[2] = {2,2};
short upos[2] = {1,1};
int score = 0;

void MapLoad() {
    FILE *fp;
    int nu;
    fp = fopen("map.dat","r");
    if(fp == nullptr){
        printf("Fail to load map");
        exit(0x05);
    }
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 25; ++j) {
            nu = fgetc(fp);
            if(nu == 10){
                break;
            }else{
                map[i][j] = nu-CHANGE;
            }
        }
    }
}

void MapInit() {
    MapLoad();
    for (int i = 0;i < 17;++i) {
        for (int j = 0;j < 24;++j) {
            if (map[i][j] == 0)
                printf("■");
            else if(map[i][j] == 1)
            {
                printf(" ");
            }else if(map[i][j] == 9){
                printf("^");
            }else if(map[i][j] == 8){
                printf("Win");
            }else if(map[i][j] == 6){
                printf("▢");
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

void movebox(short x, short y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    printf("▢");
}

void viewscore(short x, short y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    printf("score:%d      ",score + 49);
}

void savescore(){
    FILE *fp;
    fp = fopen("score.txt","w");
    fprintf(fp,"score:%d\n",score + 49);
}
/*void usermove() {
    short x = upos[0];
    short y = upos[1];
    int  input;
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
    upos[0] = x;
    upos[1] = y;
}*/

void movewbox() {
    short xu = upos[0];
    short yu = upos[1];
    short xb = bpos[0];
    short yb = bpos[1];
    int  input;
    viewscore(50,0);
    input = getch();
    if((input == 0x57||input == 0x77 )&&(map[yu - 1][xu] != 0)){
        if(xu == xb && (yu-1) == yb && (map[yb - 1][xb] != 0)){
            clear(xu, yu);
            yu = (short)(yu - 1);
            move(xu, yu);
            yb = (short)(yb - 1);
            movebox(xb,yb);
            score += -10;
        } else if(xu == xb && (yu-1) == yb && (map[yb - 1][xb] == 0)){
            return;
        }else{
            clear(xu, yu);
            yu = (short)(yu - 1);
            move(xu, yu);
            score += -10;
        }
    }else if((input == 0x53||input == 0x73)&&(map[yu + 1][xu] != 0)){
        if(xu == xb && (yu+1) == yb && (map[yb + 1][xb] != 0)){
            clear(xu, yu);
            yu = (short)(yu + 1);
            move(xu, yu);
            yb = (short)(yb + 1);
            movebox(xb,yb);
            score += -10;
        } else if(xu == xb && (yu+1) == yb && (map[yb + 1][xb] == 0)){
            return;
        }else{
            clear(xu, yu);
            yu = (short)(yu + 1);
            move(xu, yu);
            score += -10;
        }
    }else if((input == 0x41||input == 0x61)&&(map[yu][xu - 1] != 0)){
        if((xu-1) == xb && yu == yb && (map[yb][xb - 1] != 0)){
            clear(xu, yu);
            xu = (short)(xu-1);
            move(xu, yu);
            xb = (short)(xb - 1);
            movebox(xb,yb);
            score += -10;
        }else if((xu-1) == xb && yu == yb && (map[yb][xb - 1] == 0)){
            return;
        }else{
            clear(xu, yu);
            xu = (short)(xu-1);
            move(xu, yu);
            score += -10;
        }
    }else if((input == 0x44||input == 0x64)&&(map[yu][xu + 1] != 0)){
        if((xu+1) == xb && yu == yb && (map[yb][xb + 1] != 0)){
            clear(xu, yu);
            xu = (short)(xu+1);
            move(xu, yu);
            xb = (short)(xb + 1);
            movebox(xb,yb);
            score += -10;
        } else if((xu+1) == xb && yu == yb && (map[yb][xb + 1] == 0)){
            return;
        }else{
            clear(xu, yu);
            xu = (short)(xu+1);
            move(xu, yu);
            score += -10;
        }
    }
    if(map[yb][xb] == 8){
        score += 1000;
        viewscore(50,0);
        Sleep(1000);
        system("cls");
        printf("score:%d\n",score + 49);
        printf("YOU WIN\n");
        savescore();
        system("pause");
        exit(0);
    }
    upos[0] = xu;
    upos[1] = yu;
    bpos[0] = xb;
    bpos[1] = yb;
}
