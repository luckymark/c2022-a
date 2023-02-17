#include "Chessgame.h"
Chessgame::Chessgame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;


	man->init(chess);  //初始化棋手
	ai->init(chess);
}
	//对局开始
void Chessgame::play()
{
	chess->init();
	while (1)
	{//棋手先手
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;

		}
		//AI latter
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;


		}
	}
}