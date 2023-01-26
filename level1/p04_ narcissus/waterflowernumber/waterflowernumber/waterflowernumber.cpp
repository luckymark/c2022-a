/*
打印出所有3位水仙花数

水仙花数：n位数的每个数位的n次方之和等于该n位数本身

例如：153 = 1 ^ 3 + 5 ^ 3 + 3 ^ 3
*/

#include <stdio.h>

int main() {
	//考虑三位数abc
	int a = 0, b = 0, c = 0;
	for (int i = 100; i < 1000;i++) {
		a = i / 100;
		b = (i / 10) % 10;
		c = i % 10;
		if (i == a * a * a + b * b * b + c * c * c) {
			printf("%d\n", i);
		}
	}
	return 0;
}