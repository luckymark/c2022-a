#include<stdio.h>
#include<time.h>
#include<math.h>
# define _CRT_SECURE_NO_WARNINGS 1
int isprime(int num)
{
	int i = 0;
	if (num <= 3)
		return 1;
	if (num % 6 != 1 && num % 6 != 5)
		return 0;
		for (i = 5; i < (int)sqrt(num); i+=6)
		{
			if (num % i == 0 || num % i + 2 == 0)
				return 0;
		}
		return 1;
}
int main()
{
	int  num = 0;
	clock_t start = 0, finish = 0;
	double time = 0;
	start = clock();
	for (num = 2; num < 1000; num++)
		if (isprime(num))
			printf("%d\n", num);
	finish = clock();
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	printf("%fms", time);
	return 0;
}