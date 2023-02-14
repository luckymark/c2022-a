#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
char  map[50][50]{
			"##############################",
			"#@         #   ##   # ### ####",
			"# #   ## #   # #### # ### ####",
			"#   # ##   ###    # #  ##   ##",
			"#   # ##  ###    #  #  ## ####",
			"##### #     # ##### ##    ####",
			"#   # ##### #   #   # # #    #",
			"# # #    ## # #### ## # # ####",
			"# # # ##      ##      # # ####",
			"# # # #### ## ## ###### #   ##",
			"# #   ##   # ## ###### ###   #",
			"# ###### # #####  #        # #",
			"#        # #     ##### ### #  ",
			"# ######## ##### # ### ### # #",
			"#     # ## ##### ###       ###",
			"##### # ## #      ######## # #",
			"#     # ## ## ###        #   #",
			"# # ###       ###### ####### #",
			"# #    ### ##      #         #",
			"##############################"
};
int x = 1, y = 1, winX = 12, winY = 29;
void move(char);
int main()
{
	int i;
	char ch;
	for (i = 0; i <= 19; i++)
	{
		puts(map[i]);
	}
	while (x != winX || y != winY)
	{
	ch = getch();
	move(ch);
	}
	system("cls");
	printf("win!\n");
	system("pause");
	return 0;
}
void move(char ch) {

	
	switch (ch)
	{
	case 'w':
		if (map[x - 1][y] != '#')
		{
			map[x][y] = ' ';
			x--;
			map[x][y] = '@';
			break;
		}
	case 's':
		if (map[x + 1][y] != '#')
		{
			map[x][y] = ' ';
			x++;
			map[x][y] = '@';
			break;
		}
	case 'a':
		if (map[x][y - 1] != '#')
		{
			map[x][y] = ' ';
			y--;
			map[x][y] = '@';
			break;
		}
	case 'd':
		if (map[x][y + 1] != '#')
		{
			map[x][y] = ' ';
			y++;
			map[x][y] = '@';
			break;
		}
	}
	system("cls");
	for (int i = 0; i <= 19; i++)
		puts(map[i]);
}










