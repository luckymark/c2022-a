#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void MakeMaps()
{
	char arr1[10][10] = {
	{'*','*','*','*','*','*','*','*','*','*'},
	{'*',' ',' ',' ',' ',' ',' ',' ','#',' '},
	{'*',' ',' ',' ','*',' ','*','*',' ','*'},
	{'*',' ',' ',' ','*',' ','*',' ',' ','*'},
	{'*','*','*',' ','*','*','*',' ','*','*'},
	{'*',' ','*',' ','*',' ','*',' ',' ','*'},
	{'*','#','*',' ','*','#','*',' ','*','*'},
	{'*',' ','*',' ',' ',' ','*',' ','*','*'},
	{'*',' ',' ',' ','*','*','*',' ','#',' '},
	{'*','*','*','*','*','*','*','*','*','*'} };

	char arr2[10][10] = {
	{'*','*','*','*','*','*','*','*','*','*'},
	{'*',' ','*',' ',' ',' ',' ',' ',' ','*'},
	{'*',' ','*',' ','*','#','*','*',' ','*'},
	{'*',' ',' ',' ','*',' ','*',' ',' ','*'},
	{'*',' ',' ',' ','*','*','*',' ','*','*'},
	{'*',' ',' ',' ','*','*','*',' ',' ','*'},
	{'*',' ',' ',' ','*','*','*',' ','*','*'},
	{'*','#','*',' ','#',' ','*',' ','*','*'},
	{'*',' ','*',' ','*','*','*','#','*','*'},
	{'*','*','*','*','*','*','*',' ','*','*'} };

	char arr3[10][10] = {
	{'*','*','*','*','*','*','*','*','*','*'},
	{'*',' ','*',' ',' ',' ',' ',' ',' ','*'},
	{'*',' ','*',' ','*',' ','*','*',' ','*'},
	{'*',' ',' ',' ','*',' ','*',' ',' ','*'},
	{'*','*','*',' ','*','*','*',' ','*','*'},
	{' ','#',' ',' ','*','*','*',' ',' ','*'},
	{'*',' ','*',' ','*','*','*',' ','*','*'},
	{'*',' ','*',' ','*',' ','#',' ','*','*'},
	{'*',' ',' ','#','*','*','*','#','*','*'},
	{'*','*','*',' ','*','*','*',' ','*','*'} };

	FILE* fp1 = fopen("sample1.txt", "w");
	FILE* fp2 = fopen("sample2.txt", "w");
	FILE* fp3 = fopen("sample3.txt", "w");
	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			fputc(arr1[a][b], fp1);
		}
	}
	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			fputc(arr2[a][b], fp2);
		}
	}
	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			fputc(arr3[a][b], fp3);
		}
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}


int main()
{
	MakeMaps();
	//制作三个随机地图
	FILE* fp=NULL;
	
	srand((unsigned)time(NULL));
	clock_t before, after;
	before = clock();
	printf("欢迎来到迷宫游戏！(#是箱子，*是墙，@是玩家)\n");
	int x = 1, y = 1;
	int grade=150;
	char arr[10][10];
	

	switch (rand() % 3 + 1)
	{
	case 1:fp = fopen("sample1.txt", "r"); break;
	case 2:fp = fopen("sample2.txt", "r"); break;
	case 3:fp = fopen("sample3.txt", "r"); break;
	default:printf("error!\n\a"); break;
	}

	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			arr[a][b] = fgetc(fp);
		}
	}
	arr[y][x] = '@';//玩家
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
	back: //重新输入窗口
		switch (getchar())
		{
		case 'w':
			if (arr[y - 1][x] == ' ')
			{
				arr[y - 1][x] = '@';
				arr[y][x] = ' ';
				y--;
				grade--;
			}
			else if (arr[y - 1][x] == '#' && arr[y - 2][x] == ' ')
			{
				arr[y - 2][x] = '#';
				arr[y - 1][x] = '@';
				arr[y][x] = ' ';
				y--;
				grade--;
			}
			else;
		getchar(); break;
		case 'a':
			if (arr[y][x - 1] == ' ')
			{
				arr[y][x - 1] = '@';
				arr[y][x] = ' ';
				x--;
				grade--;
			}
			else if (arr[y][x-1] == '#' && arr[y][x-2] == ' ')
			{
				arr[y][x-2] = '#';
				arr[y][x-1] = '@';
				arr[y][x] = ' ';
				x--;
				grade--;
			}
			else;
			getchar(); break;
		case 's':
			if (arr[y + 1][x] == ' ')
		    {
			arr[y + 1][x] = '@';
			arr[y][x] = ' ';
			y++;
			grade--;
		    }
			else if (arr[y + 1][x] == '#' && arr[y + 2][x] == ' ')
			{
				arr[y + 2][x] = '#';
				arr[y + 1][x] = '@';
				arr[y][x] = ' ';
				y++;
				grade--;
			}
			else;
			getchar(); break;
		case 'd':
			if (arr[y][x + 1] == ' ')
		    {
			arr[y][x + 1] = '@';
			arr[y][x] = ' ';
			x++;
			grade--;
		    }
			else if (arr[y][x+1] == '#' && arr[y][x+2] == ' ')
			{
				arr[y][x+2] = '#';
				arr[y][x+1] = '@';
				arr[y][x] = ' ';
				x++;
				grade--;
			}
			else;
			getchar(); break;
		default:printf("输入错误！请重新输入：\n"); goto back; //重新输入
		}

		if (arr[5][1]=='#'&&arr[5][5]=='#'&&arr[1][9]=='#'&&arr[8][9]=='#'||
			arr[8][1]=='#'&&arr[7][5]=='#'&&arr[9][7]=='#'&&arr[3][5]=='#'||
			arr[5][0]=='#'&&arr[9][3]=='#'&&arr[7][5]=='#'&&arr[9][7]=='#')
		{
			after = clock();
			printf("恭喜你获得胜利！耗时%.1lf秒！\n", (after - before) / (double)1000);
			printf("你一共走了%d步，你的得分是%d分！\n", 150-grade,grade);
			break;
		}
	}
	fclose(fp);
	return 0;
}