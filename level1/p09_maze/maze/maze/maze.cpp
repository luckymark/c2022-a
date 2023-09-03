/*题目：迷宫小游戏（基于console）
功能要求：
1. 在控制台上显示一个迷宫，包括：墙、玩家、出口等；
1. 通过上下左右键，控制玩家行走；
1. 当玩家到达出口，则显示玩家赢得了游戏；*/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
//玩家的当前坐标
void setMaze(int* p, int ROL);
void move(char c, int* p, int ROL, int *playerPosition, int moveX, int moveY);
int main() {
	const int ROL = 20;
	initial:
	//0是可以走，1是阻挡，2是玩家位置，3是初始位置，-1是出口
	int controlnum[ROL][ROL] = { 
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1},
		{1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,0,1},//row 5
		{1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,0,0,1,0,1},
		{1,0,1,0,1,0,0,0,0,0,0,1,1,0,1,1,1,1,0,1},
		{1,0,1,0,1,0,1,1,1,1,1,1,0,0,1,1,1,1,0,1},
		{1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},//row 10
		{1,0,1,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1},
		{1,0,1,0,0,0,0,0,2,1,0,1,0,1,1,0,0,0,0,1},
		{1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,1,0,1},
		{1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1},//row 15
		{1,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1},
		{1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,1,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1},
		{1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1}//row 20
	};
	const int outPosition = (ROL-1)*ROL+15;
	const int initialPlayerPosition = (13-1)*ROL+8;
	int playerPosition = initialPlayerPosition;
	char c;
	setMaze(&controlnum[0][0],ROL);
	printf("wasd移动，r重置");
	do {
		c = _getch();
		switch (c) {
		case 'w':
			move(c, &controlnum[0][0], ROL, &playerPosition, 0, -1);
			break;
		case 'a':
			move(c, &controlnum[0][0], ROL, &playerPosition, -1, 0);
			break;
		case 's':
			move(c, &controlnum[0][0], ROL, &playerPosition, 0, 1);
			break;
		case 'd':
			move(c, &controlnum[0][0], ROL, &playerPosition, 1, 0);
			break;
		case 'r':
			goto initial;
			break;
		}
	} while (playerPosition!=outPosition);
	
	printf("you win");
	return 0;
}
//按下任何键盘之前等待，用getchar
//在碰到边界的时候要走不动

void setMaze(int *p,int ROL) {
	//每次重新打印一次地图
	system("cls");
	for (int i = 0; i < ROL;++i) {
		for (int j = 0; j < ROL;++j) {
			switch (*(p + i * ROL + j)) {
			case 1:
				printf(" *");
				break;
			case 0:
				printf("  ");
				break;
			case 2:
				printf(" p");
				break;
			case 3:
				printf(" o");
				break;
			}		
		}
		printf("\n");
	}	
}
void move(char c,int *p,int ROL,int *playerPosition,int moveX,int moveY) {
	if ((*(p+((*playerPosition / ROL) + moveY)*ROL+(*playerPosition % ROL) + moveX) ==0)|| (*(p + ((*playerPosition / ROL) + moveY) * ROL + (*playerPosition % ROL) + moveX) == 3)) {
		*(p + (*playerPosition / ROL)  * ROL + (*playerPosition % ROL) )=0;
		*(p + ((*playerPosition / ROL) + moveY) * ROL + (*playerPosition % ROL) + moveX )=2;
		*playerPosition = ((*playerPosition / ROL) + moveY) * ROL + (*playerPosition % ROL) + moveX;
		setMaze(p,  ROL);
	}
	else {
		setMaze(p,  ROL);
		printf("you cannot move\n");
	}
}