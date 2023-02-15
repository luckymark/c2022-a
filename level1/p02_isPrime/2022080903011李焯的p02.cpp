#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int n, i, count;
    count = 1;
    scanf_s("%d", &n);
    if (n <= 0)
        printf("error");

    else if (n == 1)
        printf("no");
    if (n == 2)
        printf("yes");
    if (n == 3)
        printf("yes");
        if (n > 3)
    {
        for (i = 2; i <= sqrt(float(n)); ++i)
            if (n % i == 0)
            {
                count = 0;
                break;
            }
        if (count == 0)
            printf("no");
        else
            printf("yes");
    }
    return 0;
}
