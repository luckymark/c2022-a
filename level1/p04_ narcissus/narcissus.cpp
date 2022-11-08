#include<stdio.h>
#include<math.h>
int main() {
	for (int i = 100; i < 1000; i++) {
		int ones = i % 10;
		int tens = i / 10 % 10;
		int hundreds = i / 100;
		if (i == pow(ones, 3) + pow(tens, 3) + pow(hundreds, 3)) {
			printf("%d\n", i);
		}
	}return 0;
}