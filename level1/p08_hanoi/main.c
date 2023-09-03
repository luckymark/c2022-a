#include <stdio.h>

void move(char A, char C) {//执行最大盘子n的从A-C的移动
    printf("%c -> %c\n",A,C);
}
void hanoi(int n, char A, char B, char C) {
    if (n == 1)
        move(A, C);
    else {
        hanoi(n - 1, A, C, B);//将n-1个盘子由A经过C移动到B
        move(A, C);             //执行最大盘子n移动
        hanoi(n - 1, B, A, C);//剩下的n-1盘子，由B经过A移动到C
    }
}

int main() {
    printf("移动汉诺塔的步骤：\n");
    hanoi(64, 'A', 'B' ,'C');
}
