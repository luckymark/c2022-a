#include <stdio.h>
#include <string.h>
#include "Basic.h"
#include "AIhead.h"
#include "Human.h"
#include "Stack.h"

#define LSTEP 40
#define BOARDSIZE 600
#define X_REGRET 400
#define Y_REGRET 615
#define W_REGRET 105
#define H_REGRET 55

int gPiece = BPIECE;
int gBoard[15][15] = { 0 };
int gPlayer = 1;
int gPlayer1;
int gPlayer2;

STACK_RECORD gStack;

int main() {
	int round = 1, flagEnd = 0, flagwithdraw = 0;
	int x = 7, y = 7;
	gStack.top = 0;

	//棋局准备
	memset(gStack.date[0].board, '0', sizeof(gStack.date[0].board));
	gPlayer1 = menu();
	if (gPlayer1 == 1) {
		gPlayer2 = 2;
	}
	else {
		gPlayer2 = 1;
	}
	drawBoard();

	//棋局开始&结束
	while (1) {
		if (gPlayer == gPlayer1) {
			while (!(flagwithdraw = human(&x, &y)));
		}
		else {
			while (!AI(&x, &y, round));
		}
		//得到的xy是修正过的坐标（棋盘坐标0-14）
		if (flagwithdraw != 2) {
			if (gBoard[x][y] == EMPTY) {
				gBoard[x][y] = gPiece;

				drawPiece(x, y);
				highlight(x, y, gStack.date[gStack.top].x, gStack.date[gStack.top].y, round);
				push_record(x, y);

				//test
				if (gPlayer == gPlayer1) {
					printf("human (%d, %d)\n\n", x, y);
				}
				else {
					printf("AI (%d, %d)\n\n", x, y);
				}

				flagEnd = endJudge(x, y);
				if (round >= 15 * 15) {
					flagEnd = 1;
				}
				turnRound(flagEnd);//更换棋子（到对方下棋）
				round++;
				if (gPlayer == gPlayer1) {
					gPlayer = gPlayer2;
				}
				else {
					gPlayer = gPlayer1;
				}

				if (end(flagEnd, round) == 1) {
					break;
				}
			}
		}
		else {
			round -= 2;
			if (round <= 0) {
				round = 1;
			}
			flagwithdraw = 0;
		}
	}
	return 0;
}
