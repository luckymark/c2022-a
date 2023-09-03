#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void encryption(int length,char origin[])
{
	for (int i = 0; i < length; i++)
	{
		if (i < 100)
		{
			origin[i] = origin[i] + '5';
		}
		else
		{
			origin[i] = origin[i] + '10';
		}
	}
	for (int i = 0; i < length; i++)
	{
		printf("%c\n", origin[i]);
	}
}
void decryption(int length, char origin[])
{
	for (int i = 0; i < length; i++)
	{
		if (i < 100)
		{
			origin[i] = origin[i] - '5';
		}
		else
		{
			origin[i] = origin[i] - '10';
		}
	}
	for (int i = 0; i < length; i++)
	{
		printf("%c", origin[i]);
	}
}
int main()
{
	int length = 0;
	char origin[10000] = { 0 };
	scanf_s("%s", &origin, 10000);
	length = strlen(origin);
	encryption(length, origin);
	decryption(length, origin);
	return 0;
}
