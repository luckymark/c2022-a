#pragma once
const float size = 67.4;
const int boardsize = 13;
const int threshold = size * 0.4;
typedef enum {
	White = -1,
	Black = 1
}Kind;

struct ChessData {
	int chessmap[boardsize][boardsize];
	int chesspoint[boardsize][boardsize];
	bool sideflag;
};
void initChessData(ChessData*);
void newChessmap(ChessData* data, int row, int col);
void value(ChessData* data);

typedef struct point {
	int row;
	int col;
}Cpoint;
Cpoint move(ChessData* data);
bool Win(ChessData* game, int row, int col);
