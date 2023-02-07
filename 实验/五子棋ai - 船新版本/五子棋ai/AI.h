#pragma once
#include"Chess.h"

class AI
{
public:
	void init(Chess *chess);
	void move();
	
	
	//实现对局上各点得分值的计算，思考哪个落点得分最高
	ChessPos consider();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;

private:
	void calculateScore();
	
	
};

