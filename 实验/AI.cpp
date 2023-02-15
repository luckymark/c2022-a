#include<time.h>
#include<stdlib.h>
#include"point.h"
#include"check.h"
#include"AI.h"
#include"UI.h"

int canMakeMinSearch = 1;
int bTurn,round;

long double MiniMax(struct point p[25][25], int color, int depth, long double min, long double max) {
	int m, n, t = 0, br = 0;
	long double va = 0;
	if (depth == 0 || end(p) != 0)
	{
		return checkStateVal(p);
	}
	else if (color == player)
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) {
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0 &&
					((canMakeMinSearch != 0 && m >= 8 && m <= 16 && n >= 8 && n <= 16) ||
						canMakeMinSearch == 0))
				{
					if (num < 80) {
						t = 0;
						if (p[m][n].has_neighnors != 0)
							t = 1;
					}
					else {
						t = 1;
					}
					if (t == 0)
					{
						va = INFINITY;
					}
					else {
						p[m][n].state = player;
						set_neighnors(p, p[m][n], 0);
						round++;
						if (((m <= 8 || m >= 16) || (n <= 8 || n >= 16)) && canMakeMinSearch != 0) {
							canMakeMinSearch = 0;
							bTurn = round;
						}
						va = MiniMax(p, -player, depth - 1, min, max);
						p[m][n].state = 0;
						set_neighnors(p, p[m][n], 1);
						round--;
						if (bTurn > round) {
							canMakeMinSearch = 1;
						}
					}
					if (va < max)
					{
						max = va;
					}
					if (max < min)
					{
						br = 1;
						break;
					}
				}
			}
		}
		return max;
	}
	else if (color == -player)
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) {
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0 && 
					((canMakeMinSearch != 0 && m >= 8 && m <= 16 && n >= 8 && n <= 16) ||
						canMakeMinSearch == 0))
				{
					if (num < 80) {
						t = 0;
						if (p[m][n].has_neighnors != 0) {
							t = 1;
						}
					}
					else {
						t = 1;
					}
					if (t == 0)
					{
						va = -INFINITY;
					}
					else {
						p[m][n].state = -player;
						set_neighnors(p, p[m][n], 0);
						round++;
						if (((m <= 8 || m >= 16) || (n <= 8 || n >= 16)) && canMakeMinSearch != 0) {
							canMakeMinSearch = 0;
							bTurn = round;
						}
						va = MiniMax(p, player, depth - 1, min, max);
						p[m][n].state = 0;
						set_neighnors(p, p[m][n], 1);
						round--;
						if (bTurn > round) {
							canMakeMinSearch = 1;
						}
					}
					if (va > min)
					{
						min = va;
					}
					if (max < min)
					{
						br = 1;
						break;
					}
				}
			}
		}
		return min;
	}
	return 0;
}

place robotTry(struct point p[25][25], int f) {//AI 
	place MaxMove = { 12,12 }, MinMove = { 12,12 }, bestMove;
	long double MaxVal = -INFINITY;
	int neighnors;
	round = num;
	if (num == 0) return{ 12,12 };
	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			if (p[i][j].state == 0 && ((i>=8 && i <=16 && j >= 8 && j <= 16)||canMakeMinSearch == 0)) {
				if (p[i][j].has_neighnors != 0) {
					p[i][j].state = -player;
					round++;
					set_neighnors(p, p[i][j], 0);
					if (((i <= 8 || i >= 16) || (j <= 8 || j >= 16)) && canMakeMinSearch != 0) {
						canMakeMinSearch = 0;
						bTurn = round;
					}
					if (end(p) != 0) {
						return { i,j };
					}
					p[i][j].val = MiniMax(p, player, 3, -INFINITY, INFINITY);
					p[i][j].state = 0;
					set_neighnors(p, p[i][j], 1);
					round--;
					if (bTurn > round){
						canMakeMinSearch = 1;
					}
					
					if (p[i][j].val >= MaxVal) {
						MaxVal = p[i][j].val;
						bestMove = { i,j };
					}
				}
			}
		}
	}

	return bestMove;
}

place robot2(struct point p[25][25], int color, int f) {//AI (純綷一層思考)
	place max_p, min_p;
	long double min = 0, max = 0;
	if (f == 0) return { 12,12 };
	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			p[i][j].a_value = p[i][j].d_value = 0;
			if (p[i][j].state == 0) {
				p[i][j].a_value = checkVal(p, p[i][j], color);
				if (p[i][j].a_value > max) {
					max = p[i][j].a_value;
					max_p.x = i;
					max_p.y = j;
				}
				p[i][j].d_value = checkVal(p, p[i][j], -color);
				if (p[i][j].d_value > min) {
					min = p[i][j].d_value;
					min_p.x = i;
					min_p.y = j;
				}
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
