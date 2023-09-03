#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int isPrime(int x,int Primes[],int KnownPrimes);
int main()
{   
    const int numb=1000;
    int Primes[numb]={2};
    int count=1;
    int i=3;
    clock_t start,finish;
    start=clock();
    while(i<1000){
        if(isPrime(i,Primes,count )==1){
            Primes[count++]=i;
        }
        i++;
    }
    for(int i=0;i<count;i++){
        printf("%d\n",Primes[i]);
    }
    finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    printf("共用%lf秒\n",time);
    system("pause");
    return 0;
}
int isPrime(int x,int Primes[],int count)
{
    int ret=1;
    for(int i=0;i<count;i++){
        if(x%Primes[i]==0){
            ret=0;
            break;
        }
    }
    return ret;
}