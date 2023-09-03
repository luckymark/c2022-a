#include"chessdata.h"
#include"ifwin.h"
#include<math.h>
extern struct chessdata game;



int point_assess(int i, int j)
{
	if (game.chessmap[i][j] == 0)
		return 0;
	int f1 = 10, f2 = 10, f3 = 10, f4 = 10, f5 = 10, f6 = 10, f7 = 10, f8 = 10, m = 1, scorehan, q = 0;
	for (q = 1; game.chessmap[i + q][j] != -game.chessmap[i][j] && i + q < 20 && q < 5; q++)
	{
	}
	if (q < 5)
		f1 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i + a][j] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f1 = pow(10, m);

	}
	m = 1;
	for (q = 1; game.chessmap[i - q][j] != -game.chessmap[i][j] && i - q >4 && q < 5; q++)
	{
	}
	if (q < 5)
		f2 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i - a][j] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f2 = pow(10, m);

	}
	m = 1;
	for (q = 1; game.chessmap[i][j + q] != -game.chessmap[i][j] && j + q < 20 && q < 5; q++)
	{
	}
	if (q < 5)
		f3 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i][j + a] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f3 = pow(10, m);
	}
	m = 1;
	for (q = 1; game.chessmap[i][j - q] != -game.chessmap[i][j] && j - q > 4 && q < 5; q++)
	{
	}
	if (q < 5)
		f4 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i][j - a] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f4 = pow(10, m);
	}
	m = 1;
	for (q = 1; game.chessmap[i + q][j + q] != -game.chessmap[i][j] && i + q < 20 && q < 5 && j + q < 20; q++)
	{
	}
	if (q < 5)
		f5 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i + a][j + a] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f5 = pow(10, m);
	}
	m = 1;
	for (q = 1; game.chessmap[i - q][j - q] != -game.chessmap[i][j] && i - q > 4 && q < 5 && j - q>4; q++)
	{
	}
	if (q < 5)
		f6 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i - a][j - a] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f6 = pow(10, m);
	}
	m = 1;
	for (q = 1; game.chessmap[i + q][j - q] != -game.chessmap[i][j] && i + q < 20 && q < 5 && j - q>4; q++)
	{
	}
	if (q < 5)
		f7 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i + a][j - a] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f7 = pow(10, m);
	}
	m = 1;
	for (q = 1; game.chessmap[i - q][j + q] != -game.chessmap[i][j] && i - q > 4 && q < 5 && j + q < 20; q++)
	{
	}
	if (q < 5)
		f8 = 0;
	else
	{
		for (int a = 1; a <= 4; a++)
		{
			if (game.chessmap[i - a][j + a] == game.chessmap[i][j])
				m++;
			else
				break;
		}

		f8 = pow(10, m);
	}
	scorehan = f1 + f2 + f3 + f4 + f5 + f6 + f7 + f8;
	return scorehan;
}

int  assessmap()
{
	int score_all = 0;
	for (int i = min1; i < max2; i++)
	{
		for (int j = min1; j < max2; j++)
		{

			if (game.chessmap[i][j] == 0)
				game.scoremap[i][j] = 0;
			else if (game.chessmap[i][j] == 1)//ºÚÆå
			{
				game.scoremap[i][j] =point_assess(i, j)*( - 5);
			}
			else if (game.chessmap[i][j] == -1)//°×Æå
			{
				game.scoremap[i][j] = point_assess(i, j);
			}
		}
	}
	for (int i = min1; i < max2; i++)
	{
		for (int j = min1; j < max2; j++)
		{
			score_all = score_all + game.scoremap[i][j];
		}
	}
	return score_all;
}

