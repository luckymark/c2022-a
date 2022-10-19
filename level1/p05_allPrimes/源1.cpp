#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main()
{
	clock_t t1, t2;
	int num, i, n = 1;
	float num1;
	t1 = clock();
	for (num = 2; num < 1000; num++)
	{
		num1 = sqrt(float(num));
		for (i = 2; i <= num1; ++i)
		{

			if (num % i == 0)
			{
				n = 0;
				break;

			}
			else
				n = 1;
		}
		if (n == 1)
			printf("%d\n", num);

	}
	t2 = clock();
	printf("%d ms", t2 - t1);
	system("pause");

}
