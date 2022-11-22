#include <stdio.h>

int isPrime(int integer)
{
   int num=0;
   	for(int i=2;i<integer;i++)
   	{
   		if(integer%i==0)
   		num++;
   	}
   	if(num!=0)
   	return 0;
   	else
   	return 1;
}

void fun(int num)
{
    int i,j;
    for(i=2;i<num; i++)
		{
            for(j=3;j<(num-i);j++)
               {
			   	if(isPrime(j) && isPrime(i) && isPrime(num-i-j))
					printf("%d=%d+%d+%d\n",num,i,j,num-i-j);
			   }
        }
}

int main()
{
    int num;
    scanf("%d", &num);
    fun(num);
    return 0;
}
 
