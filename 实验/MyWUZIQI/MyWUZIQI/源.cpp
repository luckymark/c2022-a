/*
��־22 12 13
������Ŀ�����������Դ 
�����ܣ�����ģ�飨a��





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