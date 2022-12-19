#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "tools.h"

int getDelay() {
    static unsigned long long lastTime = 0;
    unsigned long long currentTime = GetTickCount();
    if (lastTime == 0) {
        lastTime = currentTime;
        return 0;
    }
    else {
        int ret = currentTime - lastTime;
        lastTime = currentTime;
        return ret;
    }
}

// 载入PNG图并去透明部分
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                    | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                    | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}

// 适用于 y <0 以及x<0的任何情况
void putimagePNG2(int x, int y, IMAGE* picture) {
    IMAGE imgTmp;
    if (y < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, -y,
            picture->getwidth(), picture->getheight() + y);
        SetWorkingImage();
        y = 0;
        picture = &imgTmp;
    }

    if (x < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, -x, 0, picture->getwidth() + x, picture->getheight());
        SetWorkingImage();
        x = 0;
        picture = &imgTmp;
    } 

    putimagePNG(x, y, picture);
}

// 适用于 y <0 以及y>0的任何情况
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture) {
    IMAGE imgTmp;
    if (y < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, -y,
            picture->getwidth(), picture->getheight() + y);
        SetWorkingImage();
        y = 0;
        picture = &imgTmp;
    }

    if (x < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, -x, 0, 
            picture->getwidth()< winWidth? picture->getwidth(): winWidth, 
            picture->getheight());
        SetWorkingImage();
        x = 0;
        picture = &imgTmp;
    }
    else if (x >= winWidth) {
        return;
    }
    else if (x > winWidth-picture->getwidth()) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, 0, winWidth - x, picture->getheight());
        SetWorkingImage();
        picture = &imgTmp;
    }

    putimagePNG(x, y, picture);
}

//设A[x01,y01,x02,y02]  B[x11,y11,x12,y12].
bool rectIntersect(int x01, int y01, int x02, int y02,
    int x11, int y11, int x12, int y12)
{
    int zx = abs(x01 + x02 - x11 - x12);
    int x = abs(x01 - x02) + abs(x11 - x12);
    int zy = abs(y01 + y02 - y11 - y12);
    int y = abs(y01 - y02) + abs(y11 - y12);
    return  (zx <= x && zy <= y);
}

void  preLoadSound(const char* name) {
    char cmd[512];
    sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
    mciSendString(cmd, 0, 0, 0);
    sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
    mciSendString(cmd, 0, 0, 0);
}

void  playSound(const char* name) {
    static int index = 1;
    char cmd[512];

    if (index == 1) {
        sprintf_s(cmd, sizeof(cmd), "play %s-1", name);
        mciSendString(cmd, 0, 0, 0);
        sprintf_s(cmd, sizeof(cmd), "close %s-2", name);
        mciSendString(cmd, 0, 0, 0);
        sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
        mciSendString(cmd, 0, 0, 0);
        index++;
    }
    else if (index == 2) {
        sprintf_s(cmd, sizeof(cmd), "play %s-2", name);
        mciSendString(cmd, 0, 0, 0);
        sprintf_s(cmd, sizeof(cmd), "close %s-1", name);
        mciSendString(cmd, 0, 0, 0);
        sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
        mciSendString(cmd, 0, 0, 0);
        index = 1;
    }
}

void drawBloodBar(int x, int y, int width, int height, int lineWidth, int boardColor, int emptyColor, int fillColor, float percent) {
    LINESTYLE lineStyle;
    getlinestyle(&lineStyle);
    int lineColor = getlinecolor();
    int fileColor = getfillcolor();

    if (percent < 0) {
        percent = 0;
    }

    setlinecolor(BLUE);
    setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, lineWidth);
    setfillcolor(emptyColor);
    fillrectangle(x, y, x + width, y + height);
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 0);
    setfillcolor(fillColor);
    setlinecolor(fillColor);
    if (percent > 0) {
        fillrectangle(x + 0.5 * lineWidth, y + lineWidth * 0.5, x + width * percent, y + height - 0.5 * lineWidth);
    }
    
    setlinecolor(lineColor);
    setfillcolor(fillColor);
    setlinestyle(&lineStyle);
}