#include<stdio.h>
#include<math.h>
int main(){
	int num = 100;
	printf("如果%d以內的數字符合哥德巴赫猜想,輸出1,否則輸出0\n", num);
	int prime[10001];
	prime[0] = 2;
	int len = 1;
	for (int i = 3; i <= num; i++) {
		int check = 1;
		for (int j = 0; j < len; j++) {
			if (i % prime[j] == 0) {
				check = 0;
				break;
			}
		}
		if (check == 1 ) {
			prime[len] = i;
			len++;
		}
	}
	int target;
	int res = 1;
	for (int i = 4; i <= num; i += 2)
	{
		int c = 0;
		for (int j = 0; j < len; j++) {
			target = i - prime[j];
			for (int k = 0; k < len; k++) {
				if (prime[k] == target) {
					c = 1;
					break;
				}
			}	
		}
		if (c == 0) { 
				res = i; break; 
			}
	}
	printf("%d", res);
	return 0;
}
