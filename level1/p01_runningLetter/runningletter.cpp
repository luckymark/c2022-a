#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
	int time=1;
	while(1)
	{	
		for(int i=1;i<=time;i++)
		{
			printf(" ");
			Sleep(0.001);
		}
		putchar('b');
		Sleep(120);
		system("cls");
		time++;
		if(time==119)
		{	
			for(;time>=1;time--)
			{
				for(int i=time;i>=1;i--)
				{
					printf(" ");
					Sleep(0.001);
				}
				putchar('b');
				Sleep(120);
				system("cls");
			}
		}
	}
}
