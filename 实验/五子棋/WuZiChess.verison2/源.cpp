/*������־
Ŀ���Ϊ���²���:
1.��ʼ���棨������Ϸ���򽲽⣩
2.��ʼ�����������̣��ڰ��壬ʤ����ʧ�ܽ���ͼƬ�ز�
3.��ģ����λ�����������ڵ���
4.���������ź�����
5.AI�������Ӻ��Զ�����
6.�ж�ʤ��
7.չʾʤ����ʧ�ܽ���
version.2��������:
8.��ҿ�ѡ�Ⱥ���
9.���ӻ��幦��
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
//��ҳ�ʼ����Ϊ0
#define INIT_SCORE 0
//����AI���ֵ��ж�
bool initiative;
bool initsign=true;
int once = 1;
//��ҷ���
int score;
//�ڰ���
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

//��ʾ��Ч�����ʵ��λ�ã����̵ڼ��У��ڼ��У�
int clickPosRow, clickPosCol;
//���Ӻ�ʵʱ��������
void updateGameMap(ChessData* data, int row, int col);
//������Ӻ���
void Man_Go();
//AI���Ӻ���
void AI_GO();
//�ж�ʤ��
bool checkOver();
//����ҵ÷�
void initScore();
//ǿ��AI��һ���������������м�
void initAI(ChessData* data);
//���庯��
void back(ChessData* data);
//������ʼ����
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
//�������̡�����ͼƬ�ز�
void init() {
	//�������̴���
	initgraph(897, 895);
	loadimage(0, "res/����2.jpg");

	//��ӻ�ӭ��Ч
	mciSendString("play res/start.wav", 0, 0, 0);

	loadimage(&chessBlackImg, "res/black.png", BLOCK_SIZE, BLOCK_SIZE, true);
	loadimage(&chessWhiteImg, "res/white.png", BLOCK_SIZE, BLOCK_SIZE, true);

	initChessData(&game);
	initScore();
	head->next = NULL;
}

//ģ���㷨��������������������������λ�ã����������ڵ�λ��
bool clickBoard(MOUSEMSG msg)
{
	int col = (msg.x - margin_x) / BLOCK_SIZE;
	int row = (msg.y - margin_y) / BLOCK_SIZE;

	int leftTopPosX = margin_x + col * BLOCK_SIZE;
	int leftTopPosY = margin_y + row * BLOCK_SIZE;

	int selctPos = false;


	do {//����
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
		//����
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
		//����
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
		//����
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
//���Ӻڰ��壬����ͼƬ
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
	//����
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
	//����
	while (!initiative) {
		//Ĭ��AI��һ�����Ž������м�
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
			mciSendString("play res/ʤ��.mp3", 0, 0, 0);
			loadimage(0, "res/ʤ��.jpg");
			score += 100;
		}
		else {
			mciSendString("play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, "res/ʧ��.jpg");
			score -= 100;
		}

		char scoreText[64];
		sprintf(scoreText, "��ǰ������%d", score);
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
	settextstyle(70, 0, "΢���ź�");

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
	loadimage(0, "res/����2.jpg");
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