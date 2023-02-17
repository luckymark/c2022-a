#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include"point.h"
#include"check.h"
#include"AI.h"
#include"UI.h"

int bTurn;
MOVE bestMove = { {12,12},-INFINITY };

void copyBoard(point p1[25][25], point p2[25][25]){
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			p2[i][j].place = { i,j };
			if (p1[i][j].state == 1) p2[i][j].state = 1;
			else if (p1[i][j].state == 0) p2[i][j].state = 0;
			else if (p1[i][j].state == 2) p2[i][j].state = 2;
			else p2[i][j].state = -1;
		}
	}
}

void reverseBoard(point p1[25][25], point p2[25][25]) {//反轉思考
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			p2[i][j].place = { i,j };
			if (p1[i][j].state == 0) p2[i][j].state = 0;
			else if (p1[i][j].state == 2) p2[i][j].state = 2;
			else if (p1[i][j].state == 1) p2[i][j].state = -1;
			else p2[i][j].state = 1;
		}
	}
}


EvaPoint evaluate(point p[25][25])//生成最佳可能落子位置
{
	bool board[25][25] = {false};

	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			if (p[i][j].state != 0) {
				for (int k = -2; k <= 2; k++) {
					board[i + k][j] = true;
					board[i + k][j + k] = true;
					board[i + k][j - k] = true;
					board[i][j + k] = true;
				}
			}
		}
	}

	long double worth[25][25];
	EvaPoint bestPoints;
	long double w;
	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			worth[i][j] = -INFINITY;
			if (p[i][j].state == 0 && board[i][j]==true) {
				p[i][j].state = -player;
				worth[i][j] = checkStateVal(p);
				p[i][j].state = 0;
			}
		}
	}
	for (int k = 0; k < numOfEvaluate; k++) {
		w = -INFINITY;
		for (int i = MIN; i < MAX; i++) {
			for (int j = MIN; j < MAX; j++) {
				if (worth[i][j] >= w) {
					w = worth[i][j];
					bestPoints.place[k] = { i,j };
				}
			}
		}
		bestPoints.score[k] = w;
		worth[bestPoints.place[k].x][bestPoints.place[k].y] = -INFINITY;//避免重複
	}
	return bestPoints;
}

long double MiniMax(struct point p[25][25], int color, int depth, long double alpha, long double beta) {
	if (depth == 0 || end(p) != 0) {
		if (depth == 0) {
			EvaPoint P;
			P = evaluate(p);
			return P.score[0];
		}
		else return checkStateVal(p);
	}
	else if (color == -player) {//AI
		EvaPoint P;
		P = evaluate(p);

		for (int i = 0; i < numOfEvaluate; i++) {
			p[P.place[i].x][P.place[i].y].state = -player;
			long double val = MiniMax(p, player, depth - 1, alpha, beta);
			p[P.place[i].x][P.place[i].y].state = 0;;

			if (val > alpha) {
				alpha = val;
				if (depth == DEPTH) {
					bestMove.place = P.place[i];
					bestMove.val = val;
				}
			}
			if (beta<= alpha) break;
		}
		return alpha;
	}
	else {//player
		point reverseP[25][25];
		reverseBoard(p, reverseP);
		EvaPoint P;
		P = evaluate(reverseP);

		for (int i = 0; i < numOfEvaluate; i++) {
			p[P.place[i].x][P.place[i].y].state = player;
			long double val = MiniMax(p,-player,depth - 1,alpha,beta);
			p[P.place[i].x][P.place[i].y].state = 0;
			if (val < beta) beta = val;
			if (beta <= alpha) break;
		}
		return beta;
	}
}

place robot3(struct point p[25][25], int f) {//AI 
	point sameP[25][25];
	copyBoard(p, sameP);
	if (num == 0) return{ 12,12 };
	MiniMax(sameP, -player, DEPTH, -INFINITY, INFINITY);
	return bestMove.place;
}

place robot2(struct point p[25][25], int color, int f) {//AI 貪心算法(純綷一層思考)
	place max_p, min_p;
	long double min = 0, max = 0;
	if (f == 0) return { 12,12 };
	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			p[i][j].a_value = p[i][j].d_value = 0;
			if (p[i][j].state == 0) {
				p[i][j].state = color;
				p[i][j].a_value = checkPointVal(p,p[i][j], color);
				if (p[i][j].a_value > max) {
					max = p[i][j].a_value;
					max_p.x = i;
					max_p.y = j;
				}
				p[i][j].state = -color;
				p[i][j].d_value = checkPointVal(p,p[i][j], -color);
				if (p[i][j].d_value > min) {
					min = p[i][j].d_value;
					min_p.x = i;
					min_p.y = j;
				}
				p[i][j].state = 0;
			}
		}
	}
	if (max >= min) return max_p;
	else return min_p;
}

place robot(struct point p[25][25]) {// random.
	place place;
	time_t t;
	srand((unsigned)time(&t));
	place.x = rand() % (MAX - MIN + 1) + MIN;
	srand((unsigned)time(&t));
	place.y = rand() % (MAX - MIN + 1) + MIN;
	return place;
}
