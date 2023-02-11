//
// Created by XuanCheng on 2023/2/11.
//

#ifndef CHESSAI_GUI_H
#define CHESSAI_GUI_H

#include <tchar.h>
#include <easyx.h>

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
