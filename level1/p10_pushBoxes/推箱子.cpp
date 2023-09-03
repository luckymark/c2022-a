#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
int main(){
	int number;
	int i;
	int x = 1;
	int y = 1;
	int records[100];
	int count = 0;
	int point = 0;
	char map[100][100];
	char a[100][100] = { "######",
						"#o    !",
						"# ## #",
						"#  * #",
						"##   #",
						"######" };

	char b[100][100] = { "######",
						"#o   #",
						"# #  #",
						"#  * #",
						"##    !",
						"######" };
	printf("请输入你想玩的地图(1或2)\n 提示：*为箱子，！为目的地");
	scanf_s("%d", &number);
	if (number == 1) {
		for (int j = 0;j < 100;j++)
			for (int k = 0;k < 100;k++) {
				map[j][k] = a[j][k];
			}
	}
	if (number == 2) {
		for (int j = 0;j < 100;j++)
			for (int k = 0;k < 100;k++) {
				map[j][k] = b[j][k];
			}
	}
		for (i = 0; i < 6; i++)
			puts(map[i]);
		char click;
		while (x != 1 || y != 5)
		{
			click = _getch();
			count++;
			if (click == 's')
			{
				if (map[x + 1][y] != '#')
				{
					if (map[x + 1][y] == '*'&&map[x+2][y]!='#') {
						map[x][y] = ' ';
						map[x + 1][y] = 'o';
						map[x + 2][y] = '*';
					}
					if (map[x + 1][y] != '*') {
						map[x][y] = ' ';
						x++;
						map[x][y] = 'o';
					}
				}
			}
			if (click == 'w')
			{
				if (map[x - 1][y] != '#')
				{
					if (map[x - 1][y] == '*' && map[x - 2][y] != '#') {
						map[x][y] = ' ';
						map[x - 1][y] = 'o';
						map[x - 2][y] = '*';
					}
					if (map[x - 1][y] != '*') {
						map[x][y] = ' ';
						x--;
						map[x][y] = 'o';
					}
				}
			}
			if (click == 'a')
			{
				if (map[x][y - 1] != '#')
				{
					if (map[x][y-1] == '*' && map[x][y-2] != '#') {
						map[x][y] = ' ';
						map[x][y-1] = 'o';
						map[x][y-2] = '*';
					}
					if (map[x][y-1] != '*') {
						map[x][y] = ' ';
						y--;
						map[x][y] = 'o';
					}
				}
			}
			if (click == 'd')
			{
				if (map[x][y + 1] != '#')
				{
					if (map[x][y + 1] == '*' && map[x][y + 2] != '#') {
						map[x][y] = ' ';
						map[x][y + 1] = 'o';
						map[x][y + 2] = '*';
					}
					if (map[x][y + 1] != '*') {
						map[x][y] = ' ';
						y++;
						map[x][y] = 'o';
					}
				}
			}

			system("cls");
			if (y == 5)
				printf("成功过关\n");
			for (i = 0; i < 6; i++)
				puts(map[i]);
		}
		if (count == 10) {
			point = 100;
		}
		else if (count >= 10) {
			point = 110 - count;
		}
		int p=0;
		records[p] = point;
		printf("一共走了%d步\n", count);
		printf("您的得分为%d分\n", point);
		printf("历史记录为%d分", records[p]);
		p++;
		return 0;
	}