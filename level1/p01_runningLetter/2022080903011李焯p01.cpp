#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
int main()
{
	char s[26] = { 0 };
	printf("runner: ");
	scanf_s("%s", &s,sizeof(s));
	int len, a, b=0 ,c ;
	printf("sleep£º ");
	scanf_s("%d",& c);
	len = strlen(s);
	{
		while (1)
		{
			system("cls");
			for (a = 0; a <= abs(b); a++)
			{
				printf(" ");
			}

			printf("%s", s);
			Sleep(c);
			if (b == 118 - len || b == 0)
				b = -b; b++;
		}
	}
	system("pause");
}