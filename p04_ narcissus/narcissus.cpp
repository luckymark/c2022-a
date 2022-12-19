#include<stdio.h>
int main() {

	int number=100;
	int a = 0;
	
	while (number < 1000) {
		int c = number;//储存number的值
		int sum = 0;//储存各位幂的和
		do {
			a = c % 10;
			c /= 10;
			sum += (a * a * a);
		} while (c > 0);
		if (sum == number) {
			printf("%d ", number);
		}
		number++;
	}

		

	return 0;
}
