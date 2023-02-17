#pragma once
const float ChessSize = 68;
const int BoardSize = 19;
const int PosSet = ChessSize * 0.4;
const int dy = 44;
const int dx = 43;
struct Chess {
	int ChessMap[BoardSize][BoardSize];//0:��   1����   -1����
	int ScoreMap[BoardSize][BoardSize];
	int PlayTurn = 1;//1:����    -1:����
};
struct ValueAndPoint {
	int value = 0;
	int row = -1;
	int col = -1;
};
void initpic();

void initchess(struct Chess*);

