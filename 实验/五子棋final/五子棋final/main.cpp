#include <graphics.h>
#include <conio.h>
#include "GameModel.h"
#include "tools.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

ChessData game; // 游戏指针
int clickPosRow, clickPosCol; // 存储点击的位置

IMAGE chessBlackImg;
IMAGE chessWhiteImg;
IMAGE background;

#define INIT_SCORE  1000
int score = INIT_SCORE; // 当前分数
void init() {
	initgraph(897, 895);
	loadimage(&background, _T("棋盘.jpg"));
	putimage(0, 0, &background);

	mciSendString(_T("start.wav"), 0, 0, 0);
		
	loadimage(&chessBlackImg, _T("black.png"), BLOCK_SIZE, BLOCK_SIZE, true);
	loadimage(&chessWhiteImg, _T("white.png"), BLOCK_SIZE, BLOCK_SIZE, true);

	// 初始化游戏模型
	initChessData(&game);
}

void chessDown(int row, int col, chessKind kind) {
	mciSendString(_T("down8.WAV"), 0, 0, 0);

	int x = leftBoard + col * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
	int y = topBoard + row * BLOCK_SIZE - 0.5 * BLOCK_SIZE;

	if (kind == CHESS_WHITE) {
		drawPNG(&chessWhiteImg, x, y);
	}
	else {
		drawPNG(&chessBlackImg, x, y);
	}
}

void manGo() {
	chessDown(clickPosRow, clickPosCol, CHESS_BLACK);

	updateGameMap(&game, clickPosRow, clickPosCol);
}

bool checkOver() {
	if (checkWin(&game, clickPosRow, clickPosCol)) {
		Sleep(1500);
		if (game.playerSign == false) {  //黑棋赢（玩家赢）,此时标记已经反转，轮到白棋落子
			mciSendString(_T("不错.mp3"), 0, 0, 0);
			loadimage(0, _T("胜利.jpg"));
			Sleep(3500);
			score += 100;
		}
		else {
			mciSendString(_T("失败.mp3"), 0, 0, 0);
			loadimage(0, _T("失败.jpg"));
			Sleep(3500);
			score -= 100;
		}

		
		return true;
	}
	return false;
}

bool clickBoard(MOUSEMSG msg) {
	int x = msg.x;
	int y = msg.y;

	int col = (x - MARGIN) / BLOCK_SIZE;
	int row = (y - MARGIN) / BLOCK_SIZE;

	int leftTopPosX = MARGIN + BLOCK_SIZE * col;
	int leftTopPosY = MARGIN + BLOCK_SIZE * row;

	int len;
	int selectPos = false;

	do {
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < VAGUE_DISTANCE) {
			clickPosRow = row;
			clickPosCol = col;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selectPos = true;
			}
			break;
		}

		// 距离右上角的距离
		len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < VAGUE_DISTANCE) {
			clickPosRow = row;
			clickPosCol = col + 1;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selectPos = true;
			}
			break;
		}

		// 距离左下角的距离
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - BLOCK_SIZE) * (y - leftTopPosY - BLOCK_SIZE));
		if (len < VAGUE_DISTANCE) {
			clickPosRow = row + 1;
			clickPosCol = col;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selectPos = true;
			}
			break;
		}

		// 距离右下角的距离
		len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY - BLOCK_SIZE) * (y - leftTopPosY - BLOCK_SIZE));
		if (len < VAGUE_DISTANCE) {
			clickPosRow = row + 1;
			clickPosCol = col + 1;

			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selectPos = true;
			}
			break;
		}
	} while (0);

	return selectPos;
}

void AI_GO() {
	position point = AI_GO(&game);
	clickPosRow = point.row;
	clickPosCol = point.col;

	Sleep(1000); //AI计算的太快，此处以假装思考
	chessDown(clickPosRow, clickPosCol, CHESS_WHITE);
	updateGameMap(&game, clickPosRow, clickPosCol);
}


int main(void) {
	init();

	while (1) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && clickBoard(msg)) {
			manGo();
			if (checkOver()) {
				init();
				continue;
			}

			AI_GO();
			if (checkOver()) {
				init();
				continue;
			}
		}
	}

	closegraph();
	return 0;
}
