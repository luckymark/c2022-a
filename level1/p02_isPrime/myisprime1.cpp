#include<stdio.h>
#include<math.h>
# define _CRT_SECURE_NO_WARNINGS 1

int main()
{
	int n = 0, input=0,est=1,sqrt_n=0;
	
	while(1)
	{ 
		printf("������\n");
		scanf("%d", &input);
		sqrt_n = (int)sqrt(1.00*input);
		if(input==1)
			printf("%d������", input);
		if(input==2)
			printf("%d������", input);
		if (input > 2)
		{
			for (n = 2; n <=sqrt_n; n++)
			{
				if (input% n == 0)
					est = 0;
			}
			break;
		}
		else
			printf("����������");
	} 
	if (est == 1)
		printf("%d������", input);
	else
		printf("% d��������", input);
	return 0;
}
