//在把1排除到素数之外后，哥德巴赫猜想的现代表述为：任一大于5的整数都可写成三个素数之和。”
//写得太丑了...
#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
void primeIn100(bool** con);
typedef int* pairOfPrime;
pairOfPrime sumOfTwoPrime(int cnt,int* primes,int now);//将now分解为两素数和并输出
int main(){
	int now;
	bool* notPrime;
	primeIn100(&notPrime);
	int primes[50];
	int cnt=0;
	for(int i=1;i<100;i++){//提取素数
		if(!notPrime[i]){
			primes[cnt]=i+1;
			cnt++;
		}
	}
//哥德巴赫猜想的等价表述为：任意充分大的偶数可以表示为两素数之和
	for(int i=6;i<=100;i++){
		if(i%2){//奇数=3+偶数
			 now=i-3;
			pairOfPrime answer=sumOfTwoPrime(cnt,primes,now);
			printf("%d=3+%d+%d\n",i,answer[0],answer[1]);
			free(answer);
		}else{//偶数=2+偶数
			now=i-2;
			pairOfPrime answer=sumOfTwoPrime(cnt,primes,now);
			printf("%d=2+%d+%d\n",i,answer[0],answer[1]);
			free(answer);
			}
		}
	return 0;
}
void primeIn100(bool** con){//借用下05
	*con=(bool*)malloc(100*sizeof(bool));
	for(int i=0;i<100;i++){
		(*con)[i]=false;
	}
	int cnt=0;
	for(int i=2;i<=100;i++){
		if(!(*con)[i-1]){
			cnt++;
			for(int j=2;i*j<=100;j++){
				(*con)[i*j-1]=true;
			}
		}
	}
}
pairOfPrime sumOfTwoPrime(int cnt,int* primes,int now){
			 for(int j=0;j<cnt;j++){//遍历素数
			 	for(int k=0;k<cnt;k++){
				 	if(primes[j]+primes[k]==now){
				 		pairOfPrime answer=(int*)malloc(2*sizeof(int));
				 		answer[0]=primes[j];
				 		answer[1]=primes[k];
				 		return answer;
					 }
				 }
			 }
			 return NULL;
}
