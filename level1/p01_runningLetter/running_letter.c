#include"stdio.h"
#include"stdlib.h"
#include"windows.h"
#include"stdbool.h"

char LETTER = 'H';
int controler = 40;

void helper(int a) {
    system("cls");

    for (int b = 0; b < a; b++)
    {
        printf(" ");
    }

    printf("%s",&LETTER);
    Sleep(100);
}

void go_back() {
    int a = 0;
    bool goOrBack = TRUE;
    while (TRUE) {
        system("mode con cols=40 lines=10 ");
        helper(a);
        if (goOrBack) {
            if (a+1 == controler) goOrBack = FALSE;
            else a++;
        }
        else {
            if (a == 0) goOrBack = TRUE;
            else a--;
        }
    }
}

int main() {
    go_back();
    return 0;
}