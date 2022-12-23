

#include "Chess.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<mmsystem.h>
#include<math.h>
#include"AI.h"
#pragma comment(lib,"winmm.lib")
IMAGE gImage;

void putimagePNG(int x, int y, IMAGE* picture);



void Chess::init()
{
	//创建游戏窗口
	initgraph(793, 793, EX_SHOWCONSOLE);

	//加载棋盘图片
	//loadimage(&gImage, _T("chessMap.png"), 800, 804, true);
	loadimage(&gImage, _T("OIP-C.jfif"), 793, 793, true);
	
	//显示棋盘图片
	//putimage(0, 0, &gImage);
	putimage(0, 0, &gImage);

	//播放音效
	//mciSendString("play start.mp3", NULL, 0, NULL);

	//加载黑白棋子图片并进行保存  
	//loadimage(&blackchessImg, _T("blackchessImg.jpg"), chesssize, chesssize, true);
	//loadimage(&whitechessImg, _T("whitechessImg.jpg"), chesssize, chesssize, true);
	loadimage(&blackchessImg, _T("黑棋.png"), chesssize, chesssize, true);
	loadimage(&whitechessImg, _T("白棋.png"), chesssize, chesssize, true);

	//清空棋盘表面，为下一局做准备
	for (int i = 0; i < gradesize; i++)
	{
		for (int j = 0; j < gradesize; j++)
		{
			chessmap[i][j] = 0;
		}
	}

	//定义开局黑方先走
	playerFlag = CHESS_BLACK;

	
}

//落子
void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{


	//落子
	int x = margin_x + chesssize * pos->x - chesssize * 0.5;
	int y = margin_y + chesssize * pos->y - chesssize * 0.5;

	if (kind == CHESS_WHITE)
	{
		//putimage(x, y, &whitechessImg);
		putimagePNG(x, y, &whitechessImg);
	}
	else
	{
		//putimage(x, y, &blackchessImg);
		putimagePNG(x, y, &blackchessImg);
	}

	updategameMap(pos);
	

}

//初始化棋盘数据
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradesize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chesssize = chessSize;
	this->playerFlag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++)
	{
		vector<int>row;
		for (int j = 0; j < gradeSize; j++)
		{
			row.push_back(0);
		}
		chessmap.push_back(row);
	}
}


bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int row = (x - margin_x) / chesssize;
	int col = (y - margin_y) / chesssize;

	int leftTopPosX = margin_x + chesssize * row;
	int leftTopPosY = margin_y + chesssize * col;
	int offset = chesssize * 0.25; // 20 鼠标点击的模糊距离上限

	int len;
	int selectPos = false;

	do {
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->x = row;
			pos->y = col;
			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}

		// 距离右上角的距离
		len = sqrt((x - leftTopPosX - chesssize) * (x - leftTopPosX - chesssize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->x = row+1;
			pos->y = col ;
			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}

		// 距离左下角的距离
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chesssize) * (y - leftTopPosY - chesssize));
		if (len < offset) {
			pos->x = row;
			pos->y = col+1;
			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}

		// 距离右下角的距离
		len = sqrt((x - leftTopPosX - chesssize) * (x - leftTopPosX - chesssize) + (y - leftTopPosY - chesssize) * (y - leftTopPosY - chesssize));
		if (len < offset) {
			pos->x = row + 1;
			pos->y = col + 1;

			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}
	} while (0);

	return selectPos;
}




int Chess::getGradeSize()
{
	return gradesize;
}

int Chess::getChessData(int row, int col)
{
	return chessmap[row][col];
}

int Chess::getChessData(ChessPos* pos)
{
	return chessmap[pos->x][pos->y];
}

bool Chess::checkOver()
{
	bool flag = 0;
	if (checkwin())
	{
		flag = 1;//棋局结束
		if (playerFlag == -1)
		{
			//执黑手胜

		}
		if (playerFlag == 1)
		{
			//执白手胜

		}
	}
	
	return flag;
}

bool Chess::checkwin()
{
	return false;
}

void Chess::updategameMap(chesspos* pos)
{
	
	chessmap[pos->x][pos->y] = playerFlag ? 1:-1;
	playerFlag = !playerFlag;

}



void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
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
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
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
