#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

#define MAXSIZE 15
#define MAXDESTINATION 20
#define STACKSIZE 1000
enum{ROUTE,WALL,CHARACTER,BOX,DESTINATION};

typedef struct {
	char str[STACKSIZE];
	int top;
}Stack;

void push(Stack* stack, char x);
char pop(Stack* stack);
void searchCharacter(char** map, int* x, int* y, int row);
int searchDestination(char** map, int des[][2], int row);
void printMap(char** map, int desNum, int des[][2]);
void record(int mapNum, unsigned step);
int check(char** map, int des[][2], int desNum);
void move(char** map,Stack* tack, int x, int y, int desNum, int des[][2], unsigned* step);

int main() {
	int chX = 0, chY = 0, row = 0, desNum = 0, mapNum = 0;
	unsigned step = 0;
	int des[MAXDESTINATION][2] = { 0 };
	Stack stack;
	stack.top = -1;
	char** map = (char**)malloc(MAXSIZE * sizeof(char*));
	for (int i = 0; i < MAXSIZE; i++) {
		map[i] = (char*)calloc(MAXSIZE, sizeof(char));
	}

	//读取地图的文件到数组中
	FILE* fpMap = NULL;
	printf("请输入1或2以选择地图\n");
	scanf_s("%d", &mapNum);
	system("cls");
	switch (mapNum) {
	case 1:	fopen_s(&fpMap, "map1.txt", "r");
		break;
	case 2: fopen_s(&fpMap, "map2.txt", "r");
		break;
	default:
		break;
	}
	if (fpMap) {
		for (int i = 0; (fgets(map[i], MAXSIZE, fpMap)) != NULL; i++) {
			row++;
		}
		fclose(fpMap);
	}
	else printf("The file is not existen\n");
	
	printMap(map, desNum, des);
	searchCharacter(map, &chX, &chY, row);
	desNum = searchDestination(map, des, row);
	move(map, &stack, chX, chY, desNum, des, &step);
	printf("You moved %u steps\n", step);
	record(mapNum,step);
	return 0;
}
void push(Stack* stack, char x) {
	if (stack->top == STACKSIZE - 1) {
		printf("FULL!\n");
	}
	else {
		stack->str[++stack->top] = x;
	}
}

char pop(Stack* stack) {
	int x = 0;
	if (stack->top == -1) {
		printf("EMPTY!\n");
	}
	else {
		x = stack->str[stack->top--];
	}
	return x;
}

void searchCharacter(char** map,int* x, int* y, int row) {
	int flag = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < strlen(map[i]); j++) {
			if (map[i][j] == CHARACTER + '0') {
				*x = i;
				*y = j;
				flag = 1;
				break;
			}
		}
		if (flag) break;
	}
}

int searchDestination(char** map, int des[][2], int row) {
	int t = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < strlen(map[i]); j++) {
			if (map[i][j] == DESTINATION + '0') {
				des[t][0] = i;
				des[t][1] = j;
				t++;
			}
		}
	}
	return t;
}

