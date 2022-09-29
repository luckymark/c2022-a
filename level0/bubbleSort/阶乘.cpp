#include<stdio.h>
int factorial(int num)
{
	if(num<=1)
	return 1;
	else
	return num*factorial(num-1);
}

int main()
{
	int num,answer;
	scanf("%d",&num);
	answer=factorial(num);
	printf("%dµÄ½×³ËÎª%d",num,answer);
	return 0;
}
