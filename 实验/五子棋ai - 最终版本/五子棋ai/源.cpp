#include<iostream>
#include"Chesscontrol.h"

int main()
{
	//c��������
	Chessman chessman;
	//Chess chess;
	//Chess chess(15, 13, 21, 54.29);
	Chess chess(15, 24, 24, 39.0);
	

	AI ai;
	

	//��������
	Chesscontrol game(&chessman, &ai, &chess);

	
	//���ÿ���ϵͳ�ĺ���
	game.play();
	

	return 0;

}