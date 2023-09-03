#include<stdio.h>
int i = 1;//定义全局变量，每次调用后加1

int main()
{
    int n;
    char A = 'A'; //定义ABC表示三个柱子
    char B = 'B';
    char C = 'C';
    printf("Input the number of disks:");
    scanf("%d", &n);
    printf("Steps of moving %d disks from A to B by means of C:\n", n);
    Hanoi(n, A, B, C);

    return 0;
}

void Hanoi(int n, char A, char B, char C)
{

    if (n == 1)//如果只有一个直接从A移到B   "%2d-(%2d):%c==>%c\n"
    {
        printf("Move %d: from %c to %c\n", n, A, B);

    }
    else
    {
        Hanoi(n - 1, A, C, B);//把n - 1个从A移到C借助B

        printf("Move %d: from %c to %c\n", n, A, B);
        Hanoi(n - 1, C, B, A);//把n - 1个从C移到B借助A

    }

}