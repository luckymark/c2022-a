#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;

#define BRICK '#'
#define PLAYER 'I'
#define DESTI '!'

char Map[11][11] = {
		 "I ########",
		 "#       ##",
		 "# # ### ##",
		 "# # ### ##",
		 "# # ######",
		 "# #      #",
		 "# ###### #",
		 "# #    ###",
		 "#   ##   !",
		 "##########" };
int ch, x = 0, y = 0;

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

void Move()
{
	do
	{
		Map[x][y] = ' ';
		ch = _getch();
		if ((ch == 72) && (Map[x - 1][y] != BRICK))
		{
			x--;
		}
		else if ((ch == 80) && (Map[x + 1][y] != BRICK))
		{
			x++;
		}
		else if ((ch == 75) && (Map[x][y - 1] != BRICK))
		{
			y--;
		}
		else if ((ch == 77) && (Map[x][y + 1] != BRICK))
		{
			y++;
		}
	} while ((ch != 72) && (ch != 80) && (ch != 75) && (ch != 77));
	if (Map[x][y] != DESTI)
	{

		Map[x][y] = PLAYER;
	}
}

int main()
{


	while (Map[x][y] != DESTI)
	{
		Draw();
		Move();
	}

	printf("You WIN!\n");

	return 0;
}


