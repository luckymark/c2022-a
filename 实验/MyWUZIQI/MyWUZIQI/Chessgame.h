#pragma once
#include"Man.h"
#include"AI.h"
#include"Chess.h"
class Chessgame
{
public:
	Chessgame(Man* man, AI* ai, Chess* chess);
	void play();//开始对局

//添加数据成员
private:
	Man* man;
	AI* ai;
	Chess* chess;

    


};

