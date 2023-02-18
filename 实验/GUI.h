//
// Created by XuanCheng on 2023/2/11.
//

#ifndef CHESSAI_GUI_H
#define CHESSAI_GUI_H

#include <tchar.h>
#include <easyx.h>

//y0 = 1;per y = 4.3;y per xiangsu = 15.621;permission = +-1
const int Y[15] = {16,83,150,218,284,351,419,486,553,621,688,755,822,889,955};
//x0 = 1.7;per x = 4.1;x per xiangsu = 15.431;permission = +-1
const int X[15] = {27,90,153,216,279,343,406,469,532,596,659,722,786,849,911};


class GUI {
private:
    static void first();
public:
    static void Init();
    static int WinCondition();
    static int win();
    static void HumanDo();
    static void fontset(int color, int height, int quality, const char *font, int weight = FW_NORMAL);
};


#endif //CHESSAI_GUI_H