void printMap(char** map, int desNum, int des[][2]) {
	printf("#####按W、S、A、D移动，按R回退#####\n");
	//修补回退产生的bug
	for (int i = 0; i < desNum;i++){
		if (map[des[i][0]][des[i][1]] == ROUTE + '0') {
			map[des[i][0]][des[i][1]] = DESTINATION + '0';
		}
	}
	for (int i = 0; i < MAXSIZE; i++)
	{	
		for (int j = 0; j < MAXSIZE; j++)
		{
			switch (map[i][j] - '0')
			{
				case 0:
					printf("  ");//route
					break;
				case 1:
					printf("█ ");//wall
					break;
				case 2:
					printf("♀");//character
					break;
				case 3:
					printf("●");//box
					break;
				case 4:
					printf("☆");//destination
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
}

void record(int mapNum, unsigned step) {
	FILE* fp = NULL;
	int isEmpty = 0;
	unsigned minStep = 0;
	switch (mapNum) {
	case 1:	fopen_s(&fp, "record1.txt", "r");
		break;
	case 2: fopen_s(&fp, "record2.txt", "r");
		break;
	default:
		break;
	}
	if (fp != NULL) {
		if (fgetc(fp) == EOF){
			isEmpty = 1;
		}
		fclose(fp);
	}

	switch (mapNum) {
	case 1:	fopen_s(&fp, "record1.txt", "w");
		break;
	case 2: fopen_s(&fp, "record2.txt", "w");
		break;
	default:
		break;
	}
	//不为空，有记录
	if (isEmpty == 0) {
		if (fp != NULL) {
			fscanf_s(fp, "%d", minStep);
			if (step < minStep) {
				fprintf(fp, "%d\n", step);
				fputs("The minimum step is ", fp);
				fprintf(fp, "%d", step);
			}
		}
	}
	//为空
	else{
		fprintf(fp, "%d\n", step);
		fputs("The minimum step is ", fp);
		fprintf(fp, "%d", step);
	}
	fclose(fp);
}

int check(char** map, int des[][2], int desNum) {
	int flag = 1;
	for (int i = 0; i < desNum; i++) {
		if (map[des[i][0]][des[i][1]] != BOX + '0') {
			flag = 0;
		}
	}
	return flag;
}

void move(char** map, Stack* stack, int x, int y, int desNum, int des[][2], unsigned* step) {
	int t = 0, flag = 0;
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//上、下、左、右
	char ch;	
	while (1) {
		flag = 0;
		ch = _getch();
		if (ch == 'w' || ch == 'W') {
			t = 0;
			flag = 0;
		}
		else if (ch == 's' || ch == 'S') {
			t = 1;
			flag = 0;
		}
		else if (ch == 'a' || ch == 'A') {
			t = 2;
			flag = 0;
		}
		else if (ch == 'd' || ch == 'D') {
			t = 3;
			flag = 0;
		}
		else if (ch == 'r' || ch == 'R') {
			flag = 1;
		}
		//压栈的时候，小写仅移动，大写推箱子
		if (flag != 1) {
			(*step)++;
			//仅移动
			if (map[x + dir[t][0]][y + dir[t][1]] == ROUTE + '0' || map[x + dir[t][0]][y + dir[t][1]] == DESTINATION + '0') {
				map[x][y] = ROUTE + '0';
				x += dir[t][0];
				y += dir[t][1];
				map[x][y] = CHARACTER + '0';
				if ('a' <= ch && ch <= 'z') {
					push(stack, ch);
				}
				else {
					push(stack, ch + 'a' - 'A');
				}
			}
			//推箱子
			else if (map[x + dir[t][0]][y + dir[t][1]] == BOX + '0' && map[x + 2 * dir[t][0]][y + 2 * dir[t][1]] != WALL + '0') {
				map[x][y] = ROUTE + '0';
				x += dir[t][0];
				y += dir[t][1];
				map[x][y] = CHARACTER + '0';
				map[x + dir[t][0]][y + dir[t][1]] = BOX + '0';
				if ('a' <= ch && ch <= 'z') {
					push(stack, ch - 'a' + 'A');
				}
				else {
					push(stack, ch);
				}
			}
		}
		//回退
		else {
			(*step)--;
			ch = pop(stack);
			if (ch == 'w' || ch == 'W') {
				t = 0;
			}
			else if (ch == 's' || ch == 'S') {
				t = 1;
			}
			else if (ch == 'a' || ch == 'A') {
				t = 2;
			}
			else if (ch == 'd' || ch == 'D') {
				t = 3;
			}
			//仅移动
			if ('a' <= ch && ch <= 'z') {
				map[x][y] = ROUTE + '0';
				x -= dir[t][0];
				y -= dir[t][1];
				map[x][y] = CHARACTER + '0';
			}
			else if ('A' <= ch && ch <= 'Z') {
				map[x + dir[t][0]][y + dir[t][1]] = ROUTE + '0';
				map[x][y] = BOX + '0';
				x -= dir[t][0];
				y -= dir[t][1];
				map[x][y] = CHARACTER + '0';
			}
		}
		system("cls");
		printMap(map, desNum, des);

		if (check(map, des, desNum)) {
			printf("YOU WIN!\n");
			break;
		}
	}
}