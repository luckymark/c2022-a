#include<stdio.h>
#include<math.h>
#include<time.h>
int main()
{
	clock_t start, finish;
	double duration;
	printf("2\n");
	int number,i;
	number = 3;
	start = clock();
	while (number<=997)
	{
		
		if (number % 2 == 0)
		{
			number++;
			continue;
		}
		for (i = 2; i <= sqrt((float)number); i++)
		{
			
			if (number % i == 0)
				break;
		}
	
		if (i > sqrt((float)number))
			printf("%d\n", number);
		number++;

	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("the time is ==%lf seconds\n", duration);
	return 0;

}