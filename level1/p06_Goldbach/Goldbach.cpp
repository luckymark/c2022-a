#define SIZE 25	//100������25������
#include<stdio.h>
#include<math.h>
int main() {
	int arr[SIZE], order = 0;
	int num = 0, factor = 0;
	for (num = 1; num <= 100; num++)
	{
		for (factor = 2; factor <= sqrt(num); factor++)
		{
			if (num % factor == 0) {
				break;
			}
		}if (factor > sqrt(num) && num != 1) {
			arr[order] = num;
			order++;
		}
	}for (int even = 6 - 2; even <= 100; even += 2) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (even == arr[i] + arr[j]) {
					printf("%d\n", even);	//������������ż��ȫ����ӡ
				}
			}
		}
	}return 0;
}