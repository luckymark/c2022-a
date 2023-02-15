#include <stdio.h>
#include <stdlib.h>
int main()
{
	float age = 18;
	for (age; age < 150; age++)
	{
		if ((1 / 6.0 + 1 / 12.0 + 1 / 7.0) * age + 5.0 + 4.0 == 1 / 2.0 * age)
		{
			printf("%d\n", (int)age - 4);
		}
	}
	system("pause");
	return 0;
}