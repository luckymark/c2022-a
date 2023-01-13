//
// Created by XuanCheng on 2023/1/1.
//

#include "Chess.h"
#include "Init.h"


void first() {
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

void fontset(int color, int height, int quality, const char *font, int weight) {
    LOGFONT f;
    gettextstyle(&f);						        // 获取当前字体设置
    settextcolor(color);					            // 设置字体颜色黑色
    f.lfHeight = height;						        // 设置字体高度为 12
    f.lfWeight = weight;					            // 设置字体粗细
    _tcscpy(f.lfFaceName, font);		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
    f.lfQuality = quality;		                        // 设置输出效果为抗锯齿
    settextstyle(&f);						        // 设置字体样式
}

void initgra() {
    initgraph(1500,956, 0);//912 956
    setbkcolor(WHITE);
    cleardevice();
}

void Init(){
    IMAGE board_img;
    initgra();
    first();
    loadimage(&board_img, _T("PNG"), MAKEINTRESOURCE(IDB_PNG1));
    putimage(0, 0,&board_img);
}

int wincondition(){
    if(score(R.hum) == FIVE_SCORE){
        return R.hum;
    }else if(score(R.com) == FIVE_SCORE){
        return R.com;
    }
    return R.emp;
}

void HumWin() {
    fontset(RED, 54, ANTIALIASED_QUALITY, _T("黑体"),FW_BLACK);
    outtextxy(400, 420, _T("您获胜了！ "));
}

void ComWin() {
    fontset(RED, 54, ANTIALIASED_QUALITY, _T("黑体"),FW_BLACK);
    outtextxy(400, 420, _T("电脑战胜！ "));
}

int win(){
    int jud = wincondition();
    if(jud == R.com){
        ComWin();
        return 1;
    }else if(jud == R.hum){
        HumWin();
        return 1;
    }
    return 0;
}

void finish(){
    int judge = win();
    if(judge){
        system("pause");
        exit(0);
    }
}