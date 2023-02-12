#include"ChessData.h"
#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
//初始化棋盘
void initChessData(struct ChessData* data) {
	if (!data) {//data==NULL
		return;
	}

	memset(data->chessMap, 0, sizeof(data->chessMap));
	memset(data->scoreMap, 0, sizeof(data->scoreMap));
	data->playerFlag = true;
}

//计算场上落点分值
void calculateScore(ChessData* data) {
	if (!data)return;

	int personNum = 0;
	int botNum = 0;
	int emptyNum = 0;

	memset(data->scoreMap, 0, sizeof(data->scoreMap));
	for (int row = 0; row < BOARD_GRADE_SIZE; row++)
		for (int col = 0; col < BOARD_GRADE_SIZE; col++) {
			if (row >= 0 && col >= 0 && data->chessMap[row][col] == 0) {
				int directs[4][2] = { {1,0},{1,1},{0,1} ,{-1,1} };
				for (int k = 0; k < 4; k++) {
					int x = directs[k][0];
					int y = directs[k][1];

					personNum = 0;
					botNum = 0;
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						if (row + i * y >= 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x >= 0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == 1) {
							personNum++;
						}
						else if (row + i * y >= 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x >= 0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}
					for (int i = 1; i <= 4; i++) {
						if (row - i * y >= 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x >= 0 && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == 1) {
							personNum++;
						}
						else if (row - i * y >= 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x >= 0 && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}
					if (personNum == 1)
						data->scoreMap[row][col] += 10;
					else if (personNum == 2) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 30;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 40;
					}
					else if (personNum == 3) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 60;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 200;
					}
					else if (personNum == 4)
						data->scoreMap[row][col] += 20000;

					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						if (row + i * y > 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x>0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == -1) {
							botNum++;
						}
						else if (row + i * y > 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x>0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}

					for (int i = 1; i <= 4; i++) {
						if (row - i * y > 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x>0 && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == -1) {
							botNum++;
						}
						else if (row - i * y > 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}
					if (botNum == 0)
						data->scoreMap[row][col] += 5;
					else if (botNum == 1)
						data->scoreMap[row][col] += 10;
					else if (botNum == 2) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 25;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 50;
					}
					else if (botNum == 3) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 55;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 300;
					}
					else if (botNum == 4)
						data->scoreMap[row][col] += 30000;
				}
			}
		}
}

//根据场上点位分值算出AI的落点
point_t actionByAI(ChessData* data) {
	calculateScore(data);

	int maxScore = 0;

	point_t maxPoints[BOARD_GRADE_SIZE * BOARD_GRADE_SIZE] = { 0 };
	int k = 0;

	for (int row = 0; row < BOARD_GRADE_SIZE; row++)
		for (int col = 0; col < BOARD_GRADE_SIZE; col++)
		{

			if (data->chessMap[row][col] == 0)
			{
				if (data->scoreMap[row][col] > maxScore)
				{
					memset(maxPoints, 0, sizeof(maxPoints));
					k = 0;
					maxScore = data->scoreMap[row][col];

					maxPoints[k].row = row;
					maxPoints[k].col = col;
					k++;
				}
				else if (data->scoreMap[row][col] == maxScore) {

					maxPoints[k].row = row;
					maxPoints[k].col = col;
					k++;
				}
			}
		}
	srand((unsigned)time(0));
	int index = rand() % k;
	return maxPoints[index];
}
//判断场上是否出现五子连珠
bool checkWin(ChessData* game, int row, int col)
{


	for (int i = 0; i < 5; i++)
	{

		if (col - i >= 0 &&
			col - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 1] &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 2] &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 3] &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 4])
			return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 1][col] &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 2][col] &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 3][col] &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 4][col])
			return true;
	}

	for (int i = 0; i < 5; i++)
	{
		if (row + i < BOARD_GRADE_SIZE &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 1][col - i + 1] &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 2][col - i + 2] &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 3][col - i + 3] &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 4][col - i + 4])
			return true;
	}

	for (int i = 0; i < 5; i++)
	{

		if (row - i >= 0 &&
			row - i + 4 < BOARD_GRADE_SIZE &&
			col - i >= 0 &&
			col - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 1][col - i + 1] &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 2][col - i + 2] &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 3][col - i + 3] &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 4][col - i + 4])
			return true;
	}
	return false;
}

