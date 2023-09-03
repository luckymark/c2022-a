#include<stdio.h>
#include<math.h>

int prime(int n);
int Goldbach(int n);

int main()
{
    int n;
    scanf("%d",&n);
    Goldbach(n);
    return 0;
}

int prime(int n)//use in if() version
{
    int a,i;
    a = sqrt((double)n);
    for(i = 2;i <= a;i++)
    {
        if(n%i == 0)
        {
            break;
        }
    }
    if(i == a+1)
    {
        return n;
    }else return 0;
}

int Goldbach(int n){
    int p = 2,q,a;
    if(n >= 4 && n <=2000 && n%2 == 0){
        for(;p <= n;p++){
            if(prime(p) == 0)
            {
                a = 0;
            }else a = 1;
            if(a)
            {
                q = n - p;
                if(prime(q) == 0)
                {
                    a = 0;
                }
            }
            if(a)
            {
                printf("%d %d",p,q);
                break;
            }
        }
    }else printf("error");
}