#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "Basic.h"

#define LSTEP 40
#define BOARDSIZE 600
#define X_REGRET 400
#define Y_REGRET 615
#define W_REGRET 105
#define H_REGRET 55

enum _PIECE PIECE;

IMAGE gBgp;
IMAGE gRegret;

int menu() {
	char round;
	int flag = 0;
	printf("\t\t*****请选择先手（黑子）或后手（白子）*****\n");
	printf("\t\t*****    按1选择先手，按2选择后手    *****\n");
	do {
		round = _getch();
	} while (round != '1' && round != '2');
	flag = round - '0';
	system("cls");
	return flag;
}

void drawLine() {
	setlinecolor(BLACK);
	for (int x = LSTEP / 2; x < BOARDSIZE; x += LSTEP) {
		line(x, LSTEP / 2, x, BOARDSIZE - LSTEP / 2);
	}
	for (int y = LSTEP / 2; y < BOARDSIZE; y += LSTEP) {
		line(LSTEP / 2, y, BOARDSIZE - LSTEP / 2, y);
	}
}

void drawPoint() {
	setfillcolor(BLACK);
	fillcircle(4 * LSTEP - LSTEP / 2, 4 * LSTEP - LSTEP / 2, 5);
	fillcircle(12 * LSTEP - LSTEP / 2, 4 * LSTEP - LSTEP / 2, 5);
	fillcircle(4 * LSTEP - LSTEP / 2, 12 * LSTEP - LSTEP / 2, 5);
	fillcircle(12 * LSTEP - LSTEP / 2, 12 * LSTEP - LSTEP / 2, 5);
	fillcircle(8 * LSTEP - LSTEP / 2, 8 * LSTEP - LSTEP / 2, 5);
}

void drawBoard() {
	initgraph(BOARDSIZE, BOARDSIZE + 85, EX_SHOWCONSOLE);
	loadimage(&gBgp, _T("..\\resource\\background.png"));
	loadimage(&gRegret, _T("..\\resource\\withdraw.png"));
	putimage(0, 0, &gBgp);
	putimage(X_REGRET, Y_REGRET, &gRegret);
	drawLine();
	drawPoint();
}

int correct(int t) {
	// 修正坐标 以棋盘网格线左上角的点为原点,一个LSTEP为一个单位长度
	int t1, t2, T;
	t -= LSTEP / 2;
	t1 = t / LSTEP * LSTEP;
	t2 = (t / LSTEP + 1) * LSTEP;

	if (abs(t1 - t) >= abs(t2 - t)) T = t2 / LSTEP;
	else T = t1 / LSTEP;

	return T;
}

void drawPiece(int x, int y) {
	//分辨率坐标
	int rx = x * LSTEP + LSTEP / 2;
	int ry = y * LSTEP + LSTEP / 2;
	if (gBoard[x][y] == BPIECE) {
		setfillcolor(BLACK);
		fillcircle(rx, ry, LSTEP / 2 - 1);
	}
	else if (gBoard[x][y] == WPIECE){
		setfillcolor(WHITE);
		fillcircle(rx, ry, LSTEP / 2 - 1);
	}
}

void highlight(int x, int y, int last_x, int last_y, int round) {
	if (round > 1) {
		last_x = last_x * LSTEP + LSTEP / 2;
		last_y = last_y * LSTEP + LSTEP / 2;
		if (gPiece == BPIECE) {
			setfillcolor(WHITE);
			fillcircle(last_x, last_y, LSTEP / 2 - 1);
		}
		else {
			setfillcolor(BLACK);
			fillcircle(last_x, last_y, LSTEP / 2 - 1);
		}
		setlinecolor(BLACK);
		circle(last_x, last_y, LSTEP / 2 - 1);
	}

	//最新落子
	x = x * LSTEP + LSTEP / 2;
	y = y * LSTEP + LSTEP / 2;
	setlinecolor(GREEN);
	circle(x, y, LSTEP / 2 - 2);
	circle(x, y, LSTEP / 2 - 1);
}

int endJudge(int x, int y) {
	int count = 1;
	int i = 1;

	//***纵向
	for (i = 1, count = 1; i < 5; i++) { //上
		if (x - i >= 0) {
			if (gBoard[x - i][y] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	for (i = 1; i < 5; i++) { //下
		if (x + i < 15) {
			if (gBoard[x + i][y] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	if (count >= 5) return gPiece;

	//***横向
	for (i = 1, count = 1; i < 5; i++) { //左
		if (y - i >= 0) {
			if (gBoard[x][y - i] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	for (i = 1; i < 5; i++) { //右
		if (y + i < 15) {
			if (gBoard[x][y + i] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	if (count >= 5) return gPiece;

	//***主对角
	for (i = 1, count = 1; i < 5; i++) { //左上
		if (x - i >= 0 && y - i >= 0) {
			if (gBoard[x - i][y - i] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	for (i = 1; i < 5; i++) { //右下
		if (x + i < 15 && y + i < 15) {
			if (gBoard[x + i][y + i] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	if (count >= 5) return gPiece;

	//***次对角
	for (i = 1, count = 1; i < 5; i++) { //右上
		if (x - i >= 0 && y + i < 15) {
			if (gBoard[x - i][y + i] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	for (i = 1; i < 5; i++) { //左下
		if (x + i < 15 && y - i >= 0) {
			if (gBoard[x + i][y - i] == gPiece) {
				count++;
			}
			else {
				break;
			}
		}
	}
	if (count >= 5) return gPiece;

	return 0;
}

void turnRound(int flag) {
	if (flag == 0) {
		if (gPiece == BPIECE) {
			gPiece = WPIECE;
		}
		else {
			gPiece = BPIECE;
		}
	}
}

int end(int flag, int round) {
	if (flag != 0) {
		TCHAR b[] = _T("黑子胜！请按任意键退出对局...");
		TCHAR w[] = _T("白子胜！请按任意键退出对局...");
		TCHAR n[] = _T("和棋！请按任意键退出对局...");
		settextcolor(WHITE);

		if (round >= 15 * 15) {
			outtextxy(100, 630, n);
			printf("和棋！\n");
		}
		else {
			if (flag == BPIECE) {
				outtextxy(100, 630, b);
				printf("黑子胜！\n");
			}
			else if (flag == WPIECE) {
				outtextxy(100, 630, w);
				printf("白子胜！\n");
			}
		}
		_getch();
		closegraph();
		return 1;
	}
	else return 0;
}