#include<stdio.h>
#include<math.h>
using namespace std;

int num = 0, hundred = 1, tens = 0,one=0;

int main(void)
{
	printf("All the 3-digit narcissus numbers are:\n");
	for (int num = 100; num < 1000; num++)
	{
		one = num % 10;
		tens = num /10 %10;
		hundred = num / 100;
		if ((hundred * hundred * hundred + tens * tens * tens + one * one * one) == num)
		{
			printf("%d\n", num);
		}
	}
	return 0;
}

