

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
	initgraph(CHESSMAP_WIDTH, CHESSMAP_HEIGHT, EX_SHOWCONSOLE);

	//加载棋盘图片
	//loadimage(&gImage, _T("chessMap.png"), 800, 804, true);
	loadimage(&gImage, _T("box\\OIP-C.jfif"), PICTURE_WIDTH, PICTURE_HEIGHT, true);
	
	//显示棋盘图片
	//putimage(0, 0, &gImage);
	putimage(0, 0, &gImage);
	setfillcolor(background);
	fillrectangle(PICTURE_WIDTH,PICTURE_HEIGHT,CHESSMAP_WIDTH,0);

	setfillcolor(WHITE);
	fillrectangle(PICTURE_WIDTH+50, PICTURE_HEIGHT-150, CHESSMAP_WIDTH-50, 400);
	settextstyle(25, 15, "幼圆");
	outtextxy(PICTURE_WIDTH + 50 +25, PICTURE_HEIGHT - 150-35, "换子");
	
	fillrectangle(PICTURE_WIDTH + 50, PICTURE_HEIGHT - 250, CHESSMAP_WIDTH - 50, 300);
	outtextxy(PICTURE_WIDTH + 50 + 25, PICTURE_HEIGHT - 250 - 35, "悔棋");

	fillrectangle(PICTURE_WIDTH + 50, PICTURE_HEIGHT - 350 , CHESSMAP_WIDTH - 50, 200);
	outtextxy(PICTURE_WIDTH + 50 + 25, PICTURE_HEIGHT - 350 - 35, "认输");
	//播放音效
	//mciSendString("play start.mp3", NULL, 0, NULL);

	//加载黑白棋子图片并进行保存  
	//loadimage(&blackchessImg, _T("blackchessImg.jpg"), chesssize, chesssize, true);
	//loadimage(&whitechessImg, _T("whitechessImg.jpg"), chesssize, chesssize, true);
	loadimage(&blackchessImg, _T("box\\黑棋.png"), chesssize, chesssize, true);
	loadimage(&whitechessImg, _T("box\\白棋.png"), chesssize, chesssize, true);
	loadimage(&smallmap, _T("box\\smallmap.png"), chesssize, chesssize, true);
	changEchessif = 0;
	gobacktimes= 3;
	//清空棋盘表面，为下一局做准备
	for (int i = 0; i < gradesize; i++)
	{
		for (int j = 0; j < gradesize; j++)
		{
			chessmap[i][j] = 0;
		}
	}
	if (changchessif == 0) {
		//定义开局黑方先走
		playerFlag = CHESS_BLACK;
	}
	else if(changchessif == 1)
	{
		playerFlag = false;
	}

	
}

//落子
void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	backlist.insert(backlist.begin(), *pos);
	if (backlist.size() > 6) {
		backlist.pop_back();
	}
	//落子
	int x = margin_x + chesssize * pos->x - chesssize * 0.5;
	int y = margin_y + chesssize * pos->y - chesssize * 0.5;
	int flag = changchessif;
	if (flag == 0) {
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
	if (flag == 1) {
		if (kind == CHESS_WHITE)
		{
			//putimage(x, y, &whitechessImg);
			putimagePNG(x, y, &blackchessImg);
		}
		else
		{
			//putimage(x, y, &blackchessImg);
			putimagePNG(x, y, &whitechessImg);
		}

		updategameMap(pos);
	}
	
	

}

//初始化棋盘数据
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradesize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chesssize = chessSize;
	

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
		if (playerFlag == false)
		{
			//执黑手胜
			//mciSendString("play res/win.mp3",0,0,0);
			loadimage(0, "box\\victory.jpg", 793, 300);
			outtextxy(CHESSMAP_WIDTH/2-50, PICTURE_HEIGHT - 150 - 35, "按任意键返回");
		}
		if (playerFlag == 1)
		{
			//执白手胜
			//mciSendString("play res/lose.mp3", 0, 0, 0);
			loadimage(0, "box\\defeat.jpg", 793, 300);
			outtextxy(CHESSMAP_WIDTH / 2 - 50, PICTURE_HEIGHT - 150 - 35, "按任意键返回");

		}
		_getch();
	}
	
	return flag;
}

