#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#include"tools.h"
#include"ChessData.h"
#include<math.h>
#include<minwindef.h>
ChessData game;
IMAGE backImg;//底图
IMAGE BlackImg;//黑棋
IMAGE WhiteImg;//白棋
IMAGE WinImg;//胜利
IMAGE LoseImg;//失败

const int distance_x = 44;
const int distance_y = 43;
int clickrow, clickcol;
int minimum(int len1, int len2, int len3, int len4);
void PlayerGO();
void AIGO();
bool click(MOUSEMSG msg) {
	int x = msg.x;
	int y = msg.y;
	int col = (x - distance_x) / size;
	int row = (y - distance_y) / size;
	int lefttopX = distance_x + size * col;
	int lefttopY = distance_y + size * row;
	int len, len1, len2, len3, len4;
	int choosePos = false;

	len1 = sqrt((x - lefttopX) * (x - lefttopX) + (y - lefttopY) * (y - lefttopY));//左上
	len2 = sqrt((x - lefttopX - size) * (x - lefttopX - size) + (y - lefttopY) * (y - lefttopY));//右上
	len3 = sqrt((x - lefttopX) * (x - lefttopX) + (y - lefttopY - size) * (y - lefttopY - size));//左下
	len4 = sqrt((x - lefttopX - size) * (x - lefttopX - size) + (y - lefttopY - size) * (y - lefttopY - size));//右下
	len = minimum(len1, len2, len3, len4);
	if (len == len1&& len < threshold) {
		clickcol = col;
		clickrow = row;
		if (game.chessmap[clickrow][clickcol] == 0) {
			choosePos = true;
		}
	}
	if (len == len2 &&len < threshold) {
		clickcol = col+1;
		clickrow = row;
		if (game.chessmap[clickrow][clickcol] == 0) {
			choosePos = true;
		}

	}
	if (len == len3 && len < threshold) {
		clickcol = col;
		clickrow = row+1;
		if (game.chessmap[clickrow][clickcol] == 0) {
			choosePos = true;
		}

	}
	if (len == len4 && len < threshold) {
		clickcol = col + 1;
		clickrow = row + 1;
		if (game.chessmap[clickrow][clickcol] == 0) {
			choosePos = true;
		}

	}
	return choosePos;
}
bool Ryo() {
	if (Win(&game, clickrow, clickcol)) {
		Sleep(1500);
		if (game.sideflag == false) {
			loadimage(0, L"赢.jpg", 897, 895);
		}
		else {
			loadimage(0, L"输.jpg", 897,895);
		}
		_getch();
		return true;
	}
	return false;
}
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

void init() {
	initgraph(897,895);
	loadimage(0, L"board.jpg", 897,895);
	loadimage(&WhiteImg, _T("white.png"), size, size);
	loadimage(&BlackImg, _T("black.png"), size, size);
	initChessData(&game);
}

void Hand(int row, int col, Kind kind) {
	int x = distance_x + col * size - 0.5 * size;
	int y = distance_y + row * size - 0.5 * size;
	if (kind == White) {
		putimagePNG(x, y, &WhiteImg);
	}
	else { putimagePNG( x, y, &BlackImg);
	}
}

int main(void) {
	init();

	while (1) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN&&click(msg)) {
			PlayerGO();
			if (Ryo()) {
				init;
				continue;
			}
			AIGO();
			if (Ryo()) {
				init();
				continue;
			}
		}
	}
	closegraph();
	return 0;
}
void PlayerGO() {
	Hand(clickrow, clickcol, Black);
	newChessmap(&game, clickrow, clickcol);
}
void AIGO() {
	Cpoint point = move(&game);
	clickcol = point.col;
	clickrow = point.row;

	Sleep(100);
	Hand(clickrow, clickcol, White);
	newChessmap(&game, clickrow, clickcol);
}
int minimum(int len1, int len2, int len3, int len4) {
	int a[4] = { len1,len2,len3,len4 };
	int q = len1;
	for (int i =1;i < 4;i++) {
		if (q > a[i]) {
			q = a[i];
		}
	}
	return q;
}


