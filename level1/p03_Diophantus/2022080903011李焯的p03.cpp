#include <stdio.h>
#include <stdlib.h>
int main()
{
	float x=18;
	for (x; x < 150; x++)
	{
		if ((1 / 6.0 + 1 / 12.0 + 1 / 7.0) * x + 5.0 + 4.0 == 1 / 2.0 * x)
		{
			printf("%d\n", (int)x - 4);
		}
	}
	system("pause");
	return 0;
}