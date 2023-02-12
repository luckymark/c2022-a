//Chessdata.h
#pragma once
const int Block_size = 43;//棋子大小
const int Board_width = 17;//落子数目
const int Dim = Block_size * 0.4;//模糊距离

struct ChessData {
	//0:空白  1：黑子  -1：白子
	int chessMap[Board_width][Board_width];
	//AI各个点的落子价值
	int scoreMap[Board_width][Board_width];
	//true:轮到黑方下棋   false：轮到白子下（AI）
	bool playerFlag;
};

typedef struct point {
	int row;
	int  list;
}point_t;

void initChessData(struct ChessData*);