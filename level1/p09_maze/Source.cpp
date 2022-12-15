#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<time.h>
#define HEIGHT 7
#define WEIGHT 7

FILE* map;
char maze[HEIGHT][WEIGHT];
int player[2] = { 1,1 };
int end[2] = { 5,5 };


void init() {
	char ch;
	map = fopen("map1.txt", "r");
	int i, j;
	i = j = 0;
	while (!feof(map)) {
		ch = fgetc(map);
		if (ch != '\n') {
			maze[i][j] = ch;
			if (j == WEIGHT - 1) {
				j = 0;
				i += 1;
			}
			else j += 1;
		}
	}
	maze[end[0]][end[1]] = 'G';
	maze[player[0]][player[1]] = 'P';
	fclose(map);
}

void draw() {
	system("cls");
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WEIGHT; j++) {
			printf("%2c", maze[i][j]);
		}
		printf("\n");
	}
}

void move(int i, int j) {
	int ch;
	while (1) {
		if (_kbhit) {
			ch = _getch();
			break;
		}
	}
	switch (ch)
	{
	case 72://up
		if (maze[i - 1][j] == '0' || maze[i - 1][j] == 'G') {
			maze[i - 1][j] = 'P';
			maze[i][j] = '0';
			player[0] = i - 1;
		}
		break;
	case 75://left
		if (maze[i][j-1] == '0' || maze[i][j - 1] == 'G') {
			maze[i][j-1] = 'P';
			maze[i][j] = '0';
			player[1] = j - 1;
			}
		break;
	case 77://right
		if (maze[i][j+1] == '0'|| maze[i][j + 1] == 'G') {
			maze[i][j+1] = 'P';
			maze[i][j] = '0';
			player[1] = j + 1;
		}
		break;
	case 80://down
		if (maze[i + 1][j] == '0' || maze[i + 1][j] == 'G') {
			maze[i + 1][j] = 'P';
			maze[i][j] = '0';
			player[0] = i + 1;
		}
		break;
	default:
		move(i, j);
		break;
	}
}

int finish() {
	int res = 0;
	if (player[0] == end[0] && player[1] == end[1])
		res = 1;
	return res;
}

void play() {
	init();
	draw();
	while (!finish()) {
		move(player[0], player[1]);
		draw();
	}
}

int main() {
	play();
	return 0;
}