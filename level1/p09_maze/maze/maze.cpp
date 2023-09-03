#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
int x = 1, y = 1;//人物坐标
int ex = 4, ey = 5;
int map[6][6] = {
   {1,1,1,1,1,1},
   {1,4,4,1,4,1},
   {1,4,1,1,4,1},
   {1,4,4,1,4,1},
   {1,1,4,4,4,6},
   {1,1,1,1,1,1},
};
void setmap() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (map[i][j] == 4) {
				printf(" ");
			}
			if (map[i][j] == 1) {
				printf("*");
			}
			if (map[i][j] == 5) {
				printf("&");
			}
			if (map[i][j] == 6) {
				printf("0");
			}
		}
		printf("\n");
	}
}//生成地图的函数
void move() {
	char ch;
	ch = _getch();
	switch (ch) {
	case 75:
		if ((y - 1) >= 0 && map[x][y - 1] != 1) {
			map[x][y] = 4;
			y -= 1;
		}
		break;
	case 80:
		if ((x + 1) <= 6 && map[x + 1][y] != 1) {
			map[x][y] = 4;
			x += 1;
		}
		break;

	case 77:
		if ((y + 1) <= 6 && map[x][y + 1] != 1) {
			map[x][y] = 4;
			y += 1;
		}
		break;
	case 72:
		if ((x - 1) >= 0 && map[x - 1][y] != 1) {
			map[x][y] = 4;
			x -= 1;
		}
		break;
	}
}
void rw(int x, int y) {
	map[x][y] = 5;
}
int main() {
	//解决闪屏
	HANDLE hOutput;
	COORD coord = { 0,0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	while (1) {
		rw(x, y);
		setmap();
		move();
		//getchar();
		SetConsoleCursorPosition(hOutput, coord);
		if (x == ex && y == ey) {
			system("cls");
			printf("you win");
			break;
		}
	}
	return 0;
}