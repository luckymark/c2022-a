#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main() {
	int num = 0;
	printf("请输入一个正整数：\n");
	scanf_s("%d", &num);
	if (num == 2) {
		printf("该数不是素数\n");
	}int temp = sqrt(num);
	for (int factor = 2; factor <= temp; factor++) {
		if (num % factor != 0) {
			printf("该数是素数");
			break;
		}else {
			printf("该数不是素数");
			break;
		}
	}return 0;
}