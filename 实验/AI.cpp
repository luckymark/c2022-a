#include<cstdio>
#include<cstring>
#include <stdbool.h>
#include "ChessData.h"
#include "AI.h"


void calculateScore(ChessData* chess)
{
	int personNum = 0;           //������������������ж�������
	int aiNum = 0;               //AI�������ж��ٸ�����
	int emptyNum = 0;            //�÷����Ͽհ�λ������
	//��������
	memset(chess->Scoremap, 0, sizeof(chess->Scoremap));

	for (int row = 0; row < BOARD_SIZE; row++)            //������������
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{

			//��ÿ������з������� ����-�¼�֦�㷨�ܲ�����һ������
			if (chess->Chessmap[col][row] == 0)
			{
				for (int x = -1; x <= 1; x++)
				{
					for (int y = -1; y <= 1; y++)
					{
						if (x == 0 && y == 0)              //���ĵ�����
							continue;
						aiNum = 0;
						personNum = 0;
						emptyNum = 0;
						//�������������ط����ӣ������ж��ٸ����壬�Ƿ��пհ�
						for (int i = 1; i <= 4; i++)       //�������ĸ�
						{
							int curRow = row + i * y;      //��ǰλ��
							int curCol = col + i * x;

							if (curRow >= 0 && curRow < BOARD_SIZE &&
								curCol >= 0 && curCol < BOARD_SIZE &&
								chess->Chessmap[curCol][curRow] == 1)
							{
								personNum++;
							}
							//������ϴ�
							else if (curRow >= 0 && curRow < BOARD_SIZE &&
								     curCol >= 0 && curCol < BOARD_SIZE && 
								     chess->Chessmap[curCol][curRow] == 0)
							{
								emptyNum++;
								break;
							}
							else                           //��������
							{
								break;
							}
						}

						//��������жϼ���
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
						
						//����Ļ���
						if (personNum == 1)         //����
						{
							chess->Scoremap[col][row] += 10;
						}
						else if (personNum == 2)
						{
							if (emptyNum == 1)      //����
							{
								chess->Scoremap[col][row] += 30;
							}
							else if (emptyNum == 2) //����
							{
								chess->Scoremap[col][row] += 40;
							}
						}
						else if (personNum == 3)
						{
							if (emptyNum == 1)      //����
							{
								chess->Scoremap[col][row] += 60;
							}
							else if (emptyNum == 2) //����
							{
								chess->Scoremap[col][row] += 200;
							}
						}
						else if (personNum == 4)
						{
							chess->Scoremap[col][row] += 20000;
						}

						//�����������÷�
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
						//����
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

						//����ĵ÷�
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

chessPos think(ChessData* chess)                //�ҵ����ֵ�������ŵ�
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
	int row = pos->row;         //�Զ�����
	int col = pos->col;         //���µ������ӳ���ʼ�ж�
	//ˮƽ����
	for (int i = 0; i < 4; i++)
	{
		if (col - i >= 0 && col - i + 4 < BOARD_SIZE &&             //��������
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 1][row] &&
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 2][row] &&
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 3][row] &&
			chess->Chessmap[col - i][row] == chess->Chessmap[col - i + 4][row]) {
			return true;
		}
	}
	//��ֱ����
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

	// "/" ����
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

	// "\"����
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