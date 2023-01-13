//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"
#include "hum.h"

void Hum(){
    ExMessage mouse;

    fontset(BLACK, 24, ANTIALIASED_QUALITY, _T("黑体"));
    outtextxy(913, 0, _T("请您落子"));
    while(true) {
        mouse.lbutton = false;
        while (!mouse.lbutton) {
            getmessage(&mouse, EX_MOUSE);
        }
        mouse.lbutton = false;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if (mouse.x > X[i] - 16 && mouse.x < X[i] + 16) {
                    if (mouse.y > Y[j] - 16 && mouse.y < Y[j] + 16 && board[i][j] == 0) {
                        if (R.hum == 1) {
                            setfillcolor(BLACK);
                        } else {
                            setfillcolor(WHITE);
                        }
                        solidcircle(X[i], Y[j], 28);
                        board[i][j] = R.hum;
                        flushmessage();
                        return;
                    }
                }
            }
        }
    }
}

void Humdo() {
    Hum();
    finish();
}

/*void Humtest(){
    ExMessage mouse;

    fontset(BLACK, 24, ANTIALIASED_QUALITY, _T("黑体"));
    outtextxy(913, 0, _T("请您落子"));
    while(true) {
        mouse.lbutton = false;
        while (!mouse.lbutton) {
            getmessage(&mouse, EX_MOUSE);
        }
        mouse.lbutton = false;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if (mouse.x > X[i] - 16 && mouse.x < X[i] + 16) {
                    if (mouse.y > Y[j] - 16 && mouse.y < Y[j] + 16 && board[i][j] == 0) {
                        if (R.com == 1) {
                            setfillcolor(BLACK);
                        } else {
                            setfillcolor(WHITE);
                        }
                        solidcircle(X[i], Y[j], 28);
                        board[i][j] = R.com;
                        flushmessage();
                        return;
                    }
                }
            }
        }
    }
}*/

