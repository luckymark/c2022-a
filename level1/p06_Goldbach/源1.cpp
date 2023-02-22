#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

const int X = 100;

int quiz(int n)
{
	for (int i = 2; i < sqrt(float(n)); i++)
	{
		int flag = 1;
		if (n % i == 0)
		{
			flag = 0;
		}
		if (flag == 1)
			return 1;
		if (flag == 0)
			return 0;
	}
}


int main()
{
	int flag = 0;
	for (int i = 4; i < X; i += 2)
	{
		for (int j = 2; j < i - 1; j++)
		{
			if (quiz(j) && quiz(i - j))
			{
				flag = 1;
			}
		}
	}
	if (flag == 0) {
		printf("证伪");
	}
	else if (flag == 1) {
		printf("证明为真");
	}
}
