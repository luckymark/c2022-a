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
	//存储当前游戏棋盘和棋子的情况，0表示空白，1表示黑子，-1表示白子,玩家拿黑棋
	int chessMap[BOARD_SIZE][BOARD_SIZE];
	//存储各个点的评分情况，作为AI下棋的依据
	int scoreMap[BOARD_SIZE][BOARD_SIZE];
	//标志下棋方，true表示黑棋方下，false表示白棋方下
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
position AI_GO(ChessData* data);//机器执行下棋
