#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;

#define BRICK '#'
#define PLAYER 'I'
#define BOX '1'
#define PLACE '0'
#define MAXMARK 500

char Map[11][11] = {
		 "I ########",
		 "#        #",
		 "#  1   0 #",
		 "#  1     #",
		 "#   ######",
		 "#        #",
		 "#        #",
		 "#        #",
		 "#       0#",
		 "##########" };
int ch, x = 0, y = 0,goals=0,step=0;

void Draw()
{
	system("cls");
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			printf("%c", Map[i][j]);
		}
		printf("\n");
	}

}

void judge(int x, int y)
{
	if (Map[x][y] == PLACE)
	{
		goals += 1;
	}
}

void Move()
{
	do
	{
		Map[x][y] = ' ';
		ch = _getch();
		if ((ch == 72) && (Map[x - 1][y] != BRICK))
		{
			x--;
			if ((Map[x][y] == BOX)&& (Map[x - 1][y] != BRICK))
			{
				Map[x][y] = PLAYER;
				judge(x-1,y);
				Map[x-1][y] = BOX;
			}
			else if ((Map[x][y] == BOX) && (Map[x - 1][y] == BRICK))
			{
			     x++;
			}
		}
		else if ((ch == 80) && (Map[x + 1][y] != BRICK))
		{
			x++;
			if ((Map[x][y] == BOX) && (Map[x + 1][y] != BRICK))
			{
				Map[x][y] = PLAYER;
				judge(x + 1, y);
				Map[x + 1][y] = BOX;
			}
			else if ((Map[x][y] == BOX) && (Map[x - 1][y] == BRICK))
			{
				x--;
			}
		}
		else if ((ch == 75) && (Map[x][y - 1] != BRICK))
		{
			y--;
			if ((Map[x][y] == BOX) && (Map[x][y - 1] != BRICK))
			{
				Map[x][y] = PLAYER;
				judge(x ,y-1);
				Map[x][y - 1] = BOX;
			}
			else if ((Map[x][y] == BOX) && (Map[x][y - 1] == BRICK))
			{
				y++;
			}
		}
		else if ((ch == 77) && (Map[x][y + 1] != BRICK))
		{
			y++;
			if ((Map[x][y] == BOX) && (Map[x][y + 1] != BRICK))
			{
				Map[x][y] = PLAYER;
				judge(x ,y+1);
				Map[x][y + 1] = BOX;
			}
			else if ((Map[x][y] == BOX) && (Map[x][y +1] == BRICK))
			{
				y--;
			}
		}
	} while ((ch != 72) && (ch != 80) && (ch != 75) && (ch != 77));
	Map[x][y] = PLAYER;
	step += 1;
}





int main()
{


	while (goals!=2)
	{
		Draw();
		Move();
	}

	printf("You WIN!\n");
	printf("Your Mark is %d\n",MAXMARK-10*step);

	return 0;
}
