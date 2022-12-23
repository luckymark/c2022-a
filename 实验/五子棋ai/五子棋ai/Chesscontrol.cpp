#include "Chesscontrol.h"


Chesscontrol::Chesscontrol(Chessman* chessman, AI* ai, Chess* chess)
{
	this->chessman = chessman;
	this->ai = ai;
	this->chess = chess;

	chessman->init(chess);//初始化判断落子的对象
	ai->init(chess);
}

//开始对局
void Chesscontrol:: play()
{
	//下棋前期盘初始化
	chess->init();
	while (1)
	{

		

		//棋士先走
		chessman->move();
		if (chess->checkOver())
		{
			chess->init();
			continue;
			
		}

		//ai走
		ai->move();
		if (chess->checkOver())
		{
			chess->init();
			continue;

		}

		
	}
}
