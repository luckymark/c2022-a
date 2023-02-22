#pragma once
#include"Chess.h"
#define sizee 15
#define PTIF 2147483647//������,Beta
#define NGIF -2147483648//������,Alpha
class AI
{
public:
	void init(Chess *chess);
	void move();
	void calculateScore1();
	void calculateScore2();
	//ʵ�ֶԾ��ϸ���÷�ֵ�ļ��㣬˼���ĸ����÷����
	ChessPos consider();

	vector<vector<int>> scoreMap;
	int jdgen(int co[sizee][sizee], int x, int y, int n);
	int score_(int a, int n);
	int minMax(int co[sizee][sizee], int deep, int a, int Alpha, int Beta);//����Сֵ�����Լ�������������֦

private:
	Chess* chess;
	typedef struct
	{
		int data;
		int Alpha;
		int Beta;
		int X;
		int Y;
	}Tree;//������
	

private:
	
	
	
};


