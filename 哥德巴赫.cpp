#include<stdio.h>
void creatprime(int a[]);
int main(void) {
	int num[1000];
	int a = 0, b = 0, c = 0;
	num[0] = 2;
	creatprime(num);
	for (int i = 6; i <= 1000; ) {
		int con = 0;
		for (a = 0; a < 250; a++) {//250是指第250个素数必大于1000； 
			for (b = 0; b < 250; b++) {
				for (c = 0; c < 250; c ++) {
					if (i == (num[a] + num[b] + num[c]) ) {
						con = 1;
						i++;
						break;
					}
				}
			}
		}

		if (con == 0) {
			printf("错误");
			return 0;
		}
	}
	printf("正确");
	return 0;





}
void creatprime(int a[]) {
	int x = 3;
	int con;
	for (int i = 0; i < 250; x++) {
		con = 1;
		for (int n = 0; n <= i; n++) {
			if (x % a[n] == 0) {
				con = 0;
				break;
			}
		}
		if (con == 1) {
			a[++i] = x;
		}
	}
}


















