#include <stdio.h>

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("%c -> %c\n", from, to);
    }
    else {
        hanoi(n - 1, from, aux, to);
        printf("%c -> %c\n", from, to);
        hanoi(n - 1, aux, to, from);
    }
}

int main() {
    int n = 64; // Ô²ÅÌÊıÁ¿
    hanoi(n, 'A', 'C', 'B');
    return 0;
}
