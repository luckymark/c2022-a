#include<cstdio>
#include<cstring>
#include <stdbool.h>
#include "ChessData.h"
#include "AI.h"


void calculateScore(ChessData* chess)
{
	int personNum = 0;           //棋手在这个方向连续有多少棋子
	int aiNum = 0;               //AI方连续有多少个棋子
	int emptyNum = 0;            //该方向上空白位的数量
	//数组清零
	memset(chess->Scoremap, 0, sizeof(chess->Scoremap));

	for (int row = 0; row < BOARD_SIZE; row++)            //遍历整个棋盘
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{

			//对每个点进行分数计算 （α-β剪枝算法能不能整一整？）
			if (chess->Chessmap[col][row] == 0)
			{
				for (int x = -1; x <= 1; x++)
				{
					for (int y = -1; y <= 1; y++)
					{
						if (x == 0 && y == 0)              //中心点无需
							continue;
						aiNum = 0;
						personNum = 0;
						emptyNum = 0;
						//假设黑棋在这个地方落子，连续有多少个黑棋，是否有空白
						for (int i = 1; i <= 4; i++)       //找连续四个
						{
							int curRow = row + i * y;      //当前位置
							int curCol = col + i * x;

							if (curRow >= 0 && curRow < BOARD_SIZE &&
								curCol >= 0 && curCol < BOARD_SIZE &&
								chess->Chessmap[curCol][curRow] == 1)
							{
								personNum++;
							}
							//碰到间断处
							else if (curRow >= 0 && curRow < BOARD_SIZE &&
								     curCol >= 0 && curCol < BOARD_SIZE && 
								     chess->Chessmap[curCol][curRow] == 0)
							{
								emptyNum++;
								break;
							}
							else                           //遇到白棋
							{
								break;
							}
						}

						//反向继续判断计算
						for (int i = 1; i <= 4; i++)
						{
							int curRow = row - i * y;
							int curCol = col - i * x;

							if (curRow >= 0 && curRow < BOARD_SIZE &&
								curCol >= 0 && curCol < BOARD_SIZE && 
								chess->Chessmap[curCol][curRow] == 1)
							{
								personNum++;
							}
							else if (curRow >= 0 && curRow < BOARD_SIZE &&
								     curCol >= 0 && curCol < BOARD_SIZE && 
								     chess->Chessmap[curCol][curRow] == 0)
							{
								emptyNum++;
								break;
							}
							else
							{
								break;
							}
						}
						
						//黑棋的积分
						if (personNum == 1)         //连二
						{
							chess->Scoremap[col][row] += 10;
						}
						else if (personNum == 2)
						{
							if (emptyNum == 1)      //死三
							{
								chess->Scoremap[col][row] += 30;
							}
							else if (emptyNum == 2) //活三
							{
								chess->Scoremap[col][row] += 40;
							}
						}
						else if (personNum == 3)
						{
							if (emptyNum == 1)      //死四
							{
								chess->Scoremap[col][row] += 60;
							}
							else if (emptyNum == 2) //活四
							{
								chess->Scoremap[col][row] += 200;
							}
						}
						else if (personNum == 4)
						{
							chess->Scoremap[col][row] += 20000;
						}

						//白棋落子所得分
						emptyNum = 0;

						for (int i = 1; i <= 4; i++)
						{
							int curRow = row + i * y;
							int curCol = col + i * x;

							if (curRow >= 0 && curRow < BOARD_SIZE &&
								curCol >= 0 && curCol < BOARD_SIZE && 
								chess->Chessmap[curCol][curRow] == -1)
							{
								aiNum++;
							}
							else if (curRow >= 0 && curRow < BOARD_SIZE &&
								     curCol >= 0 && curCol < BOARD_SIZE &&
								     chess->Chessmap[curCol][curRow] == 0)
							{
								emptyNum++;
								break;
							}
							else
							{
								break;
							}
						}
						//反向
						for (int i = 1; i <= 4; i++)
						{
							int curRow = row - i * y;
							int curCol = col - i * x;

							if (curRow >= 0 && curRow < BOARD_SIZE &&
								curCol >= 0 && curCol < BOARD_SIZE && 
								chess->Chessmap[curCol][curRow] == -1)
							{
								aiNum++;
							}
							else if (curRow >= 0 && curRow < BOARD_SIZE &&
								     curCol >= 0 && curCol < BOARD_SIZE &&
								     chess->Chessmap[curCol][curRow] == 0)
							{
								emptyNum++;
								break;
							}
							else
							{
								break;
							}
						}

						//白棋的得分
						if (aiNum == 0)
						{
							chess->Scoremap[col][row] += 5;
						}
						else if (aiNum == 1)
						{
							chess->Scoremap[col][row] += 10;
						}
						else if (aiNum == 2)
						{
							if (emptyNum == 1)
							{
								chess->Scoremap[col][row] += 25;
							}
							else if (emptyNum == 2)
							{
								chess->Scoremap[col][row] += 50;
							}
						}
						else if (aiNum == 3)
						{
							if (emptyNum == 1)
							{
								chess->Scoremap[col][row] += 55;
							}
							else if (emptyNum == 2)
							{
								chess->Scoremap[col][row] += 10000;
							}
						}
						else if (aiNum >= 4)
						{
							chess->Scoremap[col][row] += 30000;
						}
					}
				}
			}
		}
	}
}

