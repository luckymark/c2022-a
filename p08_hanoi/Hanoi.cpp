#include <stdio.h>
int main()
{
    int hanoi(int, char, char, char);
    int n, counter;
    printf("Input the number of diskes：");
    scanf_s("%d", &n);
    printf("\n");
    counter = hanoi(n, 'A', 'B', 'C');
    return 0;
}

int hanoi(int n, char x, char y, char z)
{
    int move(char, int, char);
    if (n == 1)
        move(x, 1, z);
    else
    {
        hanoi(n - 1, x, z, y);
        move(x, n, z);
        hanoi(n - 1, y, x, z);
    }
    return 0;
}

int move(char getone, int n, char putone)
{
    static int k = 1;
    printf("%2d:%3d # %c-->%c\n", k, n, getone, putone);
    if (k++ % 3 == 0)
        printf("\n");
    return 0;
}