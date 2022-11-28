// maze迷宫.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	clock_t before, after;
	before = clock();
	printf("欢迎来到迷宫游戏！(你必须捡到钱后再到出口！)\n");
	int x = 1, y = 1;
	char arr[10][10] = { 
	{'*','*','*','*','*','*','*','*','*','*'},
	{'*',' ','*',' ',' ',' ',' ',' ',' ','*'},
	{'*',' ','*',' ','*',' ','*','*',' ','*'},
	{'*',' ',' ',' ','*',' ','*',' ',' ','*'},
	{'*','*','*',' ','*','*','*',' ','*','*'},
	{'$',' ','*',' ','*',' ','*',' ',' ','*'},
	{'*',' ','*',' ','*',' ','*',' ','*','*'},
	{'*',' ','*',' ',' ',' ','*',' ','*','*'},
	{'*',' ',' ',' ','*','*','*',' ',' ',' '},
	{'*','*','*','*','*','*','*','*','*','*'} };
	arr[y][x] = '@';
	while (1)
	{
		system("cls");
		for (int a = 0; a < 10; a++)
		{
			for (int b = 0; b < 10; b++)
			{
				printf("%c\t", arr[a][b]);
			}
			printf("\n\n");
		}
		printf("请输入移动方向：\n");
		sign:
		switch (getchar())
		{
		case 'w':if (arr[y - 1][x] == ' ')
		{
			arr[y - 1][x] = '@';
			arr[y][x] = ' ';
			y--;
		}getchar(); break;
		case 'a':
			if (arr[y][x - 1] == ' ')
		{
			arr[y][x - 1] = '@';
			arr[y][x] = ' ';
			x--;
		}
			else if (arr[y][x - 1] == '$')
		{
				arr[y][x - 1] == '@';
				arr[y][x] = ' ';
				x--;
				printf("你已成功捡到钱！\n");
		}
			else { ; }
				getchar(); break;
		case 's':if (arr[y + 1][x] == ' ')
		{
			arr[y + 1][x] = '@';
			arr[y][x] = ' ';
			y++;
		}getchar(); break;
		case 'd':if (arr[y][x + 1] == ' ')
		{
			arr[y][x + 1] = '@';
			arr[y][x] = ' ';
			x++;
		}getchar(); break;
		default:printf("输入错误！请重新输入：\n"); goto sign; //重新输入
		}
		if (x == 9 && y == 8&&arr[5][0]==' ') {
			after = clock();
			printf("恭喜你获得胜利！耗时%.1lf秒！\n",(after-before)/(double)1000);
			break;
		}
	}
	return 0;
}