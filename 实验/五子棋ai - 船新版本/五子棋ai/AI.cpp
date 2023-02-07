#include "AI.h"
#include"chess.h"
#include<windows.h>

void AI::init(Chess *chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++)
	{
		vector<int>row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
			
		}
		scoreMap.push_back(row);
	
	}
}

void AI::move()
{
	ChessPos aipos = consider();
	Sleep(400);
	chess->chessDown(&aipos, CHESS_WHITE);
}

ChessPos AI::consider()
{
	
	calculateScore();
	int size;
	size = chess->getGradeSize();
	int maxscore = 0;
	
	vector<ChessPos>maxscorepos;
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (maxscore < scoreMap[row][col])
			{
				maxscore = scoreMap[row][col];
				maxscorepos.clear();
				maxscorepos.push_back(ChessPos(row, col));

			}
			else if (maxscore == scoreMap[row][col])
			{
				maxscorepos.push_back(ChessPos(row, col));

			}
			else
			{
				continue;
			}
		}
	}
	//在同样得分的各点随机选一个点视为最高得分点
	int random = rand() % (maxscorepos.size());
	return maxscorepos[random];
	
}

void AI::calculateScore()
{
	int personNum;// (棋手有几个子连在一起）
	int aiNum;
	int emptyNum = 0;//该方向有几个空白
	for (int i = 0; i < scoreMap.size(); i++)//清空评分数组
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}
	scoreMap[7][7] = 1;
	int size = chess->getGradeSize();//获取棋盘大小
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			//评测每个落点的价值
			if (chess->getChessData(row, col) == 0)
			{
				for (int y = -1; y <= 0; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						//重置
						personNum = 0;
						aiNum = 0;
						emptyNum = 0;

						if ((!(y == 0 && x == 0))
							&& (!(y == 0 && x == 1)))
						{
							//假设黑棋（棋手）在该位置落子
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row + i * x;
								int curCol = col + i * y;
								if (curRow >= 0 && 
									curRow < size &&
									curCol >= 0 && 
									curCol < size && 
									chess->getChessData(curRow, curCol) == 1)
								{
									personNum++;
								}
								else if (curRow >= 0 && 
									curRow < size && 
									curCol >= 0 && 
									curCol < size && 
									chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//反向的计算
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row - i * x;
								int curCol = col - i * y;
								if (curRow >= 0 &&
									curRow < size && 
									curCol >= 0 && 
									curCol < size &&
									chess->getChessData(curRow, curCol) == 1)
								{
									personNum++;
								}
								else if (curRow >= 0 && 
									curRow < size && curCol >= 0 &&
									curCol < size && 
									chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//计算黑棋落子得分
							if (personNum == 1)//连二
							{
								scoreMap[row][col] += 10;

							}
							else if (personNum == 2)//连三
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;//没啥用
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 30;//半死三
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 40;//活三
								}
							}
							else if (personNum == 3)//连四
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 60;//死四
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 200;//活四
								}
							}
							else if (personNum >= 4)//连五
							{
								scoreMap[row][col] += 20000;
							}

							//假设白棋落子，计算得分
							
							emptyNum = 0;//清空空白个数

							for (int i = 1; i <= 4; i++)
							{
								int curRow = row + i * x;
								int curCol = col + i * y;
								if (curRow >= 0 && 
									curRow < size &&
									curCol >= 0 && curCol < size &&
									chess->getChessData(curRow, curCol) == -1)
								{
									aiNum++;
								}
								else if (curRow >= 0 &&
									curRow < size && 
									curCol >= 0 && curCol < size && 
									chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//反向的计算
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row - i * x;
								int curCol= col - i * y;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1)
								{
									aiNum++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//计算白棋得分
							if (aiNum == 0)
								scoreMap[row][col] += 5;
							else if (aiNum == 1)//连二
							{
								scoreMap[row][col] += 10;

							}
							else if (aiNum == 2)
							{
								if (emptyNum == 0)//死三
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)//活三
								{
									scoreMap[row][col] += 25;
								}
								else if (emptyNum == 2)//双头活三
								{
									scoreMap[row][col] += 50;
								}
							}
							else if (aiNum == 3)
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 55;
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 1000;
								}
							}
							else if (aiNum >= 4)
							{
								scoreMap[row][col] += 30000;
							}
						}
					}
				}
			}
		}
	}
}

