﻿#include<stdio.h>

int main()
{
	for (int a =1; a <= 9; a++)
	{
		for (int b = 0; b <= 9; b++)
		{
			for (int c = 0; c <= 9; c++)
			{
				if(a*a*a+b*b*b+c*c*c==100*a+10*b+c)
				{
					printf("%d%d%d\n", a, b, c);
			
				}
			}
		}

	}
	return 0;

}