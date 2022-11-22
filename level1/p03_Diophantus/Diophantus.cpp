#include<stdio.h>
#include<math.h>
# define _CRT_SECURE_NO_WARNINGS 1

int main()
{
	float tft = 0;
	for (tft = 0; tft < 200; tft++)
	{
		if (tft - tft / 2 - tft / 6 - tft / 12 - tft / 7 == 9)
			printf("%f", tft);
	}
	return 0;
}