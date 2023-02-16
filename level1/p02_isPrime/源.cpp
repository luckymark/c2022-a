/*功能要求：

1. 任意输入一个正整数n
1. 判断n是否为素数*/

#include<stdio.h>
int isPrime(int N);
int main()
{
	int N,k;
	printf("请输入一个数:");
	scanf_s("%d", &N);
	k=isPrime(N);
	if (k == 1)
		printf("%d不是素数", N);
	else
		printf("%d是素数",N);
}

