#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define SCREEN_WIDTH 120
int main()
{
	int n,i,k,j,L,m;
	n = 0;k = 1;
	j = SCREEN_WIDTH-1;L = -1;
	while(1)
	{
		n = n+k;						//输出向右跑的小人
		if(n == SCREEN_WIDTH || n == 0)
		{
			k = -k;
		}
		for(i = 1;i <= n;i++)
		{
			printf(" ");
		}
		printf(" O\n");
		
		for(i = 1;i <= n;i++)
		{
			printf(" ");
		}
		printf("<H>->\n");
		
		for(i = 1;i <= n;i++)
		{
			printf(" ");
		}
		printf("I I\n");
		
		
		
		j = j+L;							//输出向左跑的小人 
			if(j == SCREEN_WIDTH || j == 0)
		{
			L = -L;
		}
		for(m = 1;m <= j;m++)
		{
			printf(" ");
		}
		printf("  O\n");
		for(m = 1;m <= j;m++)
		{
			printf(" ");
		}
		printf("[-<H>\n");
		for(m = 1;m <= j;m++)
		{
			printf(" ");
		}
		printf("  I I");
		
		
		Sleep(100);
		system("cls");
	}
}
