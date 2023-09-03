/*打印2 - 1000以内的所有素数
打印出总的计算时间
尽可能优化算法的效率*/
#include  <stdio.h>
#include <time.h>
//本程序申请了1k个数组单元，内存直接爆炸了但是还是可以运行
int main() {
	clock_t begin = clock();
	int a[1001] = {0,};
	//int counter = 0;
	for (int i = 2; i < 1002;i++) {
		a[i] = i;
	}
		for(int j = 2; j < 1002; j++) {
			if (a[j] != 0) {
				int k = j;
				printf("%d\n", j);
				//printf("%d %d\n",j,++counter);
				do {
					k = k + j;
					a[k] = 0;
				} while (k < 1002);
			}
		}
		clock_t end = clock();
		double time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("%lf\n",time);
		//以上耗时计算程序是网上抄的
	return 0;
}