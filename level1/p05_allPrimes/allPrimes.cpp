#include<stdio.h>
#include<time.h>
#include<math.h>
int main() {
	{clock_t t1, t2;
	t1 = clock();
		int num = 0; int factor = 0;
		for (num = 1; num <= 1000; num++)
		{
			for (factor = 2; factor <= sqrt(num); factor++)
			{
				if (num % factor == 0) {
					break;
				}
			}if (factor > sqrt(num) && num != 1) {
				printf("%d ", num);
			}
		}t2 = clock();
		printf("\n运行时间为：%d", t2 - t1);
	}return 0;
}