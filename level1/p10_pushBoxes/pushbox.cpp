#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<conio.h>
int map[10][10] =
{ 0,0,0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,3,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,0,0,0,1,0,0,0,0,0,
};//0是墙，1是空格（出口）,2表示人,3表示箱子
int main()
{
    for (int i = 0; i <10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 0)
            {
                printf("#");
            }
            else if (map[i][j] == 1)
            {
                printf(" ");
            }
            else if (map[i][j] == 2)
            {
                printf("*");
            }
            else if (map[i][j] == 3)
            {
                printf("-");
            }
        }
        printf("\n");
    }
    int line = 2, row = 1;//起点
    do
    {
        char action = _getch();
        if (action == 'w' && line > 1&& map[line - 1][row] != 0)
        {
            line--;
            if(map[line][row] == 3)
            {
                map[line - 1][row] = 3;
            }
            map[line + 1][row] = 1;
            map[line][row] = 2;
        }
        else if (action == 's' && line < 8 && map[line + 1][row] != 0)
        {
            line++;
            if (map[line][row] == 3)
            {
                map[line + 1][row] = 3;
            }
            map[line - 1][row] = 1;
            map[line][row] = 2;
        }
        else if (action == 'a' && row > 1 && map[line][row-1] != 0)
        {
            row--;
            if (map[line][row] == 3)
            {
                map[line][row - 1] = 3;
            }
            map[line][row + 1] = 1;
            map[line][row] = 2;
        }
        else if (action == 'd' && row < 8 && map[line][row + 1] != 0)
        {
            row++;
            if (map[line][row] == 3)
            {
                map[line][row + 1] = 3;
            }
            map[line][row - 1] = 1;
            map[line][row] = 2;
        }
        system("cls");
        for (int i = 0; i < 10; i++)
        {
            if (map[i][8] == 3|| map[i][1] == 3||((map[9][i] == 3) && i != 4)|| map[1][i] == 3)
            {
                printf("You lose");
                exit(0);
            }
           
        }
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (map[i][j] == 0)
                {
                    printf("#");
                }
                else if (map[i][j] == 1)
                {
                    printf(" ");
                }
                else if (map[i][j] == 2)
                {
                    printf("*");
                }
                else if (map[i][j] == 3)
                {
                    printf("-");
                }
            }
            printf("\n");
        }
        if (map[9][4] == 3)
        {
            printf("You win");
            break;
        }
    } while (1);
    system("pause");
    return 0;
}