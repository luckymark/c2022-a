#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
	int stage = 1;
	int pace = 1;
	while (1)
	{
		for (int i = 0; i <= stage; i++)
			printf(" "); 

		if (stage == 80 || stage == 0)
			pace = -pace;
			
		stage += pace;
		printf("hello world");
		Sleep(100);
		system("cls");
	}
	 return 0;
	
}



