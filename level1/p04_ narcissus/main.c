#include <stdio.h>
#include <math.h>

int main() {
    int number;
    printf("水仙花数有\n");
    for (number = 100; number  < 1000; ++number)
    {
        if(pow(number/100,3) + pow((number%100)/10,3) + pow((number%100)%10,3) == number)
            printf("%d\n",number);
    }

    return 0;
}
