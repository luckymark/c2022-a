#include<stdio.h>

int main()
{
	float a, b;

	for (a = 30; a++;)
	{
		if (a / 6 + a / 12 + a / 7 + 5 + a / 2 + 4 == a)
		{
			b = a / 6 + a / 12 + a / 7 + 5;
			printf("Diophantus was %d when hi got married \n", (int)b);
		}
	}
	return 0;
}
