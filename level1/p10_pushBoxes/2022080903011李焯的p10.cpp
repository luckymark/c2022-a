#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

int screen[9][11];
int  x= 4;
int y = 5;
int cum();
void printMap();
bool isWin();
bool isLose();
int getMap(FILE* fp,int level);
typedef void (*fp)();     //增强以返回值为函数指针的函数的可读性，typedef函数指针；
void movew();
void moves();
void movea();
void moved();
fp move(char ch);

void Beg()
{
	system("cls");
	printf("开始游戏请按1\n退出游戏随便你\n");
}

int main() {
	int level = 1;
	int steps = 0;
	char ch,begin,end;
	Beg();
	begin = _getch();
	if (begin == '1') 
	{
		printf("请用wsad/WSAD代表上下左右来进行游戏\n");
		while (1) 
		{
			system("cls");
			FILE* fp = NULL;
			getMap(fp, level);
			printMap();
			ch = _getch();
			void (*p)();
			p = move(ch);
			p();
			steps++;
			if (isLose())
			{
				system("cls");
				printMap();
				printf("游戏失败");
				return 0;
			}
			if (isWin())		
			{
				if (level == 3) {
					printf("恭喜你通过了游戏!");
					FILE* fpp;
					fpp = fopen("result", "w");
					fprintf(fpp, "%d", steps);
					fclose(fpp);
					return 0;
				}
				level++;

			}
		}
	}
	else
		return 0;
}
void movew() {
	if (x > 0) {
		if (screen[x - 1][y] == 1) {
			return;/*如果箱子的上面是墙，则地图不会发生变化，因为
			推不动嘛*/
		}
		else if (screen[x - 1][y] == 0) {
			screen[x - 1][y] += 3;
			screen[x][y] -= 3;
			x--;/*如果前面是空地，则需要向前移动一格，也就是原先人的位置
			变成空地，前方的空地变成人，空地（0）变成人（3）需要加3，
			人变成空地需要减3*/
		}
		else if (screen[x - 1][y] == 4) {
			screen[x - 1][y] += 3;
			screen[x][y] -= 3;
			x--;
		}//一样的
		else if (screen[x - 1][y] == 2 || screen[x - 1][y] == 6) {
			if (screen[x - 2][y] == 0) {
				screen[x - 2][y] += 2;//箱子前面的格变成箱子（2）
				screen[x - 1][y] += 1;//箱子的位置变成人（3）
				screen[x][y] -= 3;/*如果前面是空地，则需要向前移动
				一格，也就是原先是箱子的格子变成人，人的位置变成空
				地，原先的空地变成箱子,箱子（2）变成人（3）需要减
				3，空地变成人*/
				x--;
			}
			else if (screen[x - 2][y] == 1) {
				return;
			}
			else if (screen[x - 2][y] == 2) {
				return;//如果箱子的前面是墙或者其他的箱子，则箱子推不动
			}
			else if (screen[x - 2][y] == 4) {
				screen[x - 2][y] += 2;
				screen[x - 1][y] += 1;
				screen[x][y] -= 3;
				x--;
			}//这个情况别漏了
		}
	}
}
void moves() {
	if (x < 9) {
		if (screen[x + 1][y] == 1) {
			return;
		}
		else if (screen[x + 1][y] == 0) {
			screen[x + 1][y] += 3;
			screen[x][y] -= 3;
			x++;
		}
		else if (screen[x + 1][y] == 4) {
			screen[x + 1][y] += 3;
			screen[x][y] -= 3;
			x++;
		}
		else if (screen[x + 1][y] == 2 || screen[x + 1][y] == 6) {
			if (screen[x + 2][y] == 1) {
				return;
			}
			else if (screen[x + 2][y] == 0) {
				screen[x + 2][y] += 2;
				screen[x + 1][y] += 1;
				screen[x][y] -= 3;
				x++;
			}
			else if (screen[x + 2][y] == 2) {
				return;
			}
			else if (screen[x + 2][y] == 4) {
				screen[x + 2][y] += 2;
				screen[x + 1][y] += 1;
				screen[x][y] -= 3;
				x++;
			}
		}
	}
}
void movea() {
	if (y > 0) {
		if (screen[x][y - 1] == 1) {
			return;
		}
		else if (screen[x][y - 1] == 4) {
			screen[x][y - 1] += 3;
			screen[x][y] -= 3;
			y--;
		}
		else if (screen[x][y - 1] == 0) {
			screen[x][y - 1] += 3;
			screen[x][y] -= 3;
			y--;
		}
		else if (screen[x][y - 1] == 2 || screen[x][y - 1] == 6) {
			if (screen[x][y - 2] == 0) {
				screen[x][y - 2] += 2;
				screen[x][y - 1] += 1;
				screen[x][y] -= 3;
				y--;
			}
			else if (screen[x][y - 2] == 1) {
				return;
			}
			else if (screen[x][y - 2] == 2) {
				return;
			}
			else if (screen[x][y - 2] = 4) {
				screen[x][y - 2] += 2;
				screen[x][y - 1] += 1;
				screen[x][y] -= 3;
				y--;
			}
		}
	}
}
void moved() {
	if (y < 9) {
		if (screen[x][y + 1] == 1) {
			return;
		}
		else if (screen[x][y + 1] == 4) {
			screen[x][y + 1] += 3;
			screen[x][y] -= 3;
			y++;
		}
		else if (screen[x][y + 1] == 0) {
			screen[x][y + 1] += 3;
			screen[x][y] -= 3;
			y++;
		}
		else
			if (screen[x][y + 1] == 2 || screen[x][y + 1] == 6) {
				if (screen[x][y + 2] == 0) {
					screen[x][y + 2] += 2;
					screen[x][y + 1] += 1;
					screen[x][y] -= 3;
					y++;
				}
				else if (screen[x][y + 2] == 4) {
					screen[x][y + 2] += 2;
					screen[x][y + 1] += 1;
					screen[x][y] -= 3;
					y++;
				}
				else if (screen[x][y + 2] == 2) {
					return;
				}
				else if (screen[x][y + 2] == 1) {
					return;
				}
			}

	}
}
fp move(char ch)
{
	switch (ch)
	{
	case 'W':
	case'w':
		return movew;
	case 'S':
	case's':
		return moves;
	case 'A':
	case'a':
		return movea;
	case 'D':
	case'd':
		return moved;
	default:
		break;
	}
}
void printMap() {
	int i, j;
	printf("请用wsad代表上下左右来进行游戏\n");
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			switch (screen[i][j]) {
			case 0:
				printf("  ");//空 
				break;
			case 1:
				printf("■");//墙 
				break;
			case 2:
				printf("★");//箱子 
				break;
			case 3:
				printf("♀");//人 
				break;
			case 4:
				printf("○");//终点 
				break;
			case 6:
				printf("★");//箱子和终点
				break;
			case 7:
				printf("♀");//终点显示人
				break;
			}
		}
		printf("\n");
	}
}
int cum() {
	int i, j, dterminal = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			if (screen[i][j] == 2) {
				dterminal++;
			}
		}
	}
	return dterminal;
} // 计算终点个数
bool isLose() {
	int i, j;
	int k = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			if (i > 0 && j > 0) {
				if (screen[i][j] == 2 || screen[i][j] == 6) {
					if (((screen[i - 1][j] == 1 || screen[i - 1][j] == 2 || screen[i - 1][j] == 6) && (screen[i][j - 1] == 1 || screen[i][j - 1] == 2 || screen[i][j - 1] == 6))
						|| ((screen[i][j - 1] == 1 || screen[i][j - 1] == 2 || screen[i][j - 1] == 6) && (screen[i + 1][j] == 1 || screen[i + 1][j] == 2 || screen[i + 1][j] == 6))
						|| ((screen[i + 1][j] == 1 || screen[i + 1][j] == 2 || screen[i + 1][j] == 6) && (screen[i][j + 1] == 1 || screen[i][j + 1] == 2 || screen[i][j + 1] == 6))
						|| ((screen[i][j + 1] == 1 || screen[i][j + 1] == 2 || screen[i][j + 1] == 6) && (screen[i - 1][j] == 1 || screen[i - 1][j] == 2 || screen[i - 1][j] == 6))) {
						k++;
					}
				} //看看还能不能再进行游戏了；
			}
		}
	}
	if (k ==cum()) {
		return true;
	}
	else
		return false;
}
bool isWin() {
	int i, j, k = 0;
	int t = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			if (screen[i][j] == 6) {
				k++;
			}
		}
	}
	if (k == cum()) {
		return true;
	}
	else
		return false;
} 
int getMap(FILE* fp ,int level)
{
	
	switch (level)
	{
	case 1:
		fp = fopen("map1.txt", "r");
		break;
	case 2:
		fp= fopen("map2.txt", "r");
		break;
	case 3:
		fp = fopen("map3.txt", "r");
		break;
	default:
		break;
	}
	if (fp == NULL) {
			printf("open error/n");
			return -1;
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 11; j++) {
				fscanf(fp, "%d", screen[i][j]);
			}
		}
	fclose(fp);
	return 0;
}


