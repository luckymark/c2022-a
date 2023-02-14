# define _CRT_SECURE_NO_WARNINGS 1#
#include "box.h"
int m = 0;
int main()
{
	int n = 0;
	do
	{
		meun();
		printf("ÇëÑ¡Ôñ");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("¿ªÊ¼\n");
		    initializebox();
			myprint();
			start();
			
			break;
		case 0:
			break;
		default:
			break;
		}
	} while (n == 1);
	return 0;
}