#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<easyx.h>
#include<conio.h>

#define ROW 12
#define COL 20
#define SIZE 15


#define RIGHT 100
#define LEFT 97
#define UP 119
#define DOWN 115
#define RETRY 8



int map[ROW][COL];
int px = 0;
int py = 0;
int point = 0;





enum element
{
	WAY,WALL,DOOR,PLAYER,BOX
};


void readmap(const char*file)
{
	FILE *fp = fopen(file, "r");
	if (!fp)
	{
		perror("is:");
		return;
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			fscanf(fp, "%d ",&map[i][j]);
		}
	}
	fclose(fp);
}


void draw()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			int x = SIZE * j;
			int y = SIZE * i;
			switch (map[i][j])
			{
			case WAY:
				setfillcolor(RGB(0,0,0));
				fillrectangle(x, y, x + SIZE, y + SIZE);
				break;
			case WALL:
				setfillcolor(RGB(0,0,170));
				fillrectangle(x, y, x + SIZE, y + SIZE);
				break;
			case PLAYER:
				setfillcolor(RGB(0, 170, 170));
				fillrectangle(x, y, x + SIZE, y + SIZE);
				break;
			case BOX:
				setfillcolor(RGB(170, 0, 170));
				fillrectangle(x, y, x + SIZE, y + SIZE);
				break;
			case DOOR:
				setfillcolor(RGB(0, 170, 0));
				fillrectangle(x, y, x + SIZE, y + SIZE);
				break;
			default:
				printf("error");
				break;
			}
		}
	}
}



void move()
{
	flag:
	switch (_getch())
	{
	case RIGHT:
		if (map[px][py + 1] == WALL||(map[px][py+1]==BOX&&map[px][py+2]==WALL))
			goto flag;
		else if (map[px][py + 1] == BOX)
		{
			map[px][py] = WAY;
			py++;
			map[px][py] = PLAYER;
			map[px][py + 1] = BOX;
			point++;
		}
		else
		{
			map[px][py] = WAY;
			py++;
			map[px][py] = PLAYER;
			point++;
		}
		break;
	case LEFT:
		if (map[px][py - 1] == WALL || (map[px][py - 1] == BOX && map[px][py - 2] == WALL))
			goto flag;
		else if (map[px][py - 1] == BOX)
		{
			map[px][py] = WAY;
			py--;
			map[px][py] = PLAYER;
			map[px][py - 1] = BOX;
			point++;
		}
		else
		{
			map[px][py] = WAY;
			py--;
			map[px][py] = PLAYER;
			point++;
		}
		break;
	case UP:
		if (map[px - 1][py] == WALL || (map[px - 1][py] == BOX && map[px - 2][py ]== WALL))
			goto flag;
		else if (map[px - 1][py] == BOX)
		{
			map[px][py] = WAY;
			px--;
			map[px][py] = PLAYER;
			map[px - 1][py] = BOX;
			point++;
		}
		else
		{
			map[px][py] = WAY;
			px--;
			map[px][py] = PLAYER;
			point++;
		}
		break;
	case DOWN:
		if (map[px + 1][py] == WALL || (map[px+1][py] == BOX && map[px+2][py] == WALL))
			goto flag;
		else if (map[px + 1][py] == BOX)
		{
			map[px][py] = WAY;
			px++;
			map[px][py] = PLAYER;
			map[px + 1][py] = BOX;
			point++;
		}
		else
		{
			map[px][py] = WAY;
			px++;
			map[px][py] = PLAYER;
			point++;
		}
		break;
	case RETRY:
		px = 0;
		py = 0;
		point = 0;
		readmap("./resource/map.txt");
		break;
	default:
		printf("error");
		break;
	}
}

int judge()
{
		if (map[ROW - 1][COL - 1] == PLAYER)
			return 0;
		return 1;
}



void remember()
{
	FILE* fp = fopen("./resource/score.txt", "w");
	if (!fp)
	{
		perror("error:");
		return;
	}
	fprintf(fp, "第一局所用步数为：%d", point);
	fclose;
}


void show()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
}




int main()
{
	initgraph(960, 640);
	readmap("./resource/map.txt");
	do
	{
		draw();
		move();
	} while (judge() == 1);
	printf("step:%d",point);
	remember();
	point = 0;
	/*show();*/
	system("pause");
	return 0;
}