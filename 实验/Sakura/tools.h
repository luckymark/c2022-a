#pragma once
#include <graphics.h>

//���ؾ�����һ�ε��ü����ʱ�䣨��λ��ms)����һ�ε���ʱ����0
int getDelay(); 

//��Դ�治֧��x<0
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

// ������ x <0 �Լ�x>0���κ����
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

// �ж����������Ƿ��ཻ
//����ͼƬ���Ե�����������
bool rectIntersect(int a1X, int a1Y, int a2X, int a2Y,
    int b1X, int b1Y, int b2X, int b2Y);

void  preLoadSound(const char* name);
void  playSound(const char* name);

void drawBloodBar(int x, int y, int width, int height, int lineWidth, int boardColor, int emptyColor, int fillColor, float percent);