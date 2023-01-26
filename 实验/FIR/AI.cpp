#include "AI.h"
#include "Basic.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <stdio.h>

#define CENTRE 7
#define SDEPTH 4
#define EXTENTION 1
#define PINF 2147483647
#define NINF -2147483648

Direction DIR[8] = { {0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1} };
int RECORD_SCORE[15][15];
int SCORE[3][6] = { {0,20,300,1800,5000,100000},{0,10,100,600,2100,100000},{0,0,0,0,0,100000} };//SCORE[n_rival][n_self],顺序:活，眠，死

void findBoundary(int boundary[], int** vBoard) {
	//找出囊括落有棋子的最小矩形
	int extention = EXTENTION;
	int flag = 0;

	//上边界，从上往下
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			if (vBoard[x][y] != EMPTY) {
				boundary[0] = y;
				flag = 1;
				break;
			}
		}
		if (flag) break;
	}
	flag = 0;
	//下边界，从下往上
	for (int y = 14; y >= 0; y--) {
		for (int x = 0; x < 15; x++) {
			if (vBoard[x][y] != EMPTY) {
				boundary[1] = y;
				flag = 1;
				break;
			}
		}
		if (flag) break;
	}
	flag = 0;
	//左边界，从左往右
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			if (vBoard[x][y] != EMPTY) {
				boundary[2] = x;
				flag = 1;
				break;
			}
		}
		if (flag) break;
	}
	flag = 0;
	//右边界，从右往左
	for (int x = 14; x >= 0; x--) {
		for (int y = 0; y < 15; y++) {
			if (vBoard[x][y] != EMPTY) {
				boundary[3] = x;
				flag = 1;
				break;
			}
		}
		if (flag) break;
	}
	flag = 0;

	//扩展
	for (int i = 0; i <= 2; i += 2) {//上，左
		for (int j = 0; j < EXTENTION; j++) {
			if (boundary[i] - 1 >= 0) {
				boundary[i]--;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i <= 3; i += 2) {//下，右
		for (int j = 0; j < EXTENTION; j++) {
			if (boundary[i] + 1 <= 14) {
				boundary[i]++;
			}
			else {
				break;
			}
		}
	}
}

int maxminSearch(int depth, int player, int** vBoard, int alpha, int beta) {
	int score = 0;
	int boundary[4] = { 0, 14, 0, 14 }; //上下左右
	int x1, x2, y1, y2;

	if (player == BPIECE) {
		player = WPIECE;
	}
	else {
		player = BPIECE;
	}

	//叶结点
	if (depth == 0) {
		return evaluate(vBoard);
	}

	findBoundary(boundary, vBoard);
	y1 = boundary[0];
	y2 = boundary[1];
	x1 = boundary[2];
	x2 = boundary[3];

	//max层
	if (depth % 2 == 0) {
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (vBoard[i][j] == EMPTY) {
					vBoard[i][j] = player;
					score = maxminSearch(depth - 1, player, vBoard, alpha, beta);
					vBoard[i][j] = EMPTY;
					if (depth == SDEPTH) {
						RECORD_SCORE[i][j] = score;
					}
					if (score > alpha){			// 对于AI，更新极大值 
						alpha = score;
					}
					if (alpha >= beta){   		// Alpha-剪枝
						return alpha;
					}
				}
			}
		}
		return alpha;
	}
	//min层
	else {
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (vBoard[i][j] == EMPTY) {
					vBoard[i][j] = player;
					score = maxminSearch(depth - 1, player, vBoard, alpha, beta);
					vBoard[i][j] = EMPTY;
					if (depth == SDEPTH) {
						RECORD_SCORE[i][j] = score;
					}
					if (score < beta) {			// 对于human，更新极小值 
						beta = score;
					}
					if (alpha >= beta) {   		// Beta-剪枝
						return beta;
					}
				}
			}
		}
		return beta;
	}
}

