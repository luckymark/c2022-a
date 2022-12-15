#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<easyx.h>
#include<conio.h>
#define ROW 12
#define COL 20

#define SIZER 15
#define SIZEC 15

#define RIGHT 100
#define LEFT 97
#define UP 119
#define DOWN 115


int px = 0;
int py = 0;

enum element
{
	WAY,WALL, DOOR,PLAYER,MEMORY
};

int Map[ROW][COL];

void readmap(const char* file)
{
	FILE* fp = fopen(file, "r");//https://blog.csdn.net/keith_bb/article/details/51119437
	if (!fp)
	{
		perror("error~");
		return ;
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			fscanf(fp, "%d ",&Map[i][j]);//这里一定要加&，别忘了！！
		}
	}
	fclose(fp);
}



void player()
{
	flag:
	switch (_getch())
	{
	case RIGHT:
		if (Map[px][py+1] == WALL)
			goto flag;
		py++;
		Map[px][py] = PLAYER;
		break;
	case LEFT:
		if (Map[px][py-1] == WALL)
			goto flag;
		py--;
		Map[px][py] = PLAYER;
		break;
	case UP:
		if (Map[px-1][py] == WALL)
			goto flag;
		px--;
		Map[px][py] = PLAYER;
		break;
	case DOWN:
		if (Map[px+1][py] == WALL)
			goto flag;
		px++;
		Map[px ][py] = PLAYER;
		break;
	default:
		printf("error");
		break;
	}
}



void show()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%d ",Map[i][j]);
		}
		printf("\n");
	}
}



int judge()
{
	if (Map[ROW -1][COL -1] == PLAYER)
		return 0;
	return 1;
}

void draw()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			int x = j * SIZER;
			int y = i * SIZEC;
			switch (Map[i][j])
			{
			case WALL:
				setfillcolor(RGB(0, 170, 0));
				fillrectangle(x, y, x+SIZER, y+SIZEC);
				break;
			case DOOR:
				setfillcolor(RGB(0,0,170));
				fillrectangle(x, y, x + SIZER, y + SIZEC);
				break;
			case PLAYER:
				setfillcolor(RGB(170, 0, 0));
				fillrectangle(x, y, x + SIZER, y + SIZEC);
			case MEMORY:
				setfillcolor(RGB(170, 170, 0));
				fillrectangle(x, y, x + SIZER, y + SIZEC);
			default:
				break;
			}
		}
	}
}

int main()
{
	initgraph(960,640);
	readmap("./resource/map.txt");
	do
	{
		draw();
		player();
	} while (judge() == 1);
	//show();
	system("pause");
	return 0;
}