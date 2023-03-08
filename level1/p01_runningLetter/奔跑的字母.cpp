#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
	int a,b;
	a=1;
	
	while(a<=100)
	{
		
		system("cls");
		
		b=1;
		while(b<=a)
		{
			
			printf("  ");
			b++; 
			
		}
		printf("H");
		Sleep(1);
		a++;
		
    }
	/*printf("H");
	Sleep(1000);
	
	system("cls");
	printf("  H");
	Sleep(1000);
	
	system("cls");
	printf("    H");
	Sleep(1000);
 
 	system("cls");
	printf("       H");
	Sleep(1000);*/


	
	return 0;
} 
