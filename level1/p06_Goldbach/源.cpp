/* 在100范围内验证哥德巴赫猜想的正确性*/

#include <stdio.h>
#include <math.h>

#define N 100

void SeparateEven(int n); //将n分成两个素数的和
void prime(int n); //判断素数

int isPrime[N + 1];

int main()
{
	int a, b;

	scanf_s("%d%d", &a, &b);
	if (a % 2 != 0)
		a++;
	prime(N); //调用筛选素数函数

	for (int i = a; i <= b; i += 2)
		SeparateEven(i); //将i表示为两个素数之和 

	return 0;
}

// 将n表示为两个素数之和 
void SeparateEven(int n)
{
	for (int i = 3; i <= n / 2; i++)
		if (isPrime[i] && isPrime[n - i]) //若两个加数都是素数，则输出n的拆分 
		{
			printf("%d = %d + %d\n", n, i, n - i);
			break;
		}
}


// 筛选从2到n之间的素数，筛选结果存入数组 isPrime 
void prime(int n)
{
	for (int i = 0; i <= n; i++)
		isPrime[i] = 1; //将isPrime数组元素初始化为1 

	isPrime[0] = isPrime[1] = 0; //0和1不是素数 
	int temp = (int)sqrt(n);

	for (int i = 2; i <= temp; i++)
		if (isPrime[i]) //筛去素数的整数倍 
			for (int j = 2 * i; j <= n; j += i)
				isPrime[j] = 0;
}
