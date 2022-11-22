#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<math.h>
 

#define L 24
 
#define WALL  0 
#define ROUTE 1 
#define PLAYER 2
 
int Rank = 6;

int game_time = 120; 
int begin_time;	
int cur_time;   
 
void HideCursor(); 
void toxy(int x, int y); 
void menu();   
void start();  
void degree(); 
void explain();
int init(int** Maze);  
void print(int** Maze);
void CreateMaze(int **maze, int x, int y);    
void move(int** Maze, char t, int *x, int *y);
 
int main() {
	menu();
	return 0;
}
 
void HideCursor() { 
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
 
void toxy(int x, int y){ 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
 
void menu() { 
	while(1) {
		system("cls"); 
		char t;
		printf("*******(走迷宫)*******");
		printf("\n======================\n");
		printf("\n||   1. 开始 游戏   ||\n");
		printf("\n||   2. 游戏 说明   ||\n");
		printf("\n||   3. 游戏 难度   ||\n");
		printf("\n||   4. 关闭 游戏   ||\n");
		printf("======================\n");
		t=getch();    
		switch(t) {
			case '1':
				begin_time = clock(); 
				start();
				break;  
			case '2':
				explain();
				break;  
			case '3':
				degree();
				break;  
			case '4':
				printf("\n欢迎下次再玩，再见（￣︶￣）");
				Sleep(1500);
				exit(0);
				break;  
			default :
				break;
		}
	}
}
 
void CreateMaze(int **maze, int x, int y) {
	maze[x][y] = ROUTE;
	
	int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,-1 },{ 0,1 } };
	int i, j;
	for (i = 0; i < 4; i++) {
		int r = rand() % 4;
		int temp = direction[0][0];
		direction[0][0] = direction[r][0];
		direction[r][0] = temp;
		temp = direction[0][1];
		direction[0][1] = direction[r][1];
		direction[r][1] = temp;
	} 

	for (i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
	
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range > 0) {
		
			dx += direction[i][0];
			dy += direction[i][1];
		
			if (maze[dx][dy] == ROUTE) {
				break;
			}
		
			int count = 0, k;
			for (j = dx - 1; j < dx + 2; j++) {
				for (k = dy - 1; k < dy + 2; k++) {
					
					if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
						count++;
					}
				}
			}
		
			if (count > 1)
				break;
		
			range -= 1;
			maze[dx][dy] = ROUTE;
		}
	
		if (range <= 0) {
			CreateMaze(maze, dx, dy);
		}
	}
}
 
int init(int** Maze) {
	int i;

	for (i = 0; i < L; i++) {
		Maze[i][0] = ROUTE;
		Maze[0][i] = ROUTE;
		Maze[i][L - 1] = ROUTE;
		Maze[L - 1][i] = ROUTE;
	}
	
	CreateMaze(Maze, 2, 2);

	Maze[2][1] = PLAYER;
	
	for (i = L - 3; i >= 0; i--) {
		if (Maze[i][L - 3] == ROUTE) {
			Maze[i][L - 2] = ROUTE;
			
			return i;
		}
	}
}
 
void print(int** Maze) {
	int i, j;
	HideCursor();
	toxy(0, 0);
	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			if (Maze[i][j] == ROUTE)
				printf("  ");
			else if(Maze[i][j] == WALL)
				printf("回");
			else if(Maze[i][j] == PLAYER) 
				printf("十");
		}
		printf("\n");
	}
	cur_time = clock(); 
	int t = (cur_time - begin_time) / 1000 ; 
	printf("剩余时间：%2d", game_time - t);
}
 
void move(int** Maze, char t, int *x, int *y) {
	int i = *x, j = *y;
	switch(t) {
		case 'w':	
			*x -= 1;
			break;
		case 's':	
			*x += 1;
			break;
		case 'a':	
			*y -= 1;
			break;
		case 'd':	
			*y += 1;
			break;
		default:
			break;
	}
	if(*x>=0 && *x<L-1 && *y>=0 && *y<L-1 && Maze[*x][*y]!=WALL) {
		Maze[i][j] = 1;
		Maze[*x][*y] = 2;
	} else {
		*x = i;
		*y = j;
	}
}
 
void start() { 
	char t;
	int *p, *q;
	int x = 2, y = 1, out = 0, i = 0;
	p = &x;
	q = &y;
	srand((unsigned)time(NULL));
	int **Maze = (int**)malloc(L * sizeof(int *));
		for (i = 0; i < L; i++) {
			Maze[i] = (int*)calloc(L, sizeof(int));
		}
		out = init(Maze);
		system("cls");
		print(Maze);
		while(1) {
			if(kbhit()){
				t = getch();  
				if(t == 27)   
					break;
				move(Maze, t, p, q);
			}
			print(Maze);
			if(x == out && y == L-2) {
				system("cls");
				printf("=============\n");
				printf("游 戏 胜 利！\n");
				printf("=============\n");
				printf("即将后返回主菜单……");
				Sleep(1500);
				break;
			}
			if (cur_time - begin_time > game_time*1000)
			{								
				system("cls");
				printf("=============\n");
				printf("游 戏 失 败！\n");
				printf("=============\n");
				printf("即将后返回主菜单……");
				Sleep(2000);
				break;
			}
		}
	
		for (i = 0; i < L; i++) free(Maze[i]);
		free(Maze);
	}
	 
	void explain() { 
		while(1) {
			char t;
			system("cls");
			printf("=================================================\n");
			printf("感谢您体验本游戏，游戏的操作如下：\n");
			printf("\n1.将输入法调整为英文（小写）\n");
			printf("\n2.通过w,s,a,d四个键控制角色上下左右移动\n");
			printf("\n3.在任意界面均可按“ESC”键返回到主菜单\n");
			printf("\n胜利条件：移动角色到出口处，加油各位(￣▽￣)\n");
			printf("=================================================\n");
			t=getch(); 
			switch(t) {
				case 27:
					menu();
					break;
				default :
					break;
			}
		}
	}
	 
	void degree() { 
		while(1) {
			char t;
			system("cls");
			printf("=======================\n");
			printf("输入1,2,3进行难度调整：\n");
			printf("\n||    1.简  单    ||\n");
			printf("\n||    2.中  等    ||\n");
			printf("\n||    3.困  难    ||\n");
			printf("=======================\n");
			t=getch();  
			switch(t) {
				case '1':
					Rank = 6;
					game_time = 120;
					printf("\n当前难度：简单，即将返回主菜单……");
					Sleep(1500);
					menu();
					break; 
				case '2':
					Rank = 3;
					game_time = 90;
					printf("\n当前难度：中等，即将返回主菜单……");
					Sleep(1500);
					menu();
					break;
				case '3':
					Rank = 0;
					game_time = 60;
					printf("\n当前难度：困难，即将返回主菜单……");
					Sleep(1500);
					menu();
					break;
				case 27:
					menu();
					break; 
				default :
					break;
			}
		}
	}
	
