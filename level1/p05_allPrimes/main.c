#include <stdio.h>
#include <time.h>


int begin,end,prime;;

int main() {
    begin=clock();
    printf("素数有:\n");
    for(prime=2;prime<=1000;prime++)
    {
        for (int time = 2; time <= prime; ++time) {
            if (prime % time == 0)
            if (time == prime)
                printf("%d\n", prime);
                else
                break;
        }
    }
    end=clock();
    printf("此次运行共用%dms\n",end-begin);
    return 0;
}
