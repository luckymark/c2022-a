#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
int main()
{
	const int WIDTH = 118;
	char s[26] = { 0 };
	printf("runner: ");
	scanf_s("%s", s, sizeof(s));
	int len, step,dire = 0, c;
	printf("sleep£º ");
	scanf_s("%d", &c);
	len = strlen(s);
	{
		while (1)
		{
			system("cls");
			for (step= 0;step <= abs(dire);step++)
			{
				printf(" ");
			}

			printf("%s", s);
			Sleep(c);
			if (dire== WIDTH- len ||dire == 0)
				dire= -dire; dire++;
		}
	}
	system("pause");
}

