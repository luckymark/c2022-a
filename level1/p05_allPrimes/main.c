#include <stdio.h>
#include <time.h>


int begin,end,prime;;

int main() {
    begin=clock();
    printf("������:\n");
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
    printf("�˴����й���%dms\n",end-begin);
    return 0;
}
