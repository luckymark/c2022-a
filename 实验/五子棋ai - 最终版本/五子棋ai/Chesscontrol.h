#pragma once
#include"Chessman.h"
#include"AI.h"
#include"Chesscontrol.h"
#include"Chess.h"


class Chesscontrol
{
public:
	Chesscontrol(Chessman* man, AI* ai, Chess* chess);
	void play();//��ʼ�Ծ�

	//t������ݳ�Ա
private:
	Chessman * chessman;
	Chesscontrol * chesscontrol;
	AI * ai;
	Chess * chess;

};

