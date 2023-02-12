#include <stdio.h>

int main() {
    int i,a,b,c;
    printf("水仙花数有：\n");
    for(i=100;i<1000;i++)

    {
        a=(i%10);
        b=(i/10%10);
        c=(i/100);

        if (a*a*a+b*b*b+c*c*c==i)
            printf("%d\n",i);
    }
    return 0;
}
