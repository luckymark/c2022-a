#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int len = 20;
	int shu[20];
	for (int i = 0; i < len; i++)
		scanf_s("%d", &shu[i]);
	for (int i = 1; i <len; i++)
	{
		for (int j = 0; j < len - i; j++)
		{
			if (shu[j] > shu[j + 1])
			{
				int tamp;
				tamp = shu[j];
				shu[j] = shu[j + 1];
				shu[j + 1] = tamp;
			}
		}

	}
	for(int i=0;i<len;i++)
	{
		printf("%d   ", shu[i]);
	}

	return 0;



}