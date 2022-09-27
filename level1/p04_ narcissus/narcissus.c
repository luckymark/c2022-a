#include <stdio.h>
#include <stdlib.h>
int threetimes(int a)
{
    int ret;
    ret=a*a*a;
    return ret;
}
int main()
{
    
    for(int numb=100;numb<1000;numb++){
        int first=numb/100,second=numb/10%10,third=numb%10;
        if(numb==threetimes(first)+threetimes(second)+threetimes(third)){
            printf("%d\n",numb);
        }
    }
    system("pause");
    return 0;
}