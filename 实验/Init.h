//
// Created by XuanCheng on 2023/1/1.
//

#ifndef CHESSAI_INIT_H
#define CHESSAI_INIT_H

#include <tchar.h>
#include <easyx.h>

void fontset(int color, int height, int quality, const char *font, int weight = FW_NORMAL);

void initgra();
void first();
void Init();

int wincondition();
void ComWin();
void HumWin();
int win();
void finish();

#endif //CHESSAI_INIT_H
