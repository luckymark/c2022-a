#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()                                     //第六个作业
{
	static int oushu = 4;
	int arr[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,93,97 };
	int size = sizeof(arr) / sizeof(arr[0]);
	for (; oushu <= 100; oushu += 2)
	{
		for (int a = 0; a < size; a++)
		{
			for (int b = 0; b < a; b++)
			{
				if (oushu == arr[a] + arr[b])
				{
					printf("%d=%d+%d\n", oushu, arr[b], arr[a]);
				}
			}
		}
	}
	return 0;
}