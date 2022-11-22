# define _CRT_SECURE_NO_WARNINGS 1
#include "maze.h"
#include <time.h>

char arr[num][num] ;
void mazeo()
{
	memset(arr, 0, sizeof(arr));
}
void meun()
{
	printf("*********走迷宫*********\n");
	printf("*********1. 开始*********\n");
	printf("*********2. 结束*********\n");
}
void initmaze ()
{
	srand((unsigned)(time)(NULL));
	int i = 1;
	int j = 1;
	int w1,w2,w3,w4 = 0;
	int p1, p2, p3, p4 = 0;
	do {
		 w1= rand() % rem+ 1;
		 w2= rand() % rem + 1;
		 w3 = rand() % rem + 1;
		 w4 = rand() % rem + 1;
	} while (w1+ w2 + w3+w4 != num-3);
	do {
		p1= rand() % rem + 1;
		p2= rand() % rem + 1;
		p3= rand() % rem + 1;
		p4 = rand() % rem + 1;
	} while (p1+ p2+ p3+p4 != num-2);
		for (j= 1; j< w1+1; j++)
		{
			arr[i][j] = 1;
		}
		for (i = 1; i < p1+1; i++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1+w2+ 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; i < p1+p2 + 1; i++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1 + w2 + w3 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; i < p1 + p2+p3 + 1; i++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1 + w2 + w3 +w4+ 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; i < p1 + p2 + p3 +p4+ 1; i++)
		{
			arr[i][j] = 1;
		}
		do {
			w1 = rand() % rem + 1;
			w2 = rand() % rem + 1;
			w3 = rand() % rem + 1;
			w4 = rand() % rem + 1;
		} while (w1 + w2 + w3 + w4 != num - 3);
	
		do {
			p1 = rand() % rem + 1;
			p2 = rand() % rem + 1;
			p3 = rand() % rem + 1;
			p4 = rand() % rem + 1;
		} while (p1 + p2 + p3 + p4 != num - 2);
		
		for (i = 1; i < p1 + 1; i++)
		{
			arr[i][j] = 1;
		}
		for (j = 1; j < w1 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1 + w2 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; i < p1 + p2 + 1; i++)
		{
			arr[i][j] = 1;
		}
		
		for (; i < p1 + p2 + p3 + 1; i++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1 + w2 + w3 + 1; j++)
		{
			arr[i][j] = 1;
		}
		do {
			w1 = rand() % rem + 1;
			w2 = rand() % rem + 1;
			w3 = rand() % rem + 1;
			w4 = rand() % rem + 1;
		} while (w1 + w2 + w3 + w4 != num - 3);
	
		do {
			p1 = rand() % rem + 1;
			p2 = rand() % rem + 1;
			p3 = rand() % rem + 1;
			p4 = rand() % rem + 1;
		} while (p1 + p2 + p3 + p4 != num - 2);
		for (j = 1; j < w1 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (i = 1; i < p1 + 1; i++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1 + w2 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; i < p1 + p2 + 1; i++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1 + w2 + w3 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; i < p1 + p2 + p3 + 1; i++)
		{
			arr[i][j] = 1;
		}
		do {
			w1 = rand() % rem + 1;
			w2 = rand() % rem + 1;
			w3 = rand() % rem + 1;
			w4 = rand() % rem + 1;
		} while (w1 + w2 + w3 + w4 != num - 3);

		do {
			p1 = rand() % rem + 1;
			p2 = rand() % rem + 1;
			p3 = rand() % rem + 1;
			p4 = rand() % rem + 1;
		} while (p1 + p2 + p3 + p4 != num - 2);
		for (j = 1; j < w1 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (i = 1; i < p1 + 1; i++)
		{
			arr[i][j] = 1;
		}
		for (; j < w1 + w2 + 1; j++)
		{
			arr[i][j] = 1;
		}
		for (; i < p1 + p2 + 1; i++)
		{
			arr[i][j] = 1;
		}
	
		do {
			w1 = rand() % rem + 1;
			w2 = rand() % rem + 1;
			w3 = rand() % rem + 1;
			w4 = rand() % rem + 1;
		} while (w1 + w2 + w3 + w4 != num - 3);
		
		do {
			p1 = rand() % rem + 1;
			p2 = rand() % rem + 1;
			p3 = rand() % rem + 1;
			p4 = rand() % rem + 1;
		} while (p1 + p2 + p3 + p4 != num - 2);
		for (j = 1; j < w1 + 1; j++)
		{
			arr[num-i-1][j] = 1;
		}
		for (i = 1; i < p1 + 1; i++)
		{
			arr[num - i - 1][j] = 1;
		}
		for (; j < w1 + w2 + 1; j++)
		{
			arr[num - i - 1][j] = 1;
		}
		for (; i < p1 + p2 + 1; i++)
		{
			arr[num - i - 1][j] = 1;
		}
		for (; j < w1 + w2 + w3 + 1; j++)
		{
			arr[num - i - 1][j] = 1;
		}
		for (; i < p1 + p2 + p3 + 1; i++)
		{
			arr[num - i - 1][j] = 1;
		}
		for (; j < w1 + w2 + w3 + w4 + 1; j++)
		{
			arr[num - i - 1][j] = 1;
		}
		for (; i < p1 + p2 + p3 + p4 + 1; i++)
		{
			arr[num - i - 1][j] = 1;
		}
}
void printmaze()
{
	system("cls");
	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < num; y++)
		{
			if (arr[x][y] == 0)
				printf("* ");
			else if (arr[x][y] == 1)
				printf("  ");
			else if (arr[x][y] == 2)
				printf("@ ");
		}
		printf("\n");
	}
}
void step()
{
	arr[1][1] = 2;
	int ran = 0, row = 0;
	printmaze();
	printf("w,a,s,d移动，走到右下角");
	do
	{
		int com = 0;
		scanf("%c", &com);
			switch (com)
			{
			case 'w':
				if (arr[1 + ran-1 ][1 + row] == 0)
					break;
				ran--;
				arr[1 + ran ][1 + row] = 2;
				arr[1 + ran+1][1 + row] = 1;
				printmaze();
				break;
			case 'a':
				if(arr[1 + ran][1 + row-1 ] ==0)
					break;
				row--;
				arr[1 + ran][1 + row ] = 2;
				arr[1 + ran][1 + row+1] = 1;
				printmaze();
				break;
			case 'd':
				if (arr[1 + ran][1 + row +1] == 0)
					break;
				row++;
				arr[1 + ran][1 + row ] = 2;
				arr[1 + ran][1 + row-1] = 1;
				printmaze();
				break;
			case 's':
				if (arr[1 + ran +1][1 + row] == 0)
					break;
				ran++;
				arr[1 + ran ][1 + row] = 2;
				arr[1 + ran-1][1 + row] = 1;
				printmaze();
				break;
			}

	} while (arr[num-2][num-2]!=2);
	printf("游戏结束\n");
}