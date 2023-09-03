#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<time.h>
#define HEIGHT 11
#define WEIGHT 14
#define PLAYER 'P'
#define BOX 'B'
#define GOAL 'G'
#define FLOOR '0'
#define WALL '1'
#define MAXSCORE 150

int m;
int finish();
int main();
#define M m-1
FILE* map;
FILE* score_record;
char maze[HEIGHT][WEIGHT];
int player[2];
int box[2][2] = { {2,5},{2,4} };
int b[2];
int end[2][2] = { { 6,1} ,{9,10} };
char last = FLOOR;
char b_last = FLOOR; 
int walk;

int ifNull(int i, int j) {
	if (maze[i][j] == FLOOR || maze[i][j] == GOAL) return 1;
	return 0;
}

void init() {
	char ch;
	walk = 0;
	player[0] = player[1] = 1;
	b[0] = box[M][0];
	b[1] = box[M][1];
	if (m == 1) map = fopen("map1.txt", "r");
	if (m == 2) map = fopen("map2.txt", "r");
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
	maze[end[M][0]][end[M][1]] = GOAL;
	maze[player[0]][player[1]] = PLAYER;
	maze[box[M][0]][box[M][1]] = BOX;
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
	if (!finish())printf("\nPress r to restart\n");
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
		if (ifNull(i-1,j)) {
			maze[i][j] = last;
			last = maze[i - 1][j];
			maze[i - 1][j] = PLAYER;
			player[0] = i - 1;
			walk += 1;
		}
		if (maze[i-1][j] == BOX && i - 2 > 0) {
			if (ifNull(i-2, j)) {
				maze[i][j] = last;
				last = b_last;
				b_last = maze[i-2][j];
				maze[i-1][j] = PLAYER;
				maze[i-2][j] = BOX;
				player[0] = i - 1;
				b[0] -= 1;
				walk += 1;
			}
		}
		break;
	case 75://left
		if (ifNull(i,j - 1)) {
			maze[i][j] = last;
			last = maze[i][j - 1];
			maze[i][j - 1] = PLAYER;
			player[1] = j - 1;
			walk += 1;
		}
		if (maze[i][j - 1] == BOX && j - 2 >0) {
			if (ifNull(i, j - 2)) {
				maze[i][j] = last;
				last = b_last;
				b_last = maze[i][j - 2];
				maze[i][j - 1] = PLAYER;
				maze[i][j - 2] = BOX;
				player[1] = j - 1;
				b[1] -= 1;
				walk += 1;
			}
		}
		break;
	case 77://right
		if (ifNull(i,j+1)) {
			maze[i][j] = last;
			last = maze[i][j + 1];
			maze[i][j + 1] = PLAYER;
			player[1] = j + 1;
			walk += 1;
		}if (maze[i][j + 1] == BOX && j + 2 < WEIGHT) {
			if (ifNull(i, j + 2)) {
				maze[i][j] = last;
				last = b_last;
				b_last = maze[i][j + 2];
				maze[i][j + 1] = PLAYER;
				maze[i][j + 2] = BOX;
				player[1] = j + 1;
				b[1] += 1;
				walk += 1;
			}
		}
		break;
	case 80://down
		if (ifNull(i+1,j)) {
			maze[i][j] = last;
			last = maze[i + 1][j];
			maze[i + 1][j] = PLAYER;
			player[0] = i + 1;
			walk += 1;
		}
		if (maze[i+1][j] == BOX && i+2 < HEIGHT) {
			if (ifNull(i+2, j)) {
				maze[i][j] = last;
				last = b_last;
				b_last = maze[i+2][j];
				maze[i+1][j] = PLAYER;
				maze[i+2][j] = BOX;
				player[0] = i+1;
				b[0] += 1;
				walk += 1;
			}
		}
		break;
	case 114:
		init();
		draw();
		break;
	default:
		move(i, j);
		break;
	}
}

int finish() {
	int res = 0;
	if (b[0] == end[M][0] && b[1] == end[M][1])
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
	draw();
	int score = MAXSCORE - walk;
	char top[10];
	printf("\nyou win!\n");
	if (m == 1) score_record = fopen("score_m1.txt", "r");
	if (m == 2) score_record = fopen("score_m2.txt", "r");
	int max_score[5],n_max_score[6],num;
	for (int i = 0; i < 5; i++) {
		fscanf(score_record, "%s %d",&top, &max_score[i]);
	}
	fclose(score_record);
	num = 0;
	int open = 0;
	if (m == 1) score_record = fopen("score_m1.txt", "w");
	if (m == 2) score_record = fopen("score_m2.txt", "w");
	for (int i = 0; i < 5; i++) {
		if (max_score[i] <= score && open == 0) {
			n_max_score[num] = score;
			n_max_score[num + 1] = max_score[i];
			num ++;
			open = 1;
		}
		else n_max_score[num] = max_score[i];
		num++;
	}
	for (int i = 0; i < 5; i++) {
		fprintf(score_record, "%d %3d\n", i + 1, n_max_score[i]);
		printf("%d %3d\n", i + 1, n_max_score[i]);
	}
	fclose(score_record);
}

int main() {
	
	int a=0;
	while (!a) {
		printf("choose the map: 1 or 2\n");
		scanf_s("%d", &m);
		if (m > 2||m<1) printf("error\n");
		else a = 1;
	}
	
	play();
	return 0;
}