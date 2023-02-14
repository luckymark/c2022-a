#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
bool isPrime(int);
int main()
{
    int n, count=1;
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
        if (isPrime(n))
            printf("yes");
        else
            printf("no");
    }
    return 0;
}
bool isPrime(int n) {
    for (int i = 2; i <= sqrt(float(n)); ++i) 
    {
        if (n % i == 0)       
            return false;
    }
    return true;
}
