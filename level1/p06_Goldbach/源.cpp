/* ��100��Χ����֤��°ͺղ������ȷ��*/

#include <stdio.h>
#include <math.h>

#define N 100

void SeparateEven(int n); //��n�ֳ����������ĺ�
void prime(int n); //�ж�����

int isPrime[N + 1];

int main()
{
	int a, b;

	scanf_s("%d%d", &a, &b);
	if (a % 2 != 0)
		a++;
	prime(N); //����ɸѡ��������

	for (int i = a; i <= b; i += 2)
		SeparateEven(i); //��i��ʾΪ��������֮�� 

	return 0;
}

// ��n��ʾΪ��������֮�� 
void SeparateEven(int n)
{
	for (int i = 3; i <= n / 2; i++)
		if (isPrime[i] && isPrime[n - i]) //�������������������������n�Ĳ�� 
		{
			printf("%d = %d + %d\n", n, i, n - i);
			break;
		}
}


// ɸѡ��2��n֮���������ɸѡ����������� isPrime 
void prime(int n)
{
	for (int i = 0; i <= n; i++)
		isPrime[i] = 1; //��isPrime����Ԫ�س�ʼ��Ϊ1 

	isPrime[0] = isPrime[1] = 0; //0��1�������� 
	int temp = (int)sqrt(n);

	for (int i = 2; i <= temp; i++)
		if (isPrime[i]) //ɸȥ������������ 
			for (int j = 2 * i; j <= n; j += i)
				isPrime[j] = 0;
}
