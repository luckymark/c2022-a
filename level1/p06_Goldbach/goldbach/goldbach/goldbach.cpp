//在100范围内验证哥德巴赫猜想的正确性
//输出某个数的表示方式

#include <stdio.h>
int judge(int a);
int main() {
	printf("6=3+3\n");
	printf("7=2+2+3\n");
	for (int number = 8; number < 30;number++) {
		int sign = 0;
		if (number % 2 == 0) {
			for (int a = 3; a <=(number/2); a = a + 2) {
				if ((judge(a)==1)&&(judge(number-a)==1)&&(sign ==0)) {
					sign = 1;
				printf("%d=%d+%d\n",number,a,number-a);
				//goto end;
				}
			}
		}
		else {
			for (int a = 2; a <= (number/3);a++) {
				for (int b = a; b  <= (number / 3);b++) {
					if ((judge(a) == 1)&& (judge(number - a - b) == 1)&& (judge(b) == 1) && (sign == 0)) {
						sign = 1;
						printf("%d=%d+%d+%d\n", number, a, b,number-a-b);
						//goto end;
					}
				}
			}
		}
		//end:;
	}
	return 0;
}
//考虑某个检索函数，可以检测某个数是否为质数
int judge(int a) {
	if (((a==2)||(a==3)||(a==5)||(a==7))||((a%2!=0)&&(a%3!=0)&&(a%5!=0)&&(a%7!=0))) {
		return 1;
	}
	else {
		return 0;
	}
}