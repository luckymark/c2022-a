#pragma once
const float ChessSize = 68;
const int BoardSize = 19;
const int PosSet = ChessSize * 0.4;
const int dy = 44;
const int dx = 43;
struct Chess {
	int ChessMap[BoardSize][BoardSize];//0:ÎÞ   1£ººÚ   -1£º°×
	int ScoreMap[BoardSize][BoardSize];
	int PlayTurn = 1;//1:ºÚÏÂ    -1:°×ÏÂ
};
struct ValueAndPoint {
	int value = 0;
	int row = -1;
	int col = -1;
};
void initpic();

void initchess(struct Chess*);

