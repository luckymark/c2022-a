#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main() {
	int num = 0;
	printf("������һ����������\n");
	scanf_s("%d", &num);
	if (num == 2) {
		printf("������������\n");
	}int temp = sqrt(num);
	for (int factor = 2; factor <= temp; factor++) {
		if (num % factor != 0) {
			printf("����������");
			break;
		}else {
			printf("������������");
			break;
		}
	}return 0;
}