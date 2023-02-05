//
// Created by XuanCheng on 2023/1/1.
//

#ifndef CHESSAI_CHESS_H
#define CHESSAI_CHESS_H

/*typedef struct {
    int hum;
    int com;
    int emp;
}col;*/
class col{
    public:
        int hum;
        int com;
        int emp;
        int trans(int color);
};

int col::trans(int color) {
    return (color == 1 ? 2 : 1);
}

extern col R;

extern int board[20][20];
//y0 = 1;per y = 4.3;y per xiangsu = 15.621;permission = +-1
const int Y[15] = {16,83,150,218,284,351,419,486,553,621,688,755,822,889,955};
//x0 = 1.7;per x = 4.1;x per xiangsu = 15.431;permission = +-1
const int X[15] = {27,90,153,216,279,343,406,469,532,596,659,722,786,849,911};

#include <cstdio>
#include <random>
#include "Init.h"
#include "easyx.h"
#include "resource.h"
#include "Score.h"
#include "hum.h"
#include "AI.h"
#include "kill.h"

#endif //CHESSAI_CHESS_H
