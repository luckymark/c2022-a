#include"stdio.h"
#include"stdlib.h"
#include"windows.h"
#include"stdbool.h"
void helper(int a) {
    system("cls");

    for (int b = 0; b <= a; b++)
    {
        printf(" ");
    }

    printf("H");
    Sleep(100);
}
int main() {
    bool goOrBack = TRUE;
    int a = 0;
    while (1)
    {
        system("mode con cols=40 lines=10 ");
        if (goOrBack)
        {
            for (a; a < 39; a++)
            {
                helper(a);
            }
            goOrBack = FALSE;
        }
        else
        {
            for (a = 37; a >= 0; a--)
            {
                helper(a);
            }
            goOrBack = TRUE;
        }
        
    }

    return 0;
}