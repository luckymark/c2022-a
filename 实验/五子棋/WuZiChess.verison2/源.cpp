/*开发日志
目标分为以下部分:
1.开始界面（包含游戏规则讲解）
2.初始化，导入棋盘，黑白棋，胜利、失败界面图片素材
3.用模糊定位法让棋子落在点上
4.玩家用鼠标信号落子
5.AI评估优劣后自动落子
6.判断胜负
7.展示胜利、失败界面
version.2更新内容:
8.玩家可选先后手
9.增加悔棋功能
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <graphics.h>
#include<Windows.h>
#include<mmsystem.h>
#include"tools.h"
#include"ChessData.h"
#include<math.h>
#pragma comment(lib,"winmm.lib")
#include< conio.h>
//玩家初始分数为0
#define INIT_SCORE 0
//用于AI先手的判断
bool initiative;
bool initsign=true;
int once = 1;
//玩家分数
int score;
//黑白棋
typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;

typedef struct backstorage {
	int row;
	int col;
	struct backstorage* next;
}Node;

Node *head=(Node*)malloc(sizeof(Node));

void creatbackstorage(int clickPosRow, int clickPosCol);

void recover(ChessData* data);

IMAGE chessBlackImg;
IMAGE chessWhiteImg;

ChessData game;

//表示有效点击的实际位置（棋盘第几行，第几列）
int clickPosRow, clickPosCol;
//落子后实时更新棋盘
void updateGameMap(ChessData* data, int row, int col);
//玩家下子函数
void Man_Go();
//AI下子函数
void AI_GO();
//判断胜负
bool checkOver();
//算玩家得分
void initScore();
//强制AI第一步走优势最大的最中间
void initAI(ChessData* data);
//悔棋函数
void back(ChessData* data);
//创建开始界面
int hello() {
	initgraph(400, 800);
	loadimage(0, "res/hello3.png");
	mciSendString("play res/hello.mp3", 0, 0, 0);
	int n = 0;
	do {
		fflush(stdin);
		n = _getch();
	} while (n != '1' &&n != '2');
	if (n == '1') 
		initiative = true;
	else initiative = false;
	system("cls");
	return 0;
}
//载入棋盘、棋子图片素材
void init() {
	//创建棋盘窗口
	initgraph(897, 895);
	loadimage(0, "res/棋盘2.jpg");

	//添加欢迎音效
	mciSendString("play res/start.wav", 0, 0, 0);

	loadimage(&chessBlackImg, "res/black.png", BLOCK_SIZE, BLOCK_SIZE, true);
	loadimage(&chessWhiteImg, "res/white.png", BLOCK_SIZE, BLOCK_SIZE, true);

	initChessData(&game);
	initScore();
	head->next = NULL;
}

//模糊算法算左上右上左下右下鼠标坐标的位置，另棋子落在点位上
bool clickBoard(MOUSEMSG msg)
{
	int col = (msg.x - margin_x) / BLOCK_SIZE;
	int row = (msg.y - margin_y) / BLOCK_SIZE;

	int leftTopPosX = margin_x + col * BLOCK_SIZE;
	int leftTopPosY = margin_y + row * BLOCK_SIZE;

	int selctPos = false;


	do {//左上
		int len = sqrt((msg.x - leftTopPosX) * (msg.x - leftTopPosX) +
			(msg.y - leftTopPosY) * (msg.y - leftTopPosY));
		if (len < POS_OFFSET) {
			clickPosRow = row;
			clickPosCol = col;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;
		}
		//右上
		int posX = leftTopPosX + BLOCK_SIZE;
		int posY = leftTopPosY;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET) {
			clickPosRow = row;
			clickPosCol = col + 1;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;
		}
		//右下
		posX = leftTopPosX + BLOCK_SIZE;
		posY = leftTopPosY + BLOCK_SIZE;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET) {
			clickPosRow = row + 1;
			clickPosCol = col + 1;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;
		}
		//左下
		posX = leftTopPosX;
		posY = leftTopPosY + BLOCK_SIZE;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET) {
			clickPosRow = row + 1;
			clickPosCol = col;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;

		}
	} while (0);
	return selctPos;
}
//落子黑白棋，放置图片
void chessDown(int row, int col, chess_kind_t kind) {
	mciSendString("play res/down7.WAV", 0, 0, 0);

	int x = margin_x + clickPosCol * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
	int y = margin_y + clickPosRow * BLOCK_SIZE - 0.5 * BLOCK_SIZE;

	if (kind == CHESS_WHITE) {
		drawPNG(&chessWhiteImg, x, y);
	}
	else {
		drawPNG(&chessBlackImg, x, y);
	}
}

int main(void) {
	hello();
	init();
	//先手
	while (initiative) {
		MOUSEMSG msg = GetMouseMsg();
		while (1) {
			if (msg.uMsg == WM_RBUTTONDOWN ) {
				back(&game);
				back(&game);
				break;
			}
			break;
			if (msg.uMsg == WM_LBUTTONDOWN )
				break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN && clickBoard(msg)) {
			Man_Go();
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
	//后手
	while (!initiative) {
		//默认AI第一步最优解是走中间
		if (once) {
			game.playerFlag = false;
			initAI(&game);
			while (1) {
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN && clickBoard(msg)) {
					Man_Go();
					break;
				}
			}
			once = 0;
		}

		MOUSEMSG msg = GetMouseMsg();
		while (1) {
			if (msg.uMsg == WM_RBUTTONDOWN) {
				back(&game);
				back(&game);
				break;
			}
			break;
			if (msg.uMsg == WM_LBUTTONDOWN)
				break;
		}
			if (initsign) {
				AI_GO();
				initsign = false;
				if (checkOver()) {
					init();
					continue;
				}
			}
			if (msg.uMsg == WM_LBUTTONDOWN && clickBoard(msg)) {
				Man_Go();
				initsign = true;
				if (checkOver()) {
					init();
					continue;
				}
			}
		
	}
	closegraph();
	return 0;
}

void Man_Go() {
	creatbackstorage(clickPosRow, clickPosCol);
	chessDown(clickPosRow, clickPosCol, CHESS_BLACK);
	updateGameMap(&game, clickPosRow, clickPosCol);
}

void AI_GO() {
	point_t point = actionByAI(&game);
	clickPosRow = point.row;
	clickPosCol = point.col;
	Sleep(1000);
	creatbackstorage(clickPosRow, clickPosCol);
	chessDown(clickPosRow, clickPosCol, CHESS_WHITE);
	updateGameMap(&game, clickPosRow, clickPosCol);
}

bool checkOver() {
	if (checkWin(&game, clickPosRow, clickPosCol)) {
		Sleep(1500);
		if (game.playerFlag == false) {
			mciSendString("play res/胜利.mp3", 0, 0, 0);
			loadimage(0, "res/胜利.jpg");
			score += 100;
		}
		else {
			mciSendString("play res/失败.mp3", 0, 0, 0);
			loadimage(0, "res/失败.jpg");
			score -= 100;
		}

		char scoreText[64];
		sprintf(scoreText, "当前分数：%d", score);
		outtextxy(310, 800, scoreText);

		FILE* fp = fopen("score.data", "wb");
		fwrite(&score, sizeof(score), 1, fp);
		fclose(fp);

		_getch();
		return true;
	}
	return false;
}

void initScore() {
	settextcolor(WHITE);
	settextstyle(70, 0, "微软雅黑");

	FILE* fp = fopen("score.txt", "rb");
	if (fp == NULL) {
		score = INIT_SCORE;
	}
	else {
		fread(&score, sizeof(score), 1, fp);
	}
	if (fp)fclose(fp);
}

void updateGameMap(ChessData* data, int row, int col)
{
	if (!data)return;
	
	if (data->playerFlag)
		data->chessMap[row][col] = -1;
	else
		data->chessMap[row][col] = 1;
	data->playerFlag = !data->playerFlag;

}

void initAI(ChessData* data) {
		clickPosRow = 6;
		clickPosCol = 6;
		chessDown(clickPosRow, clickPosCol, CHESS_WHITE);
		updateGameMap(&game, clickPosRow, clickPosCol);
}

void creatbackstorage(int clickPosRow,int clickPosCol) {
	Node* p;
	p = (Node*)malloc(sizeof(Node));
	if (p != NULL) {
		p->col = clickPosCol;
		p->row = clickPosRow;
		p->next = NULL;
	}
	if (head->next == NULL) {
		head->next = p;
	}
	else {
		Node* tail = head;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = p;
	}
}

void back(ChessData* data) {
	if (head->next == NULL) {
		return;
	}
	else {
		Node* tail = head;
		while (tail->next->next != NULL) {
			tail = tail->next;
		}
		data->chessMap[tail->next->row][tail->next->col] = 0;
		mciSendString("play res/repent1.mp3", 0, 0, 0);
		tail->next = NULL;
		free(tail->next);
		
	}
	recover(data);
	
	return;
}

void recover(ChessData* data) {
	system("cls");
	initgraph(897, 895);
	loadimage(0, "res/棋盘2.jpg");
	for (int i = 0; i < BOARD_GRADE_SIZE; i++) {
		for (int j = 0; j < BOARD_GRADE_SIZE; j++) {
			if (data->chessMap[i][j] == -1)
			{
				int x = margin_x + j * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
				int y = margin_y + i * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
					drawPNG(&chessBlackImg, x, y);
			}
			if (data->chessMap[i][j] == 1)
			{
				int x = margin_x + j * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
				int y = margin_y + i * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
				drawPNG(&chessWhiteImg, x, y);
			}
		}
	}
}