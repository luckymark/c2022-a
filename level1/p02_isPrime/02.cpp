#include<stdio.h>
#include<stdbool.h>
void answer(bool isPrime, int N);
int main(){
	int N;
	bool isPrime=true;
	printf("输入一个数：");
	scanf("%d",&N);
	answer(isPrime,N);
	return 0;
}
void answer(bool isPrime,int N){
	for(int i=2;i<=N/2;i++){//一个数N不可能有大于N/2的质因子（因为2是最小的质因子）
		if(!(N%i)){//循环判别i是否为N的质因子
			isPrime=false;
			break;
		}
	}
	if(!isPrime||N==1){
		printf("It is not prime\n");
	}else{
		printf("It is prime\n");
	}
}
