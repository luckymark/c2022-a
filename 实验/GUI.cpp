//
// Created by XuanCheng on 2023/2/11.
//

#include "GUI.h"
#include "Chess.h"
#include "resource.h"
void GUI::fontset(int color, int height, int quality, const char *font, int weight) {
    LOGFONT f;
    gettextstyle(&f);						        // 获取当前字体设置
    settextcolor(color);					            // 设置字体颜色黑色
    f.lfHeight = height;						        // 设置字体高度为 12
    f.lfWeight = weight;					            // 设置字体粗细
    strcpy_s(f.lfFaceName, sizeof(font)+1, font);		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
    f.lfQuality = quality;		                        // 设置输出效果为抗锯齿
    settextstyle(&f);						        // 设置字体样式
}

void GUI::first() {
    ExMessage mouse;

    fontset(BLACK, 24, ANTIALIASED_QUALITY, _T("黑体"));
    setfillcolor(0xCCCCCC);
    solidrectangle(600, 344, 900, 428);
    solidrectangle(600, 528, 900, 612);
    setfillcolor(BLACK);
    outtextxy(665, 365, _T("电脑先走"));
    outtextxy(665, 549, _T("玩家先走"));

    while (true){
        mouse.lbutton = false;
        while (!mouse.lbutton) {
            getmessage(&mouse, EX_MOUSE);
        }
        mouse.lbutton = false;
        if (mouse.x > 600 && mouse.x < 900) {
            if (mouse.y > 344 && mouse.y < 428) {
                R.com = 1;//电脑先
                R.hum = 2;
                R.emp = 0;
                break;
            }
            else if (mouse.y > 528 && mouse.y < 612) {
                R.com = 2;//玩家先
                R.hum = 1;
                R.emp = 0;
                break;
            }
            else {
                continue;
            }
        }
    }
}

void GUI::Init() {
    IMAGE board_img;
    initgraph(1500,956, 0);//912 956
    setbkcolor(WHITE);
    cleardevice();
    first();
    loadimage(&board_img, _T("PNG"), MAKEINTRESOURCE(IDB_PNG1));
    putimage(0, 0,&board_img);
}

int GUI::WinCondition() {
    short judgeL, judgeW, judgeD1,judgeD2;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = (i + 4 < 15) && (board.board[i][j] == R.com) && (board.board[i + 1][j] == R.com) && (board.board[i + 2][j] == R.com) && (board.board[i + 3][j] == R.com) && (board.board[i + 4][j] == R.com);
            judgeW = (j + 4 < 15) && (board.board[i][j] == R.com) && (board.board[i][j + 1] == R.com) && (board.board[i][j + 2] == R.com) && (board.board[i][j + 3] == R.com) && (board.board[i][j + 4] == R.com);
            judgeD1 = (i + 4 < 15) && (j + 4 < 15) && (board.board[i][j] == R.com) && (board.board[i + 1][j + 1] == R.com) && (board.board[i + 2][j + 2] == R.com) && (board.board[i + 3][j + 3] == R.com) && (board.board[i + 4][j + 4] == R.com);
            judgeD2 = (j - 4 >= 0) && (i + 4 < 15) && (board.board[i][j] == R.com) && (board.board[i + 1][j - 1] == R.com) && (board.board[i + 2][j - 2] == R.com) && (board.board[i + 3][j - 3] == R.com) && (board.board[i + 4][j - 4] == R.com);
            if (judgeL || judgeW || judgeD1 || judgeD2) {
                return R.com;
            }
        }
    }
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = (i + 4 < 15) && (board.board[i][j] == R.hum) && (board.board[i + 1][j] == R.hum) && (board.board[i + 2][j] == R.hum) && (board.board[i + 3][j] == R.hum) && (board.board[i + 4][j] == R.hum);
            judgeW = (j + 4 < 15) && (board.board[i][j] == R.hum) && (board.board[i][j + 1] == R.hum) && (board.board[i][j + 2] == R.hum) && (board.board[i][j + 3] == R.hum) && (board.board[i][j + 4] == R.hum);
            judgeD1 = (i + 4 < 15) && (j + 4 < 15) && (board.board[i][j] == R.hum) && (board.board[i + 1][j + 1] == R.hum) && (board.board[i + 2][j + 2] == R.hum) && (board.board[i + 3][j + 3] == R.hum) && (board.board[i + 4][j + 4] == R.hum);
            judgeD2 = (j - 4 >= 0) && (i + 4 < 15) && (board.board[i][j] == R.hum) && (board.board[i + 1][j - 1] == R.hum) && (board.board[i + 2][j - 2] == R.hum) && (board.board[i + 3][j - 3] == R.hum) && (board.board[i + 4][j - 4] == R.hum);
            if (judgeL || judgeW || judgeD1 || judgeD2) {
                return R.hum;
            }
        }
    }
    return R.emp;
}

int GUI::win() {
    if(GUI::WinCondition() == R.com){
        fontset(RED, 54, ANTIALIASED_QUALITY, _T("黑体"),FW_BLACK);
        outtextxy(400, 420, _T("愚蠢的人类！ "));
        return 1;
    }else if(GUI::WinCondition() == R.hum){
        fontset(RED, 54, ANTIALIASED_QUALITY, _T("黑体"),FW_BLACK);
        outtextxy(400, 420, _T("您获胜了！ "));
        return 1;
    }
    return 0;
}

void GUI::HumanDo() {
    ExMessage mouse{};

    fontset(BLACK, 24, ANTIALIASED_QUALITY, _T("黑体"));
    outtextxy(913, 0, _T("推翻人类暴政！ "));
    while(true) {
        mouse.lbutton = false;
        while (!mouse.lbutton) {
            getmessage(&mouse, EX_MOUSE);
        }
        mouse.lbutton = false;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if (mouse.x > X[i] - 16 && mouse.x < X[i] + 16) {
                    if (mouse.y > Y[j] - 16 && mouse.y < Y[j] + 16 && board.board[i][j] == 0) {
                        if (R.hum == 1) {
                            setfillcolor(BLACK);
                        } else {
                            setfillcolor(WHITE);
                        }
                        solidcircle(X[i], Y[j], 28);
                        board.put({i,j},R.hum);
                        flushmessage();
                        //
                        int k = board.score(R.hum);
                        printf("hum:%d\n",k);
                        //
                        return;
                    }
                }
            }
        }
    }
}
