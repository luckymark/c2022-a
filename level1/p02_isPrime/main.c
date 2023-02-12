#include <stdio.h>
int main() {
    int x, i;
    printf("请输入一个素数");
    scanf_s("%d", &x);
    for (i = 2; i <= x; i++) {
        if (x % i == 0) break;
    }
    if (i == x) printf("该数是素数");
    else printf("该数不是素数");
    return 0;
}