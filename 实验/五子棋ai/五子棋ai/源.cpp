#include<iostream>
#include"Chesscontrol.h"

int main()
{
	//c创建对象
	Chessman chessman;
	//Chess chess;
	//Chess chess(15, 13, 21, 54.29);
	Chess chess(15, 32, 32, 52.0);
	

	AI ai;
	

	//创建函数
	Chesscontrol game(&chessman, &ai, &chess);

	
	//引用控制系统的函数
	game.play();
	

	return 0;

}