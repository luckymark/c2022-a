#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<easyx.h>

#define NODE_WIDTH 20

enum MapEnum
{
	Space = 0,
	Wall = 1,
	Dest = 2,
	Person =3
};

typedef struct node {
	int x;
	int y;
}node;
node person;

void PaintGrid()
{
	for (int y = 0; y < 1000; y += NODE_WIDTH)
		line(0, y, 1000, y);
	for (int x = 0; x < 1000; x += NODE_WIDTH)
		line(x, 0, x, 1000);
}
int map[50][50];

void PaintMap()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			switch (map[i][j])
			{
			case Wall:
			{
				IMAGE img_wall;
				loadimage(&img_wall, "Wall.jpg");
				putimage(j * NODE_WIDTH, i * NODE_WIDTH, &img_wall);
				break;
			}

			case Dest:
			{
			IMAGE img_dest;
			loadimage(&img_dest, "Dest.jpg");
			putimage(j * NODE_WIDTH, i * NODE_WIDTH, &img_dest);
			break; 
			}

			case Person:
			{IMAGE img_person;
			loadimage(&img_person, "Person.jpg");
			putimage(j * NODE_WIDTH, i * NODE_WIDTH, &img_person);
			person.x = i; person.y = j;
			break; }

			case Person + Dest:
			{IMAGE img_bd;
			loadimage(&img_bd, "Person+Dest.jpg");
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
	{	if (map[person.x - 1][person.y] == Space)
		{
		map[person.x][person.y] = Space;
		map[person.x - 1][person.y] = Person;
		person.x = person.x - 1;
		}
		else if (map[person.x - 1][person.y] == Dest)
		{
			map[person.x][person.y] = Space;
			map[person.x - 1][person.y] = Person + Dest;
			person.x = person.x - 1;
		}
		break;
	}
	
	case 's':
	{	if (map[person.x + 1][person.y] == Space)
		{
		map[person.x][person.y] = Space;
		map[person.x + 1][person.y] = Person;
		person.x = person.x + 1;
		}
		else if (map[person.x - 1][person.y] == Dest)
		{
		map[person.x][person.y] = Space;
		map[person.x + 1][person.y] = Person + Dest;
		person.x = person.x + 1;
		}
		break;
	}
	case 'a':
	{	if (map[person.x][person.y-1] == Space)
		{
		map[person.x][person.y] = Space;
		map[person.x][person.y-1] = Person;
		person.y = person.y -1;
		}
		else if (map[person.x ][person.y - 1] == Dest)
		{
		map[person.x][person.y] = Space;
		map[person.x ][person.y - 1] = Person + Dest;
		person.y = person.y - 1;
		}
	break;
	}
	case 'd':
	{	if (map[person.x][person.y + 1] == Space)
		{
		map[person.x][person.y] = Space;
		map[person.x][person.y + 1] = Person;
		person.y = person.y + 1;
		}
		else if (map[person.x][person.y + 1] == Dest)
		{
		map[person.x][person.y] = Space;
		map[person.x][person.y +1] = Person + Dest;
		person.y = person.y + 1;
		}
	break;
	}}
}
int IfWin()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (map[i][j] == Person)
				return 0;
		}
	}
	return 1;
}
int main()
{
	FILE* pFile = NULL;
	errno_t err = 0;
	err=fopen_s(&pFile,"MapData.txt", "r");
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			fscanf_s(pFile, "%d", &map[i][j]);
		}
	}
	fclose(pFile);
	initgraph(1000, 1000);
	setbkcolor(RGB(164, 225, 202));
	cleardevice();
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		PaintGrid();
		PaintMap();
		FlushBatchDraw();
		move();

	}


	EndBatchDraw();
	getchar();
	closegraph();
	return 0;
}