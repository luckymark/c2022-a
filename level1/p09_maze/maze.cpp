#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<conio.h>
int map[5][10] = 
{ 0,0,0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,0,0,0,1,0,0,0,0,0
};//0是墙，1是空格（出口）,2表示人
int main()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 0)
            {
                printf("#");
            }
            else if(map[i][j] == 1)
            {
                printf(" ");
            }
            else if (map[i][j] == 2)
            {
                printf("*");
            }
        }
        printf("\n");
    }
    int line = 1, row = 1;//起点
    do
    {
        char action = _getch();
        if (action == 'w'&&line>1&& map[line][row]!=0)
        {
            line--;
            map[line+1][row] = 1;
            map[line][row] = 2;
        }
        else if(action =='s' && line <5 && map[line+1][row] != 0)
        {
            line++;
            map[line-1][row] = 1;
            map[line][row] = 2;
        }
        else if (action == 'a' && row > 1 && map[line][row] != 0)
        {
            row--;
            map[line][row+1] = 1;
            map[line][row] = 2;
        }
        else if (action == 'd' && row <10 && map[line][row+1] != 0)
        {
            row++;
            map[line][row-1] = 1;
            map[line][row] = 2;
        }
        system("cls");
        for (int i = 0; i < 5; i++)
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
            }
            printf("\n");
        }
       
        if (line == 4 && (row == 4 || row == 5))
        {
            printf("You win");
            break;
        }
    } while (1);
    system("pause");
    return 0;
}