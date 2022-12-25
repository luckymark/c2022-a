#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<easyx.h>

#define NODE_WIDTH 50


enum MyEnum
{
	Space = 0,
	Wall=1,
	Dest=2,
	Box=3,
	Person=4
};
typedef struct node {
	int x;
	int y;
}node;
node person;
void paintGrid()
{
	for (int y = 0; y < 500; y += NODE_WIDTH)
	{
		line(0, y,500, y);
	}
	for (int x = 0; x < 500; x += NODE_WIDTH)
	{
		line(x, 0, x, 500);
	}

}
int map[10][10] = {
	{0,0,0,1,1,1,0,0,0,0},
	{0,1,1,1,2,1,0,0,0,0},
	{1,1,0,3,0,1,1,1,1,1},
	{1,2,0,3,4,3,0,0,2,1},
	{1,1,1,1,3,1,1,1,1,1},
	{0,0,1,1,0,1,0,0,0,0},
	{0,0,1,0,0,1,1,1,1,0},
	{0,0,1,0,0,0,0,2,1,0},
	{0,0,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0},
};//创建二维数组作为地图

void paintMap()
{
	for(int i=0;i<10;i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{

			case Wall:
			{IMAGE img_wall;
			loadimage(&img_wall, "Wall.jpg");
			putimage(j * NODE_WIDTH, i * NODE_WIDTH, &img_wall);
			break; }
			case Dest:
			{IMAGE img_dest;
			loadimage(&img_dest, "Dest.jpg");
			putimage(j * NODE_WIDTH, i * NODE_WIDTH, &img_dest);
			break; }
			case Box:
			{IMAGE img_box;
			loadimage(&img_box, "Box.jpg");
			putimage(j * NODE_WIDTH, i* NODE_WIDTH, &img_box);
			break; }
			case Person:
			{IMAGE img_person;
			loadimage(&img_person, "Person.jpg");
			putimage(j * NODE_WIDTH, i * NODE_WIDTH, &img_person);
			person.x =i; person.y = j;
			break; }
			case Box+Dest:
			{IMAGE img_bd;
			loadimage(&img_bd, "Box+Dest.jpg");
			putimage(j * NODE_WIDTH, i * NODE_WIDTH, &img_bd);
			break; }
			}
		}

	}
}

void move()
{

	char c = _getch();
		switch (c)
		{
		case 'w':
		{
			if (map[person.x - 1][person.y] ==Space)
			{
				map[person.x - 1][person.y] = Person;
				map[person.x][person.y] = Space;
				person.x = person.x - 1;
			}
			else if (map[person.x - 1][person.y] == Box)
			{
				if (map[person.x - 2][person.y] == Space)
				{
					map[person.x - 2][person.y] = Box;
					map[person.x - 1][person.y] = Person;
					map[person.x][person.y] = Space;
					person.x = person.x - 1;
				}
				else if (map[person.x - 2][person.y] == Dest)
				{
					map[person.x - 2][person.y] = Box + Dest;
					map[person.x - 1][person.y] = Person;
					map[person.x][person.y] = Space;
					person.x = person.x - 1;
				}
			}
			break;
		}
		case 's':
		{	
			if (map[person.x + 1][person.y] == Space)
		{
			map[person.x + 1][person.y] = Person;
			map[person.x][person.y] = Space;
			person.x = person.x + 1;
		}
		else if (map[person.x + 1][person.y] == Box)
		{
			if (map[person.x + 2][person.y] == Space)
			{
				map[person.x + 2][person.y] = Box;
				map[person.x + 1][person.y] = Person;
				map[person.x][person.y] = Space;
				person.x = person.x + 1;
			}
			else if (map[person.x + 2][person.y] == Dest)
			{
				map[person.x + 2][person.y] = Box + Dest;
				map[person.x + 1][person.y] = Person;
				map[person.x][person.y] = Space;
				person.x = person.x + 1;
			}
		}

		break;
		}
		case 'a':
		{	if (map[person.x][person.y - 1] == Space)
		{
			map[person.x][person.y - 1] = Person;
			map[person.x][person.y] = Space;
			person.y = person.y - 1;
		}
		else if (map[person.x][person.y - 1] == Box)
		{
			if (map[person.x][person.y - 2] == Space)
			{
				map[person.x][person.y - 2] = Box;
				map[person.x][person.y - 1] = Person;
				map[person.x][person.y] = Space;
				person.y = person.y - 1;
			}
			else if (map[person.x][person.y - 2] == Dest)
			{
				map[person.x][person.y - 2] = Box + Dest;
				map[person.x][person.y - 1] = Person;
				map[person.x][person.y] = Space;
				person.y = person.y - 1;
			}
		}
		break;
		}
		case 'd':
		{	if (map[person.x][person.y + 1] == Space)
		{
			map[person.x][person.y + 1] = Person;
			map[person.x][person.y] = Space;
			person.y = person.y + 1;
		}
		else if (map[person.x][person.y + 1] == Box)
		{
			if (map[person.x][person.y + 2] == Space)
			{
				map[person.x][person.y + 2] = Box;
				map[person.x][person.y + 1] = Person;
				map[person.x][person.y] = Space;
				person.y = person.y + 1;
			}
			else if (map[person.x][person.y + 2] == Dest)
			{
				map[person.x][person.y + 2] = Box + Dest;
				map[person.x][person.y + 1] = Person;
				map[person.x][person.y] = Space;
				person.y = person.y + 1;
			}
		}

		break;
		}
		}
}
int ifwin()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == Box)
				return 0;
		}
	}
	return 1;
}

int main()
{	
	initgraph(500,500);

	setbkcolor(RGB(164, 225, 202));
	cleardevice();
	BeginBatchDraw();
	while (1) 
	{
		cleardevice();
		paintGrid();
		paintMap();
		FlushBatchDraw();
		move();
		int win = ifwin();
		if (win == 1)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					map[i][j] = 0;
						
				}
			}
			for (int x = 0; x < 6; x++)
				map[2][x + 2] = 1;
			for (int x = 0; x < 6; x++)
				map[7][x + 2] = 1;
			map[2][5] = 4; map[3][2] = 1; map[4][2] = 1; map[5][2] = 1; map[6][2] = 1; map[3][5] = 3;
			map[3][7] = 1; map[4][7] = 1; map[5][7] = 1; map[6][7] = 2; map[6][4] = 1; map[5][5] = 1; map[3][7] = 0; map[4][8] = 1;
		}
	}	
	

	EndBatchDraw();
	getchar();
	closegraph();
	return 0;
}

//{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//{0, 0, 1, 1, 1, 4, 1, 1, 0, 0}
//{0, 0, 1, 0, 0, 3, 0, 1, 0, 0}
//{0, 0, 1, 0, 0, 0, 0, 1, 0, 0}
//{0, 0, 1, 0, 0, 1, 0, 1, 0, 0}
//{0, 0, 1, 0, 1, 0, 0, 2, 0, 0}
//{0, 0, 1, 1, 1, 1, 1, 1, 0, 0}
//{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}