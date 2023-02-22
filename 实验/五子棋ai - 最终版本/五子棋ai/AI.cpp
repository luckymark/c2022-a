#include "AI.h"
#include"chess.h"
#include<windows.h>
int X, Y;//棋子返回值

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
	
	calculateScore1();
	int size;
	size = chess->getGradeSize();
	int maxscore = 0;
	int co[sizee][sizee] = {};
	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++)
		{
			co[i][j] = chess->getChessData(i,j);
		}
	}
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

	int random = rand() % (maxscorepos.size());
	
	int deep = 4;//AI搜索深度
	chesspos maxscoreposs ;
	static int n = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			
			minMax(co, deep, -1, NGIF, PTIF);
			maxscoreposs.x = X;
			maxscoreposs.y = Y;
			return maxscorepos[random];

		}
	}

	
}



void AI::calculateScore1()
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
void AI::calculateScore2()
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
									scoreMap[row][col] += 25;//半死三
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 50;//活三
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
									scoreMap[row][col] += 55;//死四
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 1000;//活四
								}
							}
							else if (personNum >= 4)//连五
							{
								scoreMap[row][col] += 30000;
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
								int curCol = col - i * y;
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
									scoreMap[row][col] += 30;
								}
								else if (emptyNum == 2)//双头活三
								{
									scoreMap[row][col] += 40;
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
									scoreMap[row][col] += 60;
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 200;
								}
							}
							else if (aiNum >= 4)
							{
								scoreMap[row][col] += 2000;
							}
						}
					}
				}
			}
		}
	}

}

//算出整个局面的分数之和，并且向下检视
int AI::score_(int a, int n) {
	if (a == -1) {
		calculateScore1();
	}
	else {
		calculateScore2();
	}
	

	int finalscore = 0;
	for (int i = 0; i < sizee; i++)
	{
		for (int j = 0; j < sizee; j++) {
			finalscore += scoreMap[i][j];
		}
	}
	if (n == 1 && a == 1)//此时是max层
		return finalscore - score_(-1, 2);
	else if (n == 1 && a == -1)//此时是min层
		return finalscore - score_(1, 2);
	else if (n == 2)//结束
		return finalscore;
}

int AI::jdgen(int co[sizee][sizee], int x, int y, int n)
{
	{
		int i, j;
		int sum = 0;
		if (n == 1)
		{
			for (i = x - 1; i < x + 2; i++)
				for (j = y - 1; j < y + 2; j++)
					if ((i > 0 && j > 0 && i < sizee && j < sizee) && (co[i][j] == 1 || co[i][j] == -1))
						sum = 1;
		}
		else
		{
			for (i = x - 2; i < x + 3; i += 2)
				for (j = y - 2; j < y + 3; j += 2)
					if ((i > 0 && j > 0 && i < sizee && j < sizee) && (co[i][j] == 1 || co[i][j] == -1))
						sum = 1;
		}
		return sum;
	}
}

int AI::minMax(int co[sizee][sizee], int deep, int a, int Alpha, int Beta)
//分数传递,a为1表示白棋，为2表示黑棋,调用时Alpha，Beta赋为NGIF,PTIF
{
	int i, j;
	int c[sizee][sizee];
	int minmax;
	int n = 1;
	Tree tree;
	tree.data = NGIF;//负无穷
	tree.Alpha = Alpha;
	tree.Beta = Beta;
	tree.X = 0;
	tree.Y = 0;

	a = -a;//交换黑白子
	if (deep > 0)
	{
		for (i = 0; i < sizee; i++)
			for (j = 0; j < sizee; j++)
			{
				if (co[i][j] == 0 && jdgen(co, i, j, 1) && tree.Alpha < tree.Beta)
				{
					memcpy(c, co, sizeof(int) * 15 * 15);
					c[i][j] = a;
					minmax = minMax(c, deep - 1, a, tree.Alpha, tree.Beta);
					if (deep % 2 == 0)
					{
						if (n == 1)
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Alpha < minmax)
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
					else
					{
						if (n == 1)
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Beta > minmax)
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
				}
			}
		for (i = 0; i < sizee; i++)
			for (j = 0; j < sizee; j++)
			{
				if (co[i][j] == 0 && jdgen(co, i, j, 2) && tree.Alpha < tree.Beta)
				{
					memcpy(c, co, sizeof(int) * 15 *15);
					c[i][j] = a;
					minmax = minMax(c, deep - 1, a, tree.Alpha, tree.Beta);
					if (deep % 2 == 0)
					{
						if (tree.Alpha < minmax)
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
					else
					{
						if (tree.Beta > minmax)
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
				}
			}
		X = tree.X;
		Y = tree.Y;
		return tree.data;
	}
	else
	{
		return score_(a,  1);
	}
}