
#include<stdio.h>


int main()                                              
{
	printf("三位水仙花数有：\n");
	for (int a = 100; a < 1000; a++)
	{
		int b = a;
		int arr[3];
		arr[0] = b % 10;
		b /= 10;
		arr[1] = b % 10;
		b /= 10;
		arr[2] = b % 10;
		if (a == arr[0] * arr[0] * arr[0] + arr[1] * arr[1] * arr[1] + arr[2] * arr[2] * arr[2])
		{
			printf("%-4d", a);
		}
	}
	return 0;
}