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
        //����c����a��n-1��Բ���Ƶ�b��
        hanoi(n - 1, a, c, b);
        move(a, c);
        //����a����b��n-1��Բ���Ƶ�c��
        hanoi(n - 1, b, a, c);
    }
}
int main() {
    int n;
    scanf_s("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}