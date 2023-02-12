#pragma once

const float BLOCK_SIZE = 67.4;
const int BOARD_GRADE_SIZE = 13;
const int POS_OFFSET = BLOCK_SIZE * 0.4;
const int margin_x = 43;
const int margin_y = 42;



struct ChessData {
	//0:空白 1：白子 -1：黑子
	int chessMap[BOARD_GRADE_SIZE][BOARD_GRADE_SIZE];

	//各个点的"价值评分"
	int scoreMap[BOARD_GRADE_SIZE][BOARD_GRADE_SIZE];

	//true:黑方 faulse:白棋下棋
	bool playerFlag;

};

void initChessData(struct ChessData*);
void calculateScore(ChessData* data);

typedef struct point {
	int row;
	int col;
}point_t;

point_t actionByAI(ChessData* data);

bool checkWin(ChessData* game, int row, int col);
