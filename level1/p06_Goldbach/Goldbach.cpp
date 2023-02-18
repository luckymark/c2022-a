#include<stdio.h>
#include<math.h>

int main()
{
	int prime[100];
	int cont = 0;
	prime[cont] = 2;
	int num1 = 0, num2 = 0, num3 = 0;
	int jump = 0;

	//找到2到100以内所有的素数,并存在prime数组中
	for (int num = 2; num <= 100; num++)
	{
		int i = 2;
		for (i = 2; i <= float(sqrt(num)); i++)
		{
			if (num % i == 0)
			{
				break;
			}
		}
		if (i > float(sqrt(num)))
		{
			prime[cont] = num;
			cont++;
		}
	}

	for (int i = 6; i <= 100; i++)
	{
		if (i % 2 == 0)
		{
			num3 = 2;

			int inew = i-2;
			for (int j = 0; prime[j] < inew; j++)
			{
				for (int k = 0; prime[k] < inew; k++)
				{
					if (prime[j] + prime[k] == inew)
					{
						num1 = prime[k];
						num2 = prime[j];
						jump=1;
						break;
					}
				}
				if (jump == 1)
				{
					jump = 0;
					break;
				}
			}
		}
		else
		{
			for (int j = 0; prime[j] < i; j++)
			{
				for (int k = 0; prime[k] < i; k++)
				{
					for (int n=0;prime[n]<i;n++)
					if (prime[j] + prime[k]+prime[n] == i)
					{
						num1 = prime[n];
						num2 = prime[k];
						num3 = prime[j];
						jump = 1;
						break;
					}
				}
				if (jump == 1)
				{
					jump = 0;
					break;
				}
			}
		}
		printf("%d=%d+%d+%d\n", i, num1, num2, num3);
	}


	return 0;
}