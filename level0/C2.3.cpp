//此程序将无限输出绿色的1000以内随机数 
#include<stdio.h>
#include<stdlib.h> 
int main()
{
	system("color 0a");
	while(1){
		printf("%d\t",rand()/1000);
    }
    return 0 ;
}
