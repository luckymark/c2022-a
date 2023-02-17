#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "chess.h"
#include <math.h>
bool ClickCheck(ExMessage msg);
void putimagePNG(int x, int y, IMAGE* picture, DWORD dwRop);
bool CheckOver(Chess* game, int ClickRow, int ClickCol);
void ManGO(ExMessage msg);
void Evalute();
void AiGO();
void Over(int row,int col);
struct ValueAndPoint getMaxEvalute(int step);
IMAGE white;
IMAGE black;
IMAGE chess;
IMAGE prechess;
IMAGE preblack;
IMAGE prewhite;
IMAGE vic;
IMAGE def;
int count = 0;
int start = 1;
int ClickCol = 0;
int ClickRow = 0;
struct Chess game;
struct ValueAndPoint tianyuan;
int main()
{
	while (1) {
		initpic();
		while (start) {
			ExMessage msg;
			msg = getmessage(EX_MOUSE | EX_KEY);
			if (msg.message == WM_LBUTTONDOWN) {
				if (ClickCheck(msg)) {
					ManGO(msg);
					if (count != 0) {
						AiGO();
					}
				}
			}
			
			


		}
		system("pause");
	}

	_getch();
	closegraph();
	return 0;
}
void initpic()
{
	initgraph(897, 895);
	IMAGE img;
	loadimage(&img, _T("素材/pan01.jpg"));
	putimage(0, 0, &img);
	loadimage(&black, _T("素材/black.png"), ChessSize, ChessSize, true);
	loadimage(&white, _T("素材/white.png"), ChessSize, ChessSize, true);
	loadimage(&preblack, _T("素材/preblack.png"), ChessSize, ChessSize, true);
	loadimage(&prewhite, _T("素材/prewhite.png"), ChessSize, ChessSize, true);
	loadimage(&vic, _T("素材/胜利.png"), 897, 895, true);
	loadimage(&def, _T("素材/失败.png"));
	initchess(&game);
	start = 1;
	tianyuan.col = 6;
	tianyuan.row = 6;
}

