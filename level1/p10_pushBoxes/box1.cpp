# define _CRT_SECURE_NO_WARNINGS 1
#include "box.h"
char arr[row][ran];



char ex;
void initializebox()
{
	memset(arr, 0, sizeof(arr));
	for (int x = 1; x < row-1; x++)
	{
		for (int y = 1; y < ran-1; y++)
		{
			arr[x][y] = 1;
		}
	}
	arr[1][2] = 0;
	arr[2][2] = 2;
	arr[3][2] = 0;
	arr[4][2] = 0;
	arr[6][2] = 3;
	arr[7][2] = 0;
	arr[7][3] = 0;
	arr[4][3] = 3;
	int y = 4;
	for (int x = 2; x < 6; x++)
		arr[x][y] = 0;
	arr[2][5] = 3;
	arr[5][5] = 4;
	arr[6][5] = 2;
	arr[7][5] = 0;
	arr[3][6] = 0;
	arr[3][7] = 0;
	arr[2][7] = 0;
	arr[4][7] = 2;
	arr[2][8] = 3;
	arr[7][8] = 0;
	arr[7][9] = 0;
	arr[5][9] = 2;
	arr[1][10] = 0;
	arr[2][10] = 0;
}
void meun()
{
	printf("*********推箱子*********\n");
	printf("*********1. 开始*********\n");
	printf("*********2. 结束*********\n");
}
void myprint()
{
	system("cls");
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y <ran; y++)
		{
			if (arr[x][y] == 0)
				printf("# ");
			/*else 
				printf("  ");*/
			else if (arr[x][y] == 1)
				printf("  ");
			else if (arr[x][y] == 2)
				printf("& ");
			else if (arr[x][y] == 5)
				printf("& ");
			else if (arr[x][y] == 3)
				printf("+ ");
			else if (arr[x][y] == 4)
				printf("$ ");
			else if (arr[x][y] == 6)
				printf("$ ");
		}
		printf("\n");
	}
}

