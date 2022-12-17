#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
int main()
{
<<<<<<< HEAD
	const int WIDTH = 118;
	char s[26] = { 0 };
	printf("runner: ");
	scanf_s("%s", s, sizeof(s));
	int len, step,dire = 0, c;
	printf("sleep£º ");
	scanf_s("%d", &c);
=======
	char s[26] = { 0 };
	printf("runner: ");
	scanf_s("%s", s,sizeof(s));
	int len, a, b=0 ,c ;
	printf("sleepÂ£Âº ");
	scanf_s("%d",& c);
>>>>>>> 8663bf11f1a7fb0279e64eddc8cba11fb2dbcbcd
	len = strlen(s);
	{
		while (1)
		{
			system("cls");
<<<<<<< HEAD
			for (step= 0;step <= abs(dire);step++)
=======
			for (a = 0; a <= abs(b); a++)
>>>>>>> 8663bf11f1a7fb0279e64eddc8cba11fb2dbcbcd
			{
				printf(" ");
			}

			printf("%s", s);
			Sleep(c);
<<<<<<< HEAD
			if (dire== WIDTH- len ||dire == 0)
				dire= -dire; dire++;
		}
	}
	system("pause");
}
=======
			if (b == 118 - len || b == 0)
				b = -b; b++;
		}
	}
	system("pause");
}
>>>>>>> 8663bf11f1a7fb0279e64eddc8cba11fb2dbcbcd
