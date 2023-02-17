#include <stdio.h>

int main()
{
	int x, y = 0;
	scanf_s("%d", &x);
	while (x > 0) {
		y = y * 10 + x % 10;
		x = x / 10;

	}
	printf("y=%d", y);


}


