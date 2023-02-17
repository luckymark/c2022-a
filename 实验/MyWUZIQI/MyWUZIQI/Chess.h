#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//落子位置
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};
//棋子种类
typedef enum {
	CHESS_WHITE = -1,
     CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	bool checkWin();
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();
	bool clickBoard(int x, int y,ChessPos* pos);
	void chessDown(ChessPos* pos, chess_kind_t kind);
	int getGradeSize();//获取棋盘大小（13.15.19格）
	int getChessData(int row, int col);

	bool checkOver();//胜负设计

private:
	IMAGE chessBlackImg;//小黑子
	IMAGE chessWhiteImg;//小白子

	int gradeSize;//获取棋盘大小（13.15.19格）
	int margin_x; //棋盘左边界
	int margin_y; //棋盘上边界
	float chessSize;//棋子大小
	//储存棋子分布 0-无 1-黑 -1-白 
	//chessMap[3][5]表示三行五列的落子,用于存储数据！！！！！！！
	vector<vector<int>>chessMap;

	//现在该谁落子
	bool playerFlag;//true-黑走 false-白走

	void updateGameMap(ChessPos* pos);

	ChessPos lastPos; //最近落子位置
};




