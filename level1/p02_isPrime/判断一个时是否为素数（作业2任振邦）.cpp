#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<Windows.h>
int main()
{
	int a = 0;//个位
	int b = 0;//十位
	int c = 0;//百位

	for (int i = 100; i < 1000; i++)
	{
		c = i / 100;
		b = (i / 10) % 10;
		a = i % 10;
		if (i == a * a * a + b * b * b + c + c + c)
		{
			printf("你输出的数字是水仙花数");
		}
	}
	
	system("pause");
	return 0;
}