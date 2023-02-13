#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
int main(void)
{
    char map[50][50] = {
                        "######",
                        "#O #  ",
                        "# ## #",
                        "#  # #",
                        "##   #",
                        "######",
    };
    int i, x, y, p, q;
    int ch;
    x = 1; y = 1; p = 1; q = 5;
    printf("迷宫游戏\n");
    printf("操作方式:\nw为往上走\ns为往下走\na为往左走\nd为往右走\n");//因为很菜，不知道下方向健怎样读取，只能拙劣地使用传统游戏键位。
    for (i = 0; i < 6; i++)
        puts(map[i]);
    while (x != p || y != q)
    {
        ch = getchar();
        switch (ch)
        {
        case 's':
        {
            if (map[x + 1][y] != '#')
            {
                map[x][y] = ' ';
                x++;
                map[x][y] = 'O';
            }
        }break;
        case 'w':
        {
            if (map[x - 1][y] != '#')
            {
                map[x][y] = ' ';
                x--;
                map[x][y] = 'O';
            }
        }break;
        case 'a':
        {
            if (map[x][y - 1] != '#')
            {
                map[x][y] = ' ';
                y--;
                map[x][y] = 'O';
            }
        }break;
        case 'd':
        {
            if (map[x][y + 1] != '#')
            {
                map[x][y] = ' ';
                y++;
                map[x][y] = 'O';
            }
        }break;
        }
        system("cls");
        for (i = 0; i < 6; i++)
            puts(map[i]);
    }
    system("cls");
    printf("Congratulations！");
    Sleep(5000);
    return 0;
}