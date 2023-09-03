#include"chessdata.h"
#include"ifwin.h"

extern struct chessdata game;

bool ifwin(int x, int y, int if_heibai)
{
	int ifw = 0;
	if (if_heibai == 1)
	{
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x + i][y] == 1)
				n++;
			else
				n = 0;
			if (n == 5)
				return 1;


		}
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x][y + i] == 1)
				n++;
			else
				n = 0;
			if (n == 5)
				return 1;

		}
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x + i][y + i] == 1)
				n++;
			else
				n = 0;
			if (n == 5)
				return 1;


		}
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x + i][y - i] == 1)
				n++;
			else
				n = 0;
			if (n == 5)

				return 1;

		}
		return ifw;
	}
	else if (if_heibai == -1)
	{
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x + i][y] == -1)
				n++;
			else
				n = 0;
			if (n == 5)
				return 1;

		}
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x][y + i] == -1)
				n++;
			else
				n = 0;
			if (n == 5)
				return 1;
		}
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x + i][y + i] == -1)
				n++;
			else
				n = 0;
			if (n == 5)
				return 1;
		}
		for (int i = -4, n = 0; i <= 4; i++)
		{
			if (game.chessmap[x + i][y - i] == -1)
				n++;
			else
				n = 0;
			if (n == 5)
				return 1;
		}
		return ifw;

	}


}

int end()
{
	int i, j, k = 0, x = 0, y = 0, b = 0, q = 0, e = 0;
	for (i = min1; i < max2; i++)
	{
		for (j = min1; j < max2; j++)
		{
			if (game.chessmap[i][j] == 0)
			{
				k++;
				if (k == 0)
				{
					e = 1;
				}
			}
			if (game.chessmap[i][j])
			{
				for (x = -2; game.chessmap[i][j] == game.chessmap[i][j + x] && x < 4; x++)
				{
				}
				for (y = -2; game.chessmap[i][j] == game.chessmap[i + y][j] && y < 4; y++)
				{

					for (b = -2; game.chessmap[i][j] == game.chessmap[i + b][j + b] && b < 4; b++)
					{
					}
					for (q = -2; game.chessmap[i][j] == game.chessmap[i - q][j + q] && q < 4; q++)
					{
					}
					if (x == 3 || y == 3 || b == 3 || q == 3)
					{
						if (game.chessmap[i][j] == 1)
						{
							e = 2;
						}
						if (game.chessmap[i][j] == -1)
						{
							e = 3;
						}
					}
				}
			}
		}
	}
		return e;



}


