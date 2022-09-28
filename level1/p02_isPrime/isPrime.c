#include <stdio.h>
#include <stdlib.h>
int main()
{
    printf("请输入一个正整数：\n");
    int a=1;
    scanf("%d",&a);
    for(int i=1;i<a;i++)
    {
        if(a%i==0){
            printf("不是素数\n");
            break;
        }
        if(i==a){
        printf("是素数");
    }
    
    }
    system("pause");
    return 0;
}