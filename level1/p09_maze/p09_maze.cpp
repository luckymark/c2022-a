#define ROW 21
#define LINE 22
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
char maze[ROW][LINE] = {
					"000000000000000000000",
					"0 0 0 0     0     0 0",
					"0 0 0 00000 00000 0 0",
					"0 0               0 0",
					"0 000 000 0 000 0 0 0",
					"0 0     0 0 0   0 0 0",
					"0 0 0 00000 000 000 0",
					"0 0 0     0   0 0    ",
					"0 000 0 0 000 0 0 0 0",
					"0     0 0 0 0 0 0 0 0",
					"0 00000 000 000 0 0 0",
					"0     0       0   0 0",
					"000 0 0 0 000 0 0 0 0",
					"0 0 0 0 0 0   0 0 0 0",
					"0 0000000 0 000 00000",
					"@   0   0 0         0",
					"0 0 0 0 0 00000000000",
					"0 0 0 0             0",
					"000 0 00000 0 000 000",
					"0         0 0   0   0",
					"000000000000000000000" 
};

void print()
{
	for (int i = 0; i <LINE-1; i++)
	{
		puts(maze[i]);
	}
}

int main()
{
	int x, y, endr, endl;
	char ch;
	x = 15; y = 0; 
	endr = 7; endl = 20;
	print();
	while (x != endr || y != endl)
	{
		ch = getch();

		if (ch == 's')
		{
			if (maze[x + 1][y] != '0')
			{
				maze[x][y] = ' ';
				x++;
				maze[x][y] = '@';
			}
		}
		else if (ch == 'w')
		{
			if (maze[x - 1][y] != '0')
			{
				maze[x][y] = ' ';
				x--;
				maze[x][y] = '@';
			}
		}
		else if (ch == 'a')
		{
			if (maze[x][y - 1] != '0')
			{
				maze[x][y] = ' ';
				y--;
				maze[x][y] = '@';
			}
		}
		else if (ch == 'd')
		{
			if (maze[x][y + 1] != '0')
			{
				maze[x][y] = ' ';
				y++;
				maze[x][y] = '@';
			}
		}
		system("cls");
		print();
	}
	system("cls");
	printf("ÄãÓ®ÁË");
	return 0;
}