chessPos think(ChessData* chess)                //找到最大值，即最优点
{
	struct chessPos data;
	data.col = 0;
	data.row = 0;
	calculateScore(chess);
	int maxScore = 0;
	int size = BOARD_SIZE;
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->Chessmap[col][row] == 0)
			{
				if (chess->Scoremap[col][row] > maxScore)
				{
					maxScore = chess->Scoremap[col][row];
					data.col = col;
					data.row = row;
				}
			}
		}
	}
	return data;
}

bool checkOver(chessPos* pos, ChessData* chess)
{
	int row = pos->row;         //自动变量
	int col = pos->col;         //在下的最优子出开始判断
	//水平方向
	for (int i = 0; i < 4; i++)
	{
		if (col - i >= 0 && col - i + 4 < BOARD_SIZE &&             //在棋盘内
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 1][row] &&
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 2][row] &&
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 3][row] &&
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 4][row]) {
			return true;
		}
	}
	//垂直方向
	for (int i = 0; i < 4; i++)
	{
		if (row - i >= 0 && row - i + 4 < BOARD_SIZE &&
			chess->Chessmap[col][row - i] == chess->Chessmap[col][row - i + 1] &&
			chess->Chessmap[col][row - i] == chess->Chessmap[col][row - i + 2] &&
			chess->Chessmap[col][row - i] == chess->Chessmap[col][row - i + 3] &&
			chess->Chessmap[col][row - i] == chess->Chessmap[col][row - i + 4]) {
			return true;
		}
	}

	// "/" 方向
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 && row - i + 4 < BOARD_SIZE && col + i - 4 >= 0 && col + i < BOARD_SIZE &&
			chess->Chessmap[col + i][row - i] == chess->Chessmap[col + i - 1][row - i + 1] &&
			chess->Chessmap[col + i][row - i] == chess->Chessmap[col + i - 2][row - i + 2] &&
			chess->Chessmap[col + i][row - i] == chess->Chessmap[col + i - 3][row - i + 3] &&
			chess->Chessmap[col + i][row - i] == chess->Chessmap[col + i - 4][row - i + 4]) {
			return true;
		}
	}

	// "\"方向
	for (int i = 0; i < 5; i++)
	{
		if (col - i >= 0 && row - i >= 0 && col - i + 4 < BOARD_SIZE && row - i + 4 < BOARD_SIZE &&
			chess->Chessmap[col - i][row - i] == chess->Chessmap[col - i + 1][row - i + 1] &&
			chess->Chessmap[col - i][row - i] == chess->Chessmap[col - i + 2][row - i + 2] &&
			chess->Chessmap[col - i][row - i] == chess->Chessmap[col - i + 3][row - i + 3] &&
			chess->Chessmap[col - i][row - i] == chess->Chessmap[col - i + 4][row - i + 4]) {
			return true;
		}
	}
	return false;
}