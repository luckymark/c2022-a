#include <stdio.h>
//C target
void move(char x, char y) {
    printf("%c -> %c\n", x, y);
}
void hanoi(int n, char a, char b, char c) {
    if (n == 1) {
        move(a, c);
    }
    else {
        //利用c，把a的n-1个圆盘移到b上
        hanoi(n - 1, a, c, b);
        move(a, c);
        //利用a，把b的n-1个圆盘移到c上
        hanoi(n - 1, b, a, c);
    }
}
int main() {
    int n;
    scanf_s("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}