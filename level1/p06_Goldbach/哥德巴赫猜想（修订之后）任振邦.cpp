#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
int main()
{//��°ͺղ�����ִ�����Ϊ����һ����5����������д����������֮�͡�
	//1.�������洢��һ�����鵱��
	int sum = 0;
	int sign = 1;
	int test = 0;
	int sushu[50] = { 0 };
	sushu[0] = 2;
	for (int num = 2; num < 100; num++)
	{
		for (int i = 2; i < num; i++)
		{
			if (num % i == 0)
			{
				break;
			}
			if (i == num - 1)
			{
				sushu[sign] = num;
				++sign;
			}

		}
	}
	//2.�ж�100���м�������
	for (int j = 0; j < 100; j++)
	{
		if (sushu[j] == 0)
		{
			break;
		}
		else
		{
			printf("%d\n", sushu[j]);
			sum++;
		}
	}
	printf("%d\n", sum);
	//3.��֤5~100ʱ��°ͺղ������
	for (int i = 6; i <= 100; i++)
	{
		for (int a = 0; a < sum; a++)//��������1
		{
			for (int b = 0; b < sum; b++)//��������2
			{
				for (int c = 0; c < sum; c++)//��������3
				{
					if (sushu[a] + sushu[b] + sushu[c] == i)
					{
						test++;
						goto FLAG;
					}
				}
			}
		}
	FLAG:;
	}
		printf("%d\n", test);
	if (test ==95)
	{
		printf("��°ͺղ�����100���ڳ���");
	}
	else
	{
		printf("��°ͺղ��벻����");
	}
	system("pause");
	return 0;
}