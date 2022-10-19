#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	double first, second, third, flower;
	int i;
	for (i = 100; i < 1000; i++)
	{
		first = i / 100;
		second = i / 10 - first * 10;
		third = i - first * 100 - second * 10;
		flower = pow(first, 3) + pow(second, 3)
			+ pow(third, 3);
		if (flower == i)
		{

			printf("%.0f\n", flower);
		}
	}
	system("pause");
}
