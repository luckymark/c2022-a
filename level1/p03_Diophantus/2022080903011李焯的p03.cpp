#include <stdio.h>
#include <stdlib.h>
int main()
{
	float year=18;
	for (year; year < 150; year++)
	{
		if ((1 / 6.0 + 1 / 12.0 + 1 / 7.0) * year + 5.0 + 4.0 == 1 / 2.0 * year)
		{
			printf("%d\n", (int)year - 4);
		}
	}
	system("pause");
	return 0;
}