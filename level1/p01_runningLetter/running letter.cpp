#include<stdio.h>
#include<stdlib.h>
#define  SCREEN_WIDTH 100 
int main()
{
	int step,single,i;
	const int SCREEN_WIDE = 100;//
	step= 0;
	single = 1;
	while (1)
	{
		step += single;
		if (step == SCREEN_WIDE || step== 0)
		{
			single = -single;
		}
		for (i = 1; i <= step; i++)
		{
			printf(" ");
		}
		printf("runrunrun");
		system("cls");

	}
}