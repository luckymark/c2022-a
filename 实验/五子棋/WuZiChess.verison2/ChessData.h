#pragma once

const float BLOCK_SIZE = 67.4;
const int BOARD_GRADE_SIZE = 13;
const int POS_OFFSET = BLOCK_SIZE * 0.4;
const int margin_x = 43;
const int margin_y = 42;



struct ChessData {
	//0:�հ� 1������ -1������
	int chessMap[BOARD_GRADE_SIZE][BOARD_GRADE_SIZE];

	//�������"��ֵ����"
	int scoreMap[BOARD_GRADE_SIZE][BOARD_GRADE_SIZE];

	//true:�ڷ� faulse:��������
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
