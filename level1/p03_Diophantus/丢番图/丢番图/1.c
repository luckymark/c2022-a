#include<stdio.h>
int main()                                                //��������ҵ
{
	float age;
	for (float a = 1; a < 120; a++)
	{
		if (a / 6 + a / 12 + a / 7 + 5 + 4 + a / 2 == a)
		{
			age = a;
			break;
		}
	}
	printf("������ʱ����ͼ%.0f��", age - 4);
	return 0;
}