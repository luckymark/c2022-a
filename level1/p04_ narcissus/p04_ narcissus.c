#include "stdio.h"
int main()
{
	int helper(num, n);
	for (int i = 100; i < 1000; i++)
	{
		if (helper(i % 10, 3) + helper(i % 100 / 10, 3) + helper(i / 100, 3) == i) {
			printf("%d ", i);
		}
	}
	return 0;
}
int helper(int num, int n)
{
	int res = num;
	for (int i = 1; i < n; i++)
	{
		res *= num;
	}
	return res;
}