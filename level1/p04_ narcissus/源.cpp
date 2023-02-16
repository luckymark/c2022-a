/* 功能要求：
1. 打印出所有3位水仙花数
水仙花数：n位数的每个数位的n次方之和等于该n位数本身
例如：153 = 1 ^ 3 + 5 ^ 3 + 3 ^ 3*/

#include<stdio.h>
#include<stdlib.h>
int main()
{
	int A, B, C;
	for (A = 1; A <= 9; A++)
		for (B = 0; B <= 9; B++)
			for (C = 0; C <= 9; C++)
			{
				if (A * 100 + 10 * B + C == A * A *A+ B * B * B + C * C * C)
					printf(" %d%d%d\n", A, B, C);
			}
	system("pause");
return 0;
}