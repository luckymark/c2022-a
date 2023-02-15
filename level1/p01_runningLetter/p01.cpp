#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
void run(char [],int);
int WIDTH = 118;
int main()
{
	 
	char s[26] = { 0 };
	printf("runner: ");
	scanf_s("%s", s, sizeof(s));
	int c;
	printf("sleep£º ");
	scanf_s("%d", &c);
	run(s,c);
	system("pause");
}
void run(char s[],int c) {
	int step, dire = 0;
		int len = strlen(s);
	{
		while (1)
		{
			system("cls");
			for (step = 0; step <= abs(dire); step++)
			{
				printf(" ");
			}

			printf("%s", s);
			Sleep(c);
			if (dire == WIDTH - len || dire == 0)
				dire = -dire; dire++;
		}
	}
}
