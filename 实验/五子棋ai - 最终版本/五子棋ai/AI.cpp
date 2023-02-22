#include "AI.h"
#include"chess.h"
#include<windows.h>
int X, Y;//���ӷ���ֵ

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
	
	int deep = 4;//AI�������
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
	int personNum;// (�����м���������һ��
	int aiNum;
	int emptyNum = 0;//�÷����м����հ�
	for (int i = 0; i < scoreMap.size(); i++)//�����������
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}
	scoreMap[7][7] = 1;
	int size = chess->getGradeSize();//��ȡ���̴�С
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			//����ÿ�����ļ�ֵ
			if (chess->getChessData(row, col) == 0)
			{
				for (int y = -1; y <= 0; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						//����
						personNum = 0;
						aiNum = 0;
						emptyNum = 0;

						if ((!(y == 0 && x == 0))
							&& (!(y == 0 && x == 1)))
						{
							//������壨���֣��ڸ�λ������
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

							//����ļ���
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

							//����������ӵ÷�
							if (personNum == 1)//����
							{
								scoreMap[row][col] += 10;

							}
							else if (personNum == 2)//����
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;//ûɶ��
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 30;//������
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 40;//����
								}
							}
							else if (personNum == 3)//����
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 60;//����
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 200;//����
								}
							}
							else if (personNum >= 4)//����
							{
								scoreMap[row][col] += 20000;
							}

							//����������ӣ�����÷�
							
							emptyNum = 0;//��տհ׸���

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

							//����ļ���
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

							//�������÷�
							if (aiNum == 0)
								scoreMap[row][col] += 5;
							else if (aiNum == 1)//����
							{
								scoreMap[row][col] += 10;

							}
							else if (aiNum == 2)
							{
								if (emptyNum == 0)//����
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)//����
								{
									scoreMap[row][col] += 25;
								}
								else if (emptyNum == 2)//˫ͷ����
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
	int personNum;// (�����м���������һ��
	int aiNum;
	int emptyNum = 0;//�÷����м����հ�
	for (int i = 0; i < scoreMap.size(); i++)//�����������
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}
	scoreMap[7][7] = 1;
	int size = chess->getGradeSize();//��ȡ���̴�С
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			//����ÿ�����ļ�ֵ
			if (chess->getChessData(row, col) == 0)
			{
				for (int y = -1; y <= 0; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						//����
						personNum = 0;
						aiNum = 0;
						emptyNum = 0;

						if ((!(y == 0 && x == 0))
							&& (!(y == 0 && x == 1)))
						{
							//������壨���֣��ڸ�λ������
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

							//����ļ���
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

							//����������ӵ÷�
							if (personNum == 1)//����
							{
								scoreMap[row][col] += 10;

							}
							else if (personNum == 2)//����
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;//ûɶ��
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 25;//������
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 50;//����
								}
							}
							else if (personNum == 3)//����
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 55;//����
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 1000;//����
								}
							}
							else if (personNum >= 4)//����
							{
								scoreMap[row][col] += 30000;
							}

							//����������ӣ�����÷�

							emptyNum = 0;//��տհ׸���

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

							//����ļ���
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

							//�������÷�
							if (aiNum == 0)
								scoreMap[row][col] += 5;
							else if (aiNum == 1)//����
							{
								scoreMap[row][col] += 10;

							}
							else if (aiNum == 2)
							{
								if (emptyNum == 0)//����
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)//����
								{
									scoreMap[row][col] += 30;
								}
								else if (emptyNum == 2)//˫ͷ����
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

//�����������ķ���֮�ͣ��������¼���
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
	if (n == 1 && a == 1)//��ʱ��max��
		return finalscore - score_(-1, 2);
	else if (n == 1 && a == -1)//��ʱ��min��
		return finalscore - score_(1, 2);
	else if (n == 2)//����
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
//��������,aΪ1��ʾ���壬Ϊ2��ʾ����,����ʱAlpha��Beta��ΪNGIF,PTIF
{
	int i, j;
	int c[sizee][sizee];
	int minmax;
	int n = 1;
	Tree tree;
	tree.data = NGIF;//������
	tree.Alpha = Alpha;
	tree.Beta = Beta;
	tree.X = 0;
	tree.Y = 0;

	a = -a;//�����ڰ���
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