int getScore(int** vBoard, int player) {
	int rival = 0, score = 0;
	if (player == BPIECE) {
		rival = WPIECE;
	}
	else {
		rival = BPIECE;
	}

	for (int dir = 0; dir < 4; dir++) {
		for (int i = 0; i <= 14; i++) {
			for (int j = 0; j <= 14; j++) {
				if (vBoard[i][j] != player) continue;
				int n_player = 1, n_rival = 0;
				int x = i + DIR[dir].x;
				int y = j + DIR[dir].y;

				while (x >= 0 && x <= 14 && y >= 0 && y <= 14 && vBoard[x][y] == player ){
					n_player++;
					x = x + DIR[dir].x, y = y + DIR[dir].y;
				}
				if (x >= 0 && x <= 14 && y >= 0 && y <= 14) {
					if (vBoard[x][y] == rival || x < 0 || x > 14 || y < 0 || y > 14) {
						n_rival++;
					}
				}
				//向反方向遍历
				x = i - DIR[dir].x, y = j - DIR[dir].y;
				while (x >= 0 && x <= 14 && y >= 0 && y <= 14 && vBoard[x][y] == player ){
					n_player++;
					x = x - DIR[dir].x, y = y - DIR[dir].y;
				}
				if (x >= 0 && x <= 14 && y >= 0 && y <= 14) {
					if (vBoard[x][y] == rival || x < 0 || x > 14 || y < 0 || y > 14) {
						n_rival++;
					}
				}
				if (n_player > 5) n_player = 5;
				score += SCORE[n_rival][n_player];
			}
		}
	}
	return score;
}

int evaluate(int** vBoard) {
	//对整个棋局进行评估
	int aiScore = 0, huScore = 0;
	int ai = gPiece, human;

	if (ai == BPIECE) {
		human = WPIECE;
	}
	else {
		human = BPIECE;
	}

	aiScore = getScore(vBoard, ai);
	huScore = getScore(vBoard, human);
	
	return aiScore - huScore;
}

int AI(int* x, int* y, int round) {

	int player = gPiece;
	int flag = 0;
	int alpha = NINF, beta = PINF, maxScore = NINF;

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			RECORD_SCORE[i][j] = NINF;
		}
	}

	if (gBoard[CENTRE][CENTRE] == EMPTY) {
		Sleep(500);
		*x = CENTRE;
		*y = CENTRE;
		flag = 1;
	}
	else if (round == 2) {
		Sleep(500);
		secondRound(x, y);
		flag = 1;
	}
	else {
		int** vBoard = (int**)malloc(sizeof(int*) * 15);
		for (int i = 0; i < 15; i++) {
			if (vBoard != NULL) {
				vBoard[i] = (int*)malloc(sizeof(int) * 15);
			}
		}
		//把当前棋盘复制到假想棋盘中
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (vBoard != NULL) {
					if (vBoard[i] != NULL) {
						vBoard[i][j] = gBoard[i][j];
					}
				}
			}
		}

		if (player == BPIECE) {
			player = WPIECE;
		}
		else {
			player = BPIECE;
		}
		maxminSearch(SDEPTH, player, vBoard, alpha, beta);

		int boundary[4], x1, x2, y1, y2;

		findBoundary(boundary, vBoard);
		y1 = boundary[0];//上
		y2 = boundary[1];//下
		x1 = boundary[2];//左
		x2 = boundary[3];//右

		//test 输出分数
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (gBoard[i][j] == EMPTY)
					printf("(%d, %d) %d\n", i, j, RECORD_SCORE[i][j]);
			}
		}

		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (RECORD_SCORE[i][j] > maxScore && gBoard[i][j] == EMPTY) {
					maxScore = RECORD_SCORE[i][j];
					*x = i;
					*y = j;
				}
			}
		}

		if (gBoard[*x][*y] == EMPTY) {
			flag = 1;
		}
		free(vBoard);
	}
	return flag;
}

void secondRound(int* x, int* y) {
	srand((unsigned int)time(0));
	int t;
	t = rand() % 8;
	*x = CENTRE + DIR[t].x;
	*y = CENTRE + DIR[t].y;
}

void swap(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int Max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int Min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}