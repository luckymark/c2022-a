#define SIZE 5
#include<stdio.h>
int main() {
	int arr[SIZE];
	printf("请输入所需加密的字符串\n");
	for (int a = 0; a < SIZE; a++) {
		scanf_s("%d", &arr[a]);
	}for (int a = 0; a < SIZE; a++){		//加密
		arr[a] *= 5;
		arr[a]+=2;
	}for (int a = 0; a < SIZE; a++) {
		printf("%d ", arr[a]);
	}printf("\n");
	for (int a = 0; a < SIZE; a++) {		//解密
		arr[a]-=2;
		arr[a] /= 5;
	}for (int a = 0; a < SIZE; a++) {
		printf("%d ", arr[a]);
	}return 0;
}