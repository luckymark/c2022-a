#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <Windows.h>



int Map[3][10][10] =
{
	{//第一关
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,3,3,4,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,3,0,4,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}, },
	{//第二关
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,1},
	{1,3,3,4,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,3,0,4,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}, },
	{//第三关
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,3,3,4,0,0,0,0,0,1},
	{1,0,0,0,0,3,0,0,0,1},
	{1,4,0,0,0,4,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,3,0,4,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}, }
};

int level = 0;//记录当前关卡，默认为第0关
int maparr[10][10] = { 0 };



void initGame();//初始化游戏

void initMap();//地图加载函数

void drawMap();//绘制函数

void runGame();//更新游戏数据

void moveInmap(int off_x, int off_y);//人物的移动函数

int endGame();//结束函数


int main()
{
	initGame();
    L:initMap();
	while (endGame())
	{
		runGame();

	}
	if (level < 3)
	{
		level++;
		if (level != 3)
			printf("恭喜通过本关，按任意键进入下一关\n");
		goto L;
	}
	printf("游戏胜利\n");
	return 0;
}

void initGame()
{
	printf("\n\n\n    推箱子--按任意键开始");
	_getch();
}

void initMap()
{
	//加载当前关卡地图
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			maparr[i][j] = Map[level][i][j];
		}
	}
}
void drawMap()
{
	system("cls");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (maparr[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("■");
				break;
			case 2:
				printf("♀");
				break;
			case 3:
				printf("●");
				break;
			case 4:
				printf("☆");
				break;
			case 2 + 4:
				printf("♀");
				break;
			case 3 + 4:
				printf("★");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
}
//更新游戏数据
void runGame()
{

	switch (_getch())//输入一个按键，才执行下一个语句
	{
	case 'w':
	case 'W':
		printf("向上\n");
		moveInmap(-1, 0);
		break;
	case 's':
	case 'S':
		printf("向下\n");
		moveInmap(1, 0);
		break;
	case 'a':
	case 'A':
		printf("向左\n");
		moveInmap(0, -1);
		break;
	case 'd':
	case 'D':
		printf("向右\n");
		moveInmap(0, 1);
		break;
	default:
		break;

	}
	drawMap();

}

//人物的移动函数
void moveInmap(int off_x, int off_y)
{
	int playerPos_X = 0;
	int playerPos_Y = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (2 == maparr[i][j] || 2 + 4 == maparr[i][j])
			{
				playerPos_X = i;
				playerPos_Y = j;

			}
		}
	}


	//移动
	if (0 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
		4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])//空地、目标点
	{
		maparr[playerPos_X][playerPos_Y] -= 2;
		maparr[playerPos_X + off_x][playerPos_Y + off_y] += 2;
	}
	else if (3 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
		3 + 4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])//箱子、箱子在点上
	{
		if (0 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] ||
			4 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2])//空地、目标点
		{
			maparr[playerPos_X][playerPos_Y] -= 2;
			//maparr[playerPos_X + 1][playerPos_Y] += 2;
			//maparr[playerPos_X+1][playerPos_Y] -= 3;
			maparr[playerPos_X + off_x][playerPos_Y + off_y] += (2 - 3);
			maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] += 3;
		}
	}
}
//结束函数
int endGame()
{
	//遍历
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (3 == maparr[i][j])
			{
				return 1;
			}
		}
	}
	return 0;

}

//上下左右分别是WSAD
//共有三关
