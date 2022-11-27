#include<stdio.h>
#include<windows.h>
#include<math.h>
#include<stdlib.h>
int isprime(int a)
{
	int result,i=2;

	while (i <= sqrt((double)a))
	{
		if (a % i == 0)
		{
			result = 0;
			break;
		}
		i++;
	}
	if (i > sqrt((double)a))
		result = 1;
	return result;

}
int main()
{	
	int x,left,right, i = 0;
	scanf_s("%d", &x); 
	while (x <= 1000)
	{	
		
		
		if (x % 2 != 0)
		{
			printf("errror");
			break;
		}
		
		left = x / 2 - i;
		right = x / 2 + i;
		if ((isprime(left) == 1) && (isprime(right)==1))
		{
			printf("%d和%d两个素数之和%d", left, right);
			break;

		}
		i++;
	}

	return 0;
}