/*����Ҫ��

1. ��������һ��������n
1. �ж�n�Ƿ�Ϊ����*/

#include<stdio.h>
int isPrime(int N);
int main()
{
	int N,k;
	printf("������һ����:");
	scanf_s("%d", &N);
	k=isPrime(N);
	if (k == 1)
		printf("%d��������", N);
	else
		printf("%d������",N);
}

