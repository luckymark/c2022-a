#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main()
{
    while (1) {
        int i, j, m, n, lucky, LENTH;
        LENTH = 110;
        for (i = 0; i < LENTH; i++)
        {
            for (j = 0; j < i; j++)
            {
                printf(" ");
            };
            printf("lucky");
            Sleep(10);
            system("cls");
        }
        for (int m = LENTH; m > 0; m--)
        {
            for (int n = 0; n < m; n++)
            {
                printf(" ");
            };
            printf("lucky");
            Sleep(10);
            system("cls");
        }
    }



}





