#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i, j, k, l;
	for (i = 1; i < 10; i++)
		for (j = 0; j < 10; j++)
			for (k = 0; k < 10; k++)
			{
				l = 100 * i + 10 * j + k;
				if (l == i * i * i + j * j * j + k * k * k)
				{
					printf("%d\n", l);
				}
			}
	system("pause");
}