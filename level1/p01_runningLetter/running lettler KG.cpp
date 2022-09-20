#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
    int n = 0, SINGLE = 1, i = 1;
    const int SCREEN_LENGTH = 108;//屏幕长度
    while (1)
    {
        n = n + SINGLE;
        if (n == SCREEN_LENGTH || n == 0)
        {
            SINGLE = -SINGLE;//屏幕转向
        }
        for (i = 1; i <= n; i++)
        {
            printf(" ");//前置空格
        }
        printf("helloworld \n");
        Sleep(105);
        system("cls");
    }
}
