#pragma once
#include"Chess.h"
#define sizee 15
#define PTIF 2147483647//正无穷,Beta
#define NGIF -2147483648//负无穷,Alpha
class AI
{
public:
	void init(Chess *chess);
	void move();
	void calculateScore1();
	void calculateScore2();
	//实现对局上各点得分值的计算，思考哪个落点得分最高
	ChessPos consider();

	vector<vector<int>> scoreMap;
	int jdgen(int co[sizee][sizee], int x, int y, int n);
	int score_(int a, int n);
	int minMax(int co[sizee][sizee], int deep, int a, int Alpha, int Beta);//极大极小值搜索以及阿尔法贝塔剪枝

private:
	Chess* chess;
	typedef struct
	{
		int data;
		int Alpha;
		int Beta;
		int X;
		int Y;
	}Tree;//搜索树
	

private:
	
	
	
};


