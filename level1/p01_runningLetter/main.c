#include"stdio.h"
#include"stdlib.h"
#include"Windows.h"
int main() {
    int i = 1;
    int a = 0;
    while (1)
    {
        system("mode con cols=40 lines=10 ");
        if (i == 1)
        {
            for (a; a < 39; a++)
            {
                system("cls");

                for (int b = 0; b <= a; b++)
                {
                    printf(" ");
                }

                printf("H");
                Sleep(100);
            }
        }
        else
        {
            for (a = 37; a >= 0; a--)
            {
                system("cls");

                for (int b = 0; b <= a; b++)
                {
                    printf(" ");
                }

                printf("H");
                Sleep(100);
            }
        }
        i *= -1;
    }

    return 0;
}