#include <stdio.h>
#include<math.h>
//哥德巴赫猜想：任一大于2的偶数都可写成两个素数之和
void prime(int sushu[]);
int bijiao(int j, int sushu[]);

int main() {

    int h=4, k;
    int sushu[100] = { 0 };
    prime(sushu);
    while(h < 101) {
        for (k = 0; sushu[k] > 0; k++)
            if (bijiao(h - sushu[k], sushu))
            {
                printf("%d=%d+%d\n", h, sushu[k], h - sushu[k]); break;
            }

        h += 2;
    }
    if (sushu[k] == 0)
    {
        printf("error");
    }

    return 0;
}
void prime(int sushu[])
{
    int n = 3,  a, x = 0;
    while (n < 100) {
        sushu[0] = 2;
        a = 1;
        for (int i=0 ; sushu[i] < sqrt(n); i++) {
            if (n % sushu[i] == 0)
            {
                a = 0;
                break;
            }

        }
        if (a) {
            sushu[x + 1] = n;
            x += 1;
        }
        n += 2;
    }
}
int bijiao(int j, int a[]) {
    int bijiao = 0;
    for (int l = 0; a[l] > 0; l++)
    {
        if (j == a[l])
        {
            bijiao = 1;
        }
    }
    return bijiao;
}