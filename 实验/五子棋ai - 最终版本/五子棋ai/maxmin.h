#pragma once
#include<math.h>
#include<string.h>
#include <corecrt_malloc.h>
#include"Chess.h"



#define PTIF 2147483647//正无穷,Beta
#define NGIF -2147483648//负无穷,Alpha


int X1, Y1;
#define size  15//=getgradesize()
class maxmin
{
public:
	int score_(int a, int n);
	void init(Chess* chess);
	int chessmap[size][size];
private:
	Chess* chess;
	
};