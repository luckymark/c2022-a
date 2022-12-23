#pragma once
#include"Chessman.h"
#include"AI.h"
#include"Chesscontrol.h"
#include"Chess.h"


class Chesscontrol
{
public:
	Chesscontrol(Chessman* man, AI* ai, Chess* chess);
	void play();//开始对局

	//t添加数据成员
private:
	Chessman * chessman;
	Chesscontrol * chesscontrol;
	AI * ai;
	Chess * chess;

};

