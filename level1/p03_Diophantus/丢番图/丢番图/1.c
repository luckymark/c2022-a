#include<stdio.h>
int main()                                                //第三个作业
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
	printf("儿子死时丢番图%.0f岁", age - 4);
	return 0;
}