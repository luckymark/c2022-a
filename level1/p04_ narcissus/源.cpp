/* ����Ҫ��
1. ��ӡ������3λˮ�ɻ���
ˮ�ɻ�����nλ����ÿ����λ��n�η�֮�͵��ڸ�nλ������
���磺153 = 1 ^ 3 + 5 ^ 3 + 3 ^ 3*/

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