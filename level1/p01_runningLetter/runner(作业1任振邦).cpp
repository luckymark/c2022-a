#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<Windows.h>
int main()
{
	for (int n = 0; n < 100; n++)
	{
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < i; j++)
			{
				printf(" ");
			}
			printf("hello");
			Sleep(10);

			system("cls");
		}
		for (int m = 80; m > 0; m--)
		{
			for (int a = 0; a < m; a++)
			{
				printf(" ");
			}
			printf("bye");
			Sleep(10);

			system("cls");
		}
	}

	system("pause");
	
	return 0;
}