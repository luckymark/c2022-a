#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int main()
{
	int step = 0,a = 1;
	while (1)
	{
		step += a;
		if (step == 100||step == 0)//120һ������Ļ���Ҷ�����
		{
			a = -a;
		}//����
		for (int i = 0; i <= step; i++)//ѭ���������ӣ�ÿ������ո��࣬��ĸ��������ƶ�
		{
			printf(" ");
		}
		printf("hallo world");
		Sleep(20);
		system("cls");//������
	}
	return 0;
}