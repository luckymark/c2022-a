#pragma once
#ifndef CHESS_GAMEINIT_H
#define CHESS_GAMEINIT_H

#include<easyx.h>

extern int Board[20][20];
extern const int X[15];
extern const int Y[15];

void GameInit(IMAGE board_img,int *round);
void UserMouseJ(ExMessage mouse,int color,int *win);
void WinWinWin(int *win);
void tempinit(void);
#endif