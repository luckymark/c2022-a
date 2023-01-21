#include <stdio.h>

char map(char a[15][15]) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            a[1][i] = '|';
            a[j][1] = '__';
        }
    }
    return a;
}

int main() {
    char Map[15][15];
    map(Map);
    printf("%c\n",Map[15][15]);
    return 0;
}



