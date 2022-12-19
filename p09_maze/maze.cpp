
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
int main()
{
	int i;
	int x = 1;
	int y = 1;
	char a[100][100] = { "######",
						"#o #  ",
						"# ## #",
						"#  # #",
						"##   #",
						"######" };

	for (i = 0; i < 6; i++)
		puts(a[i]);
	char click;
	while (x != 1 || y != 5)
	{
		click = _getch();
		if (click == 's')
		{
			if (a[x + 1][y] != '#')
			{
				a[x][y] = ' ';
				x++;
				a[x][y] = 'o';
			}
		}
		if (click == 'w')
		{
			if (a[x - 1][y] != '#')
			{
				a[x][y] = ' ';
				x--;
				a[x][y] = 'o';
			}
		}
		if (click == 'a')
		{
			if (a[x][y - 1] != '#')
			{
				a[x][y] = ' ';
				y--;
				a[x][y] = 'o';
			}
		}
		if (click == 'd')
		{
			if (a[x][y + 1] != '#')
			{
				a[x][y] = ' ';
				y++;
				a[x][y] = 'o';
			}
		}

		system("cls");
		if (x == 1 && y == 5)
			printf("成功过关\n");
		for (i = 0; i < 6; i++)
			puts(a[i]);
	}

	return 0;
}