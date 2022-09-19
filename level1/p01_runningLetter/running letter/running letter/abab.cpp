#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
    int length, b;
    length = 1;
    while (length <= 100)
    {
        b = 1;
        system("cls");
        while (b <= length)
        {
            printf(" ");
            b = b + 1;

        }
        printf("H");
        Sleep(10);
        length = length +1;

    }

    length = 100;
    while (length >= 1)
    {
        b = 1;
        system("cls");
        while (b <= length)
        {
            printf(" ");
            b = b + 1;

        }
        printf("H");
        Sleep(10);
        length = length -1;

    }

    return 0;
}