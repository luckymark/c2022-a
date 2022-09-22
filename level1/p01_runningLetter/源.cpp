#include<cstdio>
#include<cstring>
#include<windows.h>
char s[1000];
int main()
{
	
	int c,j = 0;
	while (c = getchar())
	{
		if (c == '\n')
		{
			break;
		}
		s[j] = c;
		j++;
	}
	int pos = 0;
	bool sign = 1;
	while (1)
	{
		if (sign)
		{
			if (pos >= 118 - strlen(s))
			{
				sign = 0;
				continue;
			}
			for (int i = 0; i < pos; i++)
			{
				printf(" ");
			}
			printf("%s", s);
			Sleep(2);
			system("cls");
			pos++;
		}
		else
		{
			if (pos == 0)
			{
				sign = 1;
				continue;
			}
			for (int i = pos - 1; i >= 0; i--)
			{
				printf(" ");
			}
			printf("%s", s);
			Sleep(2);
			system("cls");
			pos--;
		}

	}
}