#include <stdio.h>

void move(char A, char C) {//ִ���������n�Ĵ�A-C���ƶ�
    printf("%c -> %c\n",A,C);
}
void hanoi(int n, char A, char B, char C) {
    if (n == 1)
        move(A, C);
    else {
        hanoi(n - 1, A, C, B);//��n-1��������A����C�ƶ���B
        move(A, C);             //ִ���������n�ƶ�
        hanoi(n - 1, B, A, C);//ʣ�µ�n-1���ӣ���B����A�ƶ���C
    }
}

int main() {
    printf("�ƶ���ŵ���Ĳ��裺\n");
    hanoi(64, 'A', 'B' ,'C');
}