bool ClickCheck(ExMessage msg)
{
	int RIGHTClick = false;
	int col = (msg.x - dy) / ChessSize;
	int row = (msg.y - dx) / ChessSize;
	int LeftTopX = dy + col * ChessSize;
	int LeftTopY = dx + row * ChessSize;
	int LeftBotmX = dy + col * ChessSize;
	int LeftBotmY = dx + (row + 1) * ChessSize;
	int RightTopX = dy + (col + 1) * ChessSize;
	int RightTopY = dx + row * ChessSize;
	int RightBotmX = dy + (col + 1) * ChessSize;
	int RightBotmY = dx + (row + 1) * ChessSize;

	do {
		int distance = sqrt((msg.x - LeftTopX) * (msg.x - LeftTopX) + (msg.y - LeftTopY) * (msg.y - LeftTopY));
		if (distance < PosSet) {
			ClickCol = col;
			ClickRow = row;
			RIGHTClick = true;
			break;
		}
		distance = sqrt((msg.x - LeftBotmX) * (msg.x - LeftBotmX) + (msg.y - LeftBotmY) * (msg.y - LeftBotmY));
		if (distance < PosSet) {
			ClickCol = col;
			ClickRow = row + 1;
			RIGHTClick = true;
			break;
		}
		distance = sqrt((msg.x - RightTopX) * (msg.x - RightTopX) + (msg.y - RightTopY) * (msg.y - RightTopY));
		if (distance < PosSet) {
			ClickCol = col + 1;
			ClickRow = row;
			RIGHTClick = true;
			break;
		}
		distance = sqrt((msg.x - RightBotmX) * (msg.x - RightBotmX) + (msg.y - RightBotmY) * (msg.y - RightBotmY));
		if (distance < PosSet) {
			ClickCol = col + 1;
			ClickRow = row + 1;
			RIGHTClick = true;
			break;
		}
	} while (0);
	return RIGHTClick;
}
bool CheckOver(Chess* game, int ClickRow, int ClickCol)
{
	for (int i = 0; i < 5; i++) {
		if (ClickCol - i >= 0 &&
			ClickCol - i + 4 < BoardSize &&
			game->ChessMap[ClickRow][ClickCol - i] == game->ChessMap[ClickRow][ClickCol - i + 1] &&
			game->ChessMap[ClickRow][ClickCol - i] == game->ChessMap[ClickRow][ClickCol - i + 2] &&
			game->ChessMap[ClickRow][ClickCol - i] == game->ChessMap[ClickRow][ClickCol - i + 3] &&
			game->ChessMap[ClickRow][ClickCol - i] == game->ChessMap[ClickRow][ClickCol - i + 4]) {
			return true;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (ClickRow - i >= 0 &&
			ClickRow - i + 4 < BoardSize &&
			game->ChessMap[ClickRow - i][ClickCol] == game->ChessMap[ClickRow - i + 1][ClickCol] &&
			game->ChessMap[ClickRow - i][ClickCol] == game->ChessMap[ClickRow - i + 2][ClickCol] &&
			game->ChessMap[ClickRow - i][ClickCol] == game->ChessMap[ClickRow - i + 3][ClickCol] &&
			game->ChessMap[ClickRow - i][ClickCol] == game->ChessMap[ClickRow - i + 4][ClickCol]) {
			return true;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (ClickRow - i >= 0 &&
			ClickCol - i >= 0 &&
			ClickRow - i + 4 < BoardSize &&
			ClickCol - i + 4 < BoardSize &&
			game->ChessMap[ClickRow - i][ClickCol - i] == game->ChessMap[ClickRow - i + 1][ClickCol - i + 1] &&
			game->ChessMap[ClickRow - i][ClickCol - i] == game->ChessMap[ClickRow - i + 2][ClickCol - i + 2] &&
			game->ChessMap[ClickRow - i][ClickCol - i] == game->ChessMap[ClickRow - i + 3][ClickCol - i + 3] &&
			game->ChessMap[ClickRow - i][ClickCol - i] == game->ChessMap[ClickRow - i + 4][ClickCol - i + 4]) {
			return true;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (ClickCol - i >= 0 &&
			ClickRow + i < BoardSize &&
			ClickRow + i - 4 >= 0 &&
			ClickCol - i + 4 < BoardSize &&
			game->ChessMap[ClickRow + i][ClickCol - i] == game->ChessMap[ClickRow + i - 1][ClickCol - i + 1] &&
			game->ChessMap[ClickRow + i][ClickCol - i] == game->ChessMap[ClickRow + i - 2][ClickCol - i + 2] &&
			game->ChessMap[ClickRow + i][ClickCol - i] == game->ChessMap[ClickRow + i - 3][ClickCol - i + 3] &&
			game->ChessMap[ClickRow + i][ClickCol - i] == game->ChessMap[ClickRow + i - 4][ClickCol - i + 4]) {
			return true;
		}
	}
	return false;
}

void ManGO(ExMessage msg)
{
	
		int x = dy + ClickCol * ChessSize;
		int y = dx + ClickRow * ChessSize;
		//int prex;
		//int prey;
		//if (game.PlayTurn == 1) {
		//	prechess = preblack;
		//}
		//else {
		//	prechess = prewhite;
		//}
		if (game.PlayTurn == 1) {
			chess = black;
		}
		else {
			chess = white;
		}
		if (game.ChessMap[ClickRow][ClickCol] == 0) {
			putimagePNG(x - 0.5 * ChessSize, y - 0.5 * ChessSize, &chess, SRCCOPY);
			count++;
			game.ChessMap[ClickRow][ClickCol] = game.PlayTurn;
			game.PlayTurn = -game.PlayTurn;
			Over(ClickRow, ClickCol);
		}
		/*switch (msg.message)
		{
			//case WM_MOUSEMOVE:
			//putimagePNG(x - 0.5 * ChessSize, y - 0.5 * ChessSize, &preblack, SRCCOPY);
			//prex = x;
			//prey = y;
			//if (prex != x || prey != y) {
			//putpixel(x - 0.5 * ChessSize, y - 0.5 * ChessSize, 0);
			//prex = x;
			//prey = y;
			//}
			//break;
		case WM_LBUTTONDOWN:
			if (game.ChessMap[ClickRow][ClickCol] == 0) {
				putimagePNG(x - 0.5 * ChessSize, y - 0.5 * ChessSize, &chess, SRCCOPY);
				count++;
				game.ChessMap[ClickRow][ClickCol] = game.PlayTurn;
				game.PlayTurn = -game.PlayTurn;
				Over(ClickRow, ClickCol);
			}
			break;
		}*/

	
}

void Evalute()
{
	int ManNumb = 0;
	int AiNumb = 0;
	int EmptyNumb = 0;
	memset(game.ScoreMap, 0, sizeof(game.ScoreMap));
	int chessAI = -1;//1为黑 -1为白
	for (int row = 0; row < BoardSize; row++) {
		for (int col = 0; col < BoardSize; col++) {
			if (row >= 0 && col >= 0 && game.ChessMap[row][col] == 0) {
				int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int k = 0; k < 4; k++) {
					int x = directs[k][0];
					int y = directs[k][1];
					ManNumb = 0;
					AiNumb = 0;
					EmptyNumb = 0;
					for (int i = 1; i < 5; i++) {
						if (row + i * y >= 0 && row + i * y < BoardSize &&
							col + i * x >= 0 && col + i * x < BoardSize &&
							game.ChessMap[row + i * y][col + i * x] == -chessAI) {
							ManNumb++;
						}
						else if (row + i * y >= 0 && row + i * y < BoardSize &&
							col + i * x >= 0 && col + i * x < BoardSize &&
							game.ChessMap[row + i * y][col + i * x] == 0) {
							EmptyNumb++;
							break;
						}
						else
							break;
					}
					for (int i = 1; i < 5; i++) {
						if (row - i * y >= 0 && row - i * y < BoardSize &&
							col - i * x >= 0 && col - i * x < BoardSize &&
							game.ChessMap[row - i * y][col - i * x] == -chessAI) {
							ManNumb++;
						}
						else if (row - i * y >= 0 && row - i * y < BoardSize &&
							col - i * x >= 0 && col - i * x < BoardSize &&
							game.ChessMap[row - i * y][col - i * x] == 0) {
							EmptyNumb++;
							break;
						}
						else
							break;
					}
					switch (ManNumb) {
					case 1:
						game.ScoreMap[row][col] += 10;
						break;
					case 2:
						if (EmptyNumb == 1)
							game.ScoreMap[row][col] += 500;
						if (EmptyNumb == 2)
							game.ScoreMap[row][col] += 3000;
						break;
					case 3:
						if (EmptyNumb == 1)
							game.ScoreMap[row][col] += 2500;
						if (EmptyNumb == 2)
							game.ScoreMap[row][col] += 30000;
						break;
					case 4:
						game.ScoreMap[row][col] += 1000000;
						break;
					}
					EmptyNumb = 0;
					for (int i = 1; i < 5; i++) {
						if (row - i * y >= 0 && row - i * y < BoardSize &&
							col - i * x >= 0 && col - i * x < BoardSize &&
							game.ChessMap[row - i * y][col - i * x] == chessAI) {
							AiNumb++;
						}
						else if (row - i * y >= 0 && row - i * y < BoardSize &&
							col - i * x >= 0 && col - i * x < BoardSize &&
							game.ChessMap[row - i * y][col - i * x] == 0) {
							EmptyNumb++;
							break;
						}
						else
							break;
					}
					for (int i = 1; i < 5; i++) {
						if (row + i * y >= 0 && row + i * y < BoardSize &&
							col + i * x >= 0 && col + i * x < BoardSize &&
							game.ChessMap[row + i * y][col + i * x] == chessAI) {
							AiNumb++;
						}
						else if (row + i * y >= 0 && row + i * y < BoardSize &&
							col + i * x >= 0 && col + i * x < BoardSize &&
							game.ChessMap[row + i * y][col + i * x] == 0) {
							EmptyNumb++;
							break;
						}
						else
							break;
					}
					switch (AiNumb) {
					case 1:
						game.ScoreMap[row][col] += 10;
						break;
					case 2:
						if (EmptyNumb == 1)
							game.ScoreMap[row][col] += 500;
						if (EmptyNumb == 2)
							game.ScoreMap[row][col] += 3000;
						break;
					case 3:
						if (EmptyNumb == 1)
							game.ScoreMap[row][col] += 2500;
						if (EmptyNumb == 2)
							game.ScoreMap[row][col] += 30000;
						break;
					case 4:
						game.ScoreMap[row][col] += 1000000;
						break;
					
					}
				}

			}
		}
	}


}

struct ValueAndPoint Max()
{
	struct ValueAndPoint max;
	for (int row = 0; row < BoardSize; row++) {
		for (int col = 0; col < BoardSize; col++) {
			if (game.ScoreMap[row][col] > max.value) {
				max.value = game.ScoreMap[row][col];
				max.row = row;
				max.col = col;
			}
		}
	}
	return max;
}

 struct ValueAndPoint getMaxEvalute(int step)
{
	ValueAndPoint final;
	ValueAndPoint Step;
	int standard = 0;
	int maxValue = 0;
	Evalute();
	Step = Max();
	if (Step.value >= 1000000) {

		return Step;
	}
	for (int row = 0; row < BoardSize; row++) {
		for (int col = 0; col < BoardSize; col++) {
			
			if (game.ChessMap[row][col] == 0) {
				game.ChessMap[row][col] = game.PlayTurn;
				Evalute();
				Step = Max();
				if (step > 1) {
				    ValueAndPoint nextStep = getMaxEvalute(step - 1);
					if (nextStep.value >= Step.value) { // α-β剪枝
						game.ChessMap[row][col] = 0;
						return Step;
					}
					Step.value = -nextStep.value;
				}
				if (final.row == -1 || final.col == -1 || final.value > Step.value) {
					final = Step;
				}
				game.ChessMap[row][col] = 0;
			}
		}
	}
	return final;
}

void set(int row,int col,int PlayTurn)
{
	if (game.PlayTurn == 1) {
		chess = black;
	}
	else {
		chess = white;
	}
	int x = dy + col * ChessSize;
	int y = dx + row * ChessSize;
	putimagePNG(x - 0.5 * ChessSize, y - 0.5 * ChessSize, &chess, SRCCOPY);
	game.ChessMap[row][col] = game.PlayTurn;
	game.PlayTurn = -game.PlayTurn;
	count++;
}
void AiGO()
{
	ValueAndPoint point;
	if (count == 0) {
		point = tianyuan;
	}
	if (count == 1) {
		if (game.ChessMap[tianyuan.row][tianyuan.col] == 0) {
			point = tianyuan;
		}
		else {
			point.col = tianyuan.col - 1;
			point.row = tianyuan.row ;
		}
	}
	else {
		point = getMaxEvalute(64);
	}
	set(point.row, point.col, game.PlayTurn);
	
	Over(point.row, point.col);
}

void Over(int row,int col)
{
	if (CheckOver(&game, row, col) && game.PlayTurn == -1) {
		putimagePNG(0, 0, &vic, SRCCOPY);
		start = 0;
	}
	if (CheckOver(&game, row, col) && game.PlayTurn == 1) {
		putimagePNG(0, 0, &def, SRCCOPY);
		start = 0;
	}
}

void putimagePNG(int x, int y, IMAGE* picture, DWORD dwRop) //x为载入图片的X坐标，y为Y坐标
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

