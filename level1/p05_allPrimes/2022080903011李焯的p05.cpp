#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main()
{
	int i, j, count = 0;
	printf("2 3 ");
	clock_t t1, t2;
	t1 = clock();
			for (i = 4; i <= 1000; i++)	
			{
				count = 0;
				for (j = 2; j <= sqrt((double)i); ++j)
				{
					if (i % j == 0)
					{
						count = 1;
						break;
					}
				}
				if (count == 0)
				{
					printf("%d ", i);
					continue;
				}
			}
			t2 = clock();
			printf("\ntime: %d\n",t2 - t1);
	system("pause");
	return 0;
}