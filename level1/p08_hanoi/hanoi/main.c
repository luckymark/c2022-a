#include<stdio.h>

void hanoi(int n, char A, char b, char C);
void move(int x,int y);

int main()
{
    int n = 0;
    printf("input the layer of the hanoi tower\n");
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}

void move(int x, int y)
{
    printf("%c->%c\n", x, y);
}

void hanoi(int n, char A, char B, char C)
{
    if (n == 1)
    {
        move(A, C);
    }
    else
    {
        hanoi(n - 1, A, C, B);
        move(A, C);
        hanoi(n - 1, B, A, C);
    }
}
