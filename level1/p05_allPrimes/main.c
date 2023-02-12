#include <stdio.h>
#include <time.h>
#include <math.h>

int main() {
    int i ,j,a;
    clock_t start_t,finish_t;
    double duration_t;
    start_t=clock();
    for(i=2;i<1000;i++ ){
        a=1;
        for(j=2;j<=sqrt(i);j++)

        {
        if (i%j==0&&i!=j){
            a=0 ;break;}
        }
        if(a==1) printf("%d\t",i);
    }
    finish_t=clock();
    duration_t=(double)(finish_t-start_t)/ CLOCKS_PER_SEC;;
    printf("总的计算时间为",duration_t);

    return 0;
}
