#include"stdio.h"
#include"math.h"
int main()
{
	int num,sqt,b;
	scanf_s("%d", &num);
	sqt = sqrt(num);
	if (num < 2) b = 0;
	else 
	{
		b = 1;
		for (int i = 2; i <= sqt; i++)
		{
			if (num % i == 0) {
				b = 0; break;
			}
		}
	}
	if (b == 1) printf("%d is Prime", num);
	else printf("%d is not Prime", num);
	return 0;
}