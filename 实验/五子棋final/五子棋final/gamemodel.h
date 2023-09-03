#pragma once
#include<vector>
 enum chessKind
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
};
const int leftBoard = 44;
const int topBoard = 43;
const int BOARD_SIZE = 15;
const int MARGIN = 49;
const float BLOCK_SIZE = 67.4;
const int VAGUE_DISTANCE = BLOCK_SIZE * 0.4;
const int AI_THINK_TIME = 700;
typedef struct
{
	//�洢��ǰ��Ϸ���̺����ӵ������0��ʾ�հף�1��ʾ���ӣ�-1��ʾ����,����ú���
	int chessMap[BOARD_SIZE][BOARD_SIZE];
	//�洢������������������ΪAI���������
	int scoreMap[BOARD_SIZE][BOARD_SIZE];
	//��־���巽��true��ʾ���巽�£�false��ʾ���巽��
	bool playerSign;
}ChessData;
typedef struct point
{
	int row;
	int col;
}position;
void initChessData(ChessData*);
void updateGameMap(ChessData*data, int row, int col);
bool checkWin(ChessData* game, int row, int col);
void calculateScore(ChessData* data);
position AI_GO(ChessData* data);//����ִ������
