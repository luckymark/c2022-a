/*
日志22 12 13
建立项目，导入待定资源 
分配框架，建立模块（a）





*/
#include<iostream>
#include"Chessgame.h"

int main(void) {
	Man man;
	Chess chess(13, 44, 43, 67.4);
	AI ai;
	Chessgame game(&man,&ai,&chess); 

	game.play();

	return 0;




}