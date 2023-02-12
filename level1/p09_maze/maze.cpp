#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
int main()
{
	char  Map[50][50]{
			"##############################",
			"#@         #   ##   # ### ####",
			"#    # #   # ### #   ### #  #",
			"#  #####   ###    # #  ##   ##",
			"#   # ##  ###    #  #  ## ####",
			"##  # #     # ##### ##    ####",
			"#   # ##  # #   #   # # #    #",
			"# # #    ## # #### ## # # ####",
			"# # # ##      ##      # # ####",
			"# # # #### ## ## #  ### #   ##",
			"# #   ##   # ## ###### ###   #",
			"# ###### # #####  #        # #",
			"#  ##    # #     ##### ### #  ",
			"# ######## ##### # ### ### # #",
			"#     # ## ##### ###       ###",
			"##### # ## #      ######## # #",
			"#     # ## ## ###        #   #",
			"# # ###       ###### ####### #",
			"# #    ### ##      #   ###   #",
			"##############################"
	};


	int x = 1, y = 1, WinX = 12, WinY = 29, i;
	char ac;
	for (i = 0; i <= 19; i++)
	{
		puts(Map[i]);
	}
	while (x != WinX || y != WinY)
	{
		ac = getch();
		switch (ac)
		{
		case 'w':
			if (Map[x - 1][y] != '#')
			{
				Map[x][y] = ' ';
				x--;
				Map[x][y] = '@';
				break;
			}
		case 's':
			if (Map[x + 1][y] != '#')
			{
				Map[x][y] = ' ';
				x++;
				Map[x][y] = '@';
				break;
			}
		case 'a':
			if (Map[x][y - 1] != '#')
			{
				Map[x][y] = ' ';
				y--;
				Map[x][y] = '@';
				break;
			}
		case 'd':
			if (Map[x][y + 1] != '#')
			{
				Map[x][y] = ' ';
				y++;
				Map[x][y] = '@';
				break;
			}
		}
		system("cls");
		for (i = 0; i <= 19; i++)
			puts(Map[i]);
	}
	system("cls");
	printf("ÄãÓ®ÁË!\n");
	system("pause");
	return 0;
}
