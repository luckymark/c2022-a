#include <graphics.h>
#include <conio.h>
#include "GameModel.h"
#include "tools.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

ChessData game; // ��Ϸָ��
int clickPosRow, clickPosCol; // �洢�����λ��

IMAGE chessBlackImg;
IMAGE chessWhiteImg;
IMAGE background;

#define INIT_SCORE  1000
int score = INIT_SCORE; // ��ǰ����
void init() {
	initgraph(897, 895);
	loadimage(&background, _T("����.jpg"));
	putimage(0, 0, &background);

	mciSendString(_T("start.wav"), 0, 0, 0);
		
	loadimage(&chessBlackImg, _T("black.png"), BLOCK_SIZE, BLOCK_SIZE, true);
	loadimage(&chessWhiteImg, _T("white.png"), BLOCK_SIZE, BLOCK_SIZE, true);

	// ��ʼ����Ϸģ��
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
		if (game.playerSign == false) {  //����Ӯ�����Ӯ��,��ʱ����Ѿ���ת���ֵ���������
			mciSendString(_T("����.mp3"), 0, 0, 0);
			loadimage(0, _T("ʤ��.jpg"));
			Sleep(3500);
			score += 100;
		}
		else {
			mciSendString(_T("ʧ��.mp3"), 0, 0, 0);
			loadimage(0, _T("ʧ��.jpg"));
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

		// �������Ͻǵľ���
		len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < VAGUE_DISTANCE) {
			clickPosRow = row;
			clickPosCol = col + 1;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selectPos = true;
			}
			break;
		}

		// �������½ǵľ���
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - BLOCK_SIZE) * (y - leftTopPosY - BLOCK_SIZE));
		if (len < VAGUE_DISTANCE) {
			clickPosRow = row + 1;
			clickPosCol = col;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selectPos = true;
			}
			break;
		}

		// �������½ǵľ���
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

	Sleep(1000); //AI�����̫�죬�˴��Լ�װ˼��
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
