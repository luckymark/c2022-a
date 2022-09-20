#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define SCREEN_WIDTH 120
int main()
{
	int n,i,k;
	n = 0;k = 1;
	while(1)
	{
		n = n+k;
		if(n == SCREEN_WIDTH || n == 0)
		{
			k = -k;
		}
		for(i = 1;i <= n;i++)
		{
			printf(" ");
		}
		printf("RUN!");
		Sleep(100);
		system("cls");
	}
}
