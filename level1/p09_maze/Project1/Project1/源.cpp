#include <stdio.h>
#include <stdlib.h>

void startUp();
void gameInstructions();
void menu(char c);
void gameMap();

char map[6][6] = { "######",
				"#o #  ",
				"# ## #",
				"#  # #",
				"##   #",
				"######"
};


int main() {
	startUp();//游戏启动界面

	gameInstructions();//游戏说明 

	//显示菜单 
	printf("   ->  开始游戏\n");
	printf("       退出游戏\n");
	printf("按Enter进入游戏\n");
	char choose1;
	choose1 = getch();
	menu(choose1);

	//加载游戏地图
	gameMap();

	//玩家进行操作
	system("cls");
	int i, x, y, p, q, j;
	char ch;

	x = 1; y = 1; p = 1; q = 5;
	for (i = 0; i < 6; ++i) {
		printf("        ");
		for (j = 0; j < 6; ++j) {
			printf("%c  ", map[i][j]);
		}
		printf("\n");
	}
	while (x != p || y != q) {
		ch = getch();

		if (ch == 's' || ch == 'S') {
			if (map[x + 1][y] != '#') {
				map[x][y] = ' ';
				x++;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		if (ch == 'w' || ch == 'W') {
			if (map[x - 1][y] != '#') {
				map[x][y] = ' ';
				x--;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		if (ch == 'a' || ch == 'A') {
			if (map[x][y - 1] != '#') {
				map[x][y] = ' ';
				y--;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		if (ch == 'd' || ch == 'D') {
			if (map[x][y + 1] != '#') {
				map[x][y] = ' ';
				y++;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		system("cls");
		for (i = 0; i < 6; ++i) {
			printf("        ");
			for (j = 0; j < 6; ++j) {
				printf("%c  ", map[i][j]);
			}
			printf("\n");
		}
	}
	system("cls");
	printf("You Win!\n");
	Sleep(3000);
	return 0;
}

void startUp() {
	int i;
	int circle = 2;
	for (i = 0; i < circle; ++i) {
		system("cls");
		printf("        游戏正在加载");
		Sleep(500);
		system("cls");
		printf("        游戏正在加载.");
		Sleep(500);
		system("cls");
		printf("        游戏正在加载..");
		Sleep(500);
		system("cls");
		printf("        游戏正在加载...");
		Sleep(500);
	}
	system("cls");
	printf("        游戏加载完毕！\n");
	Sleep(1000);
}

void gameInstructions() {
	printf("<---操作按键：[W][S][A][D]--->\n");
	printf("<---分别对应[上][下][左][右]--->\n");
	printf("<---注意使用英文输入法--->\n");
	Sleep(1000);
}

void menu(char c) {
	system("cls");
	if (c == 'S' || c == 's') {
		printf("        游戏加载完毕！\n");
		printf("<---操作按键：[W][S][A][D]--->\n");
		printf("<---分别对应[上][下][左][右]--->\n");
		printf("       开始游戏\n");
		printf("   ->  退出游戏\n");
		printf("程序将在5s后关闭\n");
		int i = 0;
		for (i = 0; i < 5; ++i) {
			system("cls");
			printf("程序将在 %ds后关闭\n", 5 - i);
			Sleep(1000);
		}
		exit(0);//退出程序 
	}
	else {
		printf("        游戏加载完毕！\n");
		printf("<---操作按键：[W][S][A][D]--->\n");
		printf("<---分别对应[上][下][左][右]--->\n");
		printf("   ->  开始游戏\n");
		printf("       退出游戏\n");
		printf("按Enter进入游戏\n");

	}
}

void gameMap() {
	system("cls");
	printf("---正在加载游戏地图---\n");

	int i, j;
	for (i = 0; i < 6; ++i) {
		printf("        ");
		for (j = 0; j < 6; ++j) {
			printf("%c  ", map[i][j]);
			Sleep(100);
		}
		printf("\n");
		Sleep(200);
	}

	system("cls");
	printf("---Part1---\n");
	for (i = 0; i < 6; ++i) {
		printf("        ");
		for (j = 0; j < 6; ++j) {
			printf("%c  ", map[i][j]);
		}
		printf("\n");
	}
}

