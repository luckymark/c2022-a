#include"stdio.h"
int main()
{
	for (float i = 5;i>0; i++)
	{
		if ((i / 6) + (i / 12) + (i / 7) +(i/2)+ 5 + 4 == i)
		{
			printf("%.0f", i);
			break;
		}
	}
	return 0;
}