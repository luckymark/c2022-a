#pragma once
#include <graphics.h>

//返回距离上一次调用间隔的时间（单位：ms)，第一次调用时返回0
int getDelay(); 

//开源版不支持x<0
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

// 适用于 x <0 以及x>0的任何情况
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

// 判断两个矩形是否相交
//两张图片各自的左上与右下
bool rectIntersect(int a1X, int a1Y, int a2X, int a2Y,
    int b1X, int b1Y, int b2X, int b2Y);

void  preLoadSound(const char* name);
void  playSound(const char* name);

void drawBloodBar(int x, int y, int width, int height, int lineWidth, int boardColor, int emptyColor, int fillColor, float percent);