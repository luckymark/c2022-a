#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<Windows.h>
int main()
{
	//ˮ�ɻ�����ҵ
	int a = 0;//��λ
	int b = 0;//ʮλ
	int c = 0;//��λ
	printf("ˮ�ɻ���Ϊ��");
	for (int i = 100; i < 1000; i++)
	{
		c = i / 100;
		b = (i / 10) % 10;
		a = i % 10;
		if (i == a * a * a + b * b * b + c * c * c)
		{
			printf("%d ", i);
		}
	}

	system("pause");
	return 0;
}