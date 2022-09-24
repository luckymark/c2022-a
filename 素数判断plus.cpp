#include <stdio.h>
#include<math.h>
#include<time.h> 
int main() {
	int start,end;
	start=clock();
	int x = 2, yushu = 0, n = 0, i = 2, count = 0;//x为要求的数，n用于判断是不是素数 


	for (x = 2; count < 1000; x++) {
		n = 0;
		for (int i = 2; i < sqrt((double)x); i++) { //每次进这里都会重新定义i
			yushu = x % i;
			if (yushu == 0) { //这里出现了错误，if 不加大括号只管一行
				n = 1;
				break;
			}
		}


		if (n == 0) {
			printf("%d\t", x);
			count++;


			if (count % 10 == 0) { //0余5等于0，也可以看count能不能被整除
				printf("\n");
			}
		} 

	}
	end=clock(); 
	printf("共有%d个素数\n", count);
	printf("%d",end-start);
	return 0 ;
}
