#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define SIZE 24
#define WALL 0
#define ROUTE 1
#define YOU 2
#define BREAK 15

enum {entranceX=1,entranceY=2};

void swap(int* x, int* y);
void creatMaze(int** maze, int x, int y);
void checkEntrance(int** maze, int x, int y);
void printMaze(int** maze);
void move(int** maze, int x, int y, int destX, int destY);

int main() {

	srand((unsigned)time(NULL));

	int destX = 0, destY = 0;

	int** maze = (int**)malloc(SIZE * sizeof(int*));
	for (int i = 0; i < SIZE; i++) {
		maze[i] = (int*)calloc(SIZE, sizeof(int));
	}
	//让地图最外围为通路，防止挖穿最外层墙
	for (int i = 0; i < SIZE; ++i) {
		maze[i][SIZE - 1] = ROUTE;
		maze[SIZE - 1][i] = ROUTE;
		maze[i][0] = ROUTE;
		maze[0][i] = ROUTE;
	}
	creatMaze(maze, 2 + rand() % (SIZE - 4), 2 + rand() % (SIZE - 4));
	//标定入口、出口
	maze[entranceX][entranceY] = YOU;
	for (int i = SIZE - 3; i >= 0; i--) {
		if (maze[i][SIZE - 3] == ROUTE) {
			maze[i][SIZE - 2] = ROUTE;
			destX = i;
			destY = SIZE - 2;
			break;
		}
	}
	//随机打点，可能会使通路连通
	for (int i = 0; i < BREAK; i++) {
		int a = 2 + rand() % (SIZE - 4);
		int b = 2 + rand() % (SIZE - 4);
		if (maze[a][b] == WALL) {
			maze[a][b] = ROUTE;
		}
		else {
			i--;
		}
	}
	
	checkEntrance(maze,entranceX,entranceY);
	printMaze(maze);

	move(maze, entranceX, entranceY, destX, destY);
	return 0;
}
void swap(int* x, int* y) {
	int t;
	t = *x;
	*x = *y;
	*y = t;
}
void creatMaze(int** maze, int x, int y) {
	if (maze[x][y] == WALL) {
		if (maze[x + 1][y] + maze[x - 1][y] + maze[x][y + 1] + maze[x][y - 1] <= 1) {
			maze[x][y] = ROUTE;
			//洗牌算法，使各个方向的概率是一致的，都是1/4
			int direction[4] = { 0,1,2,3 };
			for (int i = 4; i > 0; --i) {
				int r = rand() % i;
				swap(&direction[r], &direction[i - 1]);

				switch (direction[i - 1]) {
				case 0:
					creatMaze(maze, x - 1, y);
					break;
				case 1:
					creatMaze(maze, x + 1, y);
					break;
				case 2:
					creatMaze(maze, x, y - 1);
					break;
				case 3:
					creatMaze(maze, x, y + 1);
					break;
				default:
					break;
				}
			}
		}
	}
}
void checkEntrance(int** maze, int x, int y) {
	if (maze[x + 1][y] + maze[x - 1][y] + maze[x][y + 1] + maze[x][y - 1] <= 1) {
		maze[x + 1][y] = ROUTE;
		checkEntrance(maze, x + 1, y);
	}
}
void printMaze(int** maze) {
	printf("*****按W、S、A、D以完成移动*****\n");
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (maze[i][j] == ROUTE) {
				printf("  ");
			}
			else if (maze[i][j] == YOU) {
				printf("@@");
			}
			else {
				printf("田");
			}
		}
		printf("\n");
	}
	printf("\n");
}
void move(int** maze, int x, int y, int destX, int destY) {
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//上、下、左、右
	char ch;
	while (1) {
		ch = _getch();
		if (ch == 'w' || ch == 'W') {
			if (maze[x + dir[0][0]][y + dir[0][1]]==ROUTE) {
				maze[x][y] = ROUTE;
				x += dir[0][0];
				y += dir[0][1];
				maze[x][y] = YOU;
				
			}
		}
		else if (ch == 's' || ch == 'S') {
			if (maze[x + dir[1][0]][y + dir[1][1]] == ROUTE) {
				maze[x][y] = ROUTE;
				x += dir[1][0];
				y += dir[1][1];
				maze[x][y] = YOU;
			}
		}
		else if (ch == 'a' || ch == 'A') {
			if (maze[x + dir[2][0]][y + dir[2][1]] == ROUTE) {
				maze[x][y] = ROUTE;
				x += dir[2][0];
				y += dir[2][1];
				maze[x][y] = YOU;
			}
		}
		else if (ch == 'd' || ch == 'D') {
			if (maze[x + dir[3][0]][y + dir[3][1]] == ROUTE) {
				maze[x][y] = ROUTE;
				x += dir[3][0];
				y += dir[3][1];
				maze[x][y] = YOU;
			}
		}
		system("cls");
		printMaze(maze);
		if (x == destX && y == destY) {
			printf("你已经成功到达终点！\n");
			break;
		}
	}
}