bool Chess::checkwin()
{
	//赢则true，输则false
	int row = lastpos.x;
	int col = lastpos.y;
	for (int i = 0; i < 5; i++)
	{
		// 往左5个，往右匹配4个子，20种情况
		if (col - i >= 0 &&
			col - i + 4 < gradesize &&
			chessmap[row][col - i] == chessmap[row][col - i + 1] &&
			chessmap[row][col - i] == chessmap[row][col - i + 2] &&
			chessmap[row][col - i] == chessmap[row][col - i + 3] &&
			chessmap[row][col - i] == chessmap[row][col - i + 4] &&
			chessmap[row][col - i] != 0)
			return true;
	}

	// 竖直方向(上下延伸4个)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradesize &&
			chessmap[row - i][col] == chessmap[row - i + 1][col] &&
			chessmap[row - i][col] == chessmap[row - i + 2][col] &&
			chessmap[row - i][col] == chessmap[row - i + 3][col] &&
			chessmap[row - i][col] == chessmap[row - i + 4][col] &&
			chessmap[row - i][col] != 0)
			return true;
	}

	// “/"方向
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradesize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradesize &&
			// 第[row+i]行，第[col-i]的棋子，与右上方连续4个棋子都相同
			chessmap[row + i][col - i] == chessmap[row + i - 1][col - i + 1] &&
			chessmap[row + i][col - i] == chessmap[row + i - 2][col - i + 2] &&
			chessmap[row + i][col - i] == chessmap[row + i - 3][col - i + 3] &&
			chessmap[row + i][col - i] == chessmap[row + i - 4][col - i + 4] &&
			chessmap[row + i][col - i] != 0)
			return true;
	}

	// “\“ 方向
	for (int i = 0; i < 5; i++)
	{
		// 第[row+i]行，第[col-i]的棋子，与右下方连续4个棋子都相同
		if (row - i >= 0 &&
			row - i + 4 < gradesize &&
			col - i >= 0 &&
			col - i + 4 < gradesize &&
			chessmap[row - i][col - i] == chessmap[row - i + 1][col - i + 1] &&
			chessmap[row - i][col - i] == chessmap[row - i + 2][col - i + 2] &&
			chessmap[row - i][col - i] == chessmap[row - i + 3][col - i + 3] &&
			chessmap[row - i][col - i] == chessmap[row - i + 4][col - i + 4] &&
			chessmap[row - i][col - i] != 0)
			return true;
	}

	return false;

}




void Chess::changechess()
{
	init();
}

void Chess::gobackchess()
{
	if (gobacktimes > 0) {
		chessmap[backlist[0].x][backlist[0].y] = 0;
		int x = margin_x + chesssize * backlist[0].x - chesssize * 0.5;
		int y = margin_y + chesssize * backlist[0].y - chesssize * 0.5;
		putimagePNG(x, y, &smallmap);

		chessmap[backlist[1].x][backlist[1].y] = 0;
		x = margin_x + chesssize * backlist[1].x - chesssize * 0.5;
		y = margin_y + chesssize * backlist[1].y - chesssize * 0.5;
		putimagePNG(x, y, &smallmap);
		backlist.erase(backlist.begin() , backlist.begin() + 2);
		gobacktimes--;
	}
	else {
		fillrectangle(PICTURE_WIDTH + 50, PICTURE_HEIGHT - 250, CHESSMAP_WIDTH - 50, 300);
		outtextxy(PICTURE_WIDTH + 50 + 10, PICTURE_HEIGHT - 250 - 35, "悔棋失败");
	}

	
}

void Chess::faill()
{
	loadimage(0, "defeat.jpg", 793, 300);
	_getch();
	init();
}




void Chess::updategameMap(chesspos* pos)
{
	
	chessmap[pos->x][pos->y] = playerFlag ? 1:-1;
	playerFlag = !playerFlag;
	lastpos = *pos;

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
