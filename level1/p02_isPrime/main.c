#include <stdio.h>
int main() {
    int x, i;
    printf("������һ������");
    scanf_s("%d", &x);
    for (i = 2; i <= x; i++) {
        if (x % i == 0) break;
    }
    if (i == x) printf("����������");
    else printf("������������");
    return 0;
}