void start()
{
	int n = 5, m = 5;
	printf("w,s,a,d移动, z退出\n");
	printf("$是角色，&是箱子，+是箱子目的地");
	while(!( arr[2][5] == 5&&arr[4][3]==5&&arr[6][2] == 5&&arr[2][8]== 5)){
		char com;
		com = _getch();
		switch (com)
		{
		case 'd': 
			void myprint();
			if (arr[n][m + 1] == 1)
			{
				if (arr[n][m] ==6)
				{
					arr[n][m] = 3;
					arr[n][m + 1] = 4;
					m += 1;
					myprint();
					break;
				}
				else {
					ex = arr[n][m];
					arr[n][m] = arr[n][m + 1];
					arr[n][m + 1] = ex;
					m += 1;
					myprint();
					break;
				}
			
				
			}
			if (arr[n][m + 1] == 2)
			{
				if (arr[n][m + 2] == 1)
				{
					ex = arr[n][m + 1];
					arr[n][m + 1] = arr[n][m + 2];
					arr[n][m + 2] = ex;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n][m + 1] = 4;
						m += 1;
						myprint();
						break;
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n][m + 1];
						arr[n][m + 1] = ex;
						m += 1;
						myprint();
						break;
					}
				
					
				}
				if (arr[n][m + 2] == 3)
				{
					arr[n][m + 1] = 1;
					arr[n][m + 2] = 5;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n][m + 1] = 4;
						m += 1;
						myprint();
						break;
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n][m + 1];
						arr[n][m + 1] = ex;
						m += 1;
						myprint();
						break;
					}
				
				}
			 }
			if (arr[n][m + 1] == 3)
			{
				arr[n][m + 1] = 6;
				arr[n][m ] = 1;
				m += 1;
				myprint();
				break;
			}
			myprint();
			break;
		case 's':
			if (arr[n+1][m ] == 1)
			{
				if (arr[n][m] == 6)
				{
					arr[n][m] = 3;
					arr[n+1][m ] = 4;
					n += 1;
					myprint();
					break;
				}
				else {
					ex = arr[n][m];
					arr[n][m] = arr[n + 1][m];
					arr[n + 1][m] = ex;
					n += 1;
					myprint();
					break;
				}
			

			}
			if (arr[n+1][m] == 2)
			{
				if (arr[n+2][m] == 1)
				{
					ex = arr[n+1][m];
					arr[n+1][m] = arr[n+2][m];
					arr[n+2][m] = ex;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n+1][m] = 4;
						n += 1;
						myprint();
						break;
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n+1][m];
						arr[n+1][m] = ex;
						n += 1;
						myprint();
						break;
					}
				

				}
				if (arr[n+2][m] == 3)
				{
					arr[n+1][m] = 1;
					arr[n+2][m] = 5;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n+1][m] = 4;
						n += 1;
						myprint();
						break;
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n+1][m];
						arr[n+1][m] = ex;
						n += 1;
						myprint();
						break;
					}
					
				}
			}
			if (arr[n+1][m ] == 3)
			{
				arr[n+1][m] = 6;
				arr[n][m] = 1;
				n += 1;
				myprint();
				break;
			}
			myprint();
			break;
			
		case 'w':
			void myprint();
			if (arr[n-1][m ] == 1)
			{
				if (arr[n][m] == 6)
				{
					arr[n][m] = 3;
					arr[n-1][m ] = 4;
					n -= 1;
					myprint();
					break;
				}
				else {
					ex = arr[n][m];
					arr[n][m] = arr[n-1][m];
					arr[n-1][m] = ex;
					n -= 1;
					myprint();
					break;
				}


			}
			if (arr[n-1][m ] == 2)
			{
				if (arr[n-2][m ] == 1)
				{
					ex = arr[n-1][m];
					arr[n-1][m] = arr[n-2][m];
					arr[n-2][m] = ex;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n-1][m] = 4;
						n -= 1;
						myprint();
						break;
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n-1][m];
						arr[n-1][m] = ex;
						n -= 1;
						myprint();
						break;
					}


				}
				if (arr[n-2][m ] == 3)
				{
					arr[n-1][m] = 1;
					arr[n-2][m] = 5;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n-1][m] = 4;
						n -= 1;
						myprint();
						break;
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n-1][m];
						arr[n-1][m] = ex;
						n -= 1;
						myprint();
						break;
					}

				}
			}
			if (arr[n-1][m] == 3)
			{
				arr[n-1][m] = 6;
				arr[n][m] = 1;
				n -= 1;
				myprint();
				break;
			}
			myprint();
			break;
		
		case 'a':
			void myprint();
			if (arr[n][m - 1] == 1)
			{
				if (arr[n][m] == 6)
				{
					arr[n][m] = 3;
					arr[n][m - 1] = 4;
					m -= 1;
					myprint();
					break;
				}
				else {
					ex = arr[n][m];
					arr[n][m] = arr[n][m - 1];
					arr[n][m - 1] = ex;
					m -= 1;
					myprint();
					break;
				}


			}
			if (arr[n][m - 1] == 2)
			{
				if (arr[n][m - 2] == 1)
				{
					ex = arr[n][m - 1];
					arr[n][m - 1] = arr[n][m - 2];
					arr[n][m - 2] = ex;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n][m - 1] = 4;
						m -= 1;
						myprint();
						break;
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n][m - 1];
						arr[n][m - 1] = ex;
						m -= 1;
						myprint();
						break;
					}


				}
				if (arr[n][m - 2] == 3)
				{
					arr[n][m - 1] = 1;
					arr[n][m - 2] = 5;
					if (arr[n][m] == 6)
					{
						arr[n][m] = 3;
						arr[n][m - 1] = 4;
						m -= 1;
						myprint();
						break;
						
					}
					else {
						ex = arr[n][m];
						arr[n][m] = arr[n][m - 1];
						arr[n][m - 1] = ex;
						m -= 1;
						myprint();
						break;
					}

				}
			}
			if (arr[n][m - 1] == 3)
			{
				arr[n][m - 1] = 6;
				arr[n][m] = 1;
				m -= 1;
				myprint();
				break;
			}
			myprint();
			break;
		case 'z':
			arr[2][5] = 5;
			arr[4][3] = 5;
			arr[6][2] = 5;
			arr[2][8] = 5;
		}




	}
	printf("游戏结束\n");

}