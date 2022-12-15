#include<stdio.h>
#include<math.h>
int judge(int x)
{
	int a = 0;
	for (int i = 2; i <= sqrt(x); i++)
	{
		if (x % i == 0)
			return 0;
	}
	return 1;
}
int main()
{
	int n, a, b,x;
	scanf_s("%d", &n);
	b = n;
	x = 0;
	int arr[304];
	if (n >= 4&&n<=2000)
	{
		for (int i = 1; i < n; i++)
		{
			if (judge(i) == 1)
			{
				arr[x] = i;
				x++;
			}
		}
		for (a = 0; a < x; a++)
		{
			for (b = 0; b < x; b++)
			{
				if (arr[a] + arr[b] == n)
				{
					printf("%d %d", arr[a], arr[b]);
					return 0;
				}
			}
		}
	}
	return 0;
}