//还不太会算复杂度，这个应该是O(N^2)的
//从头遍历，默认都是素数，额外设个桶（是叫这个名字？）得到素数后就把以它为质因子的合数从桶里排掉
//这样过一遍就筛完了
#include<stdio.h>
#include<stdbool.h>
#include<time.h>
bool NotPrime[1000]={};
int main(){
	clock_t start,end;
	start=clock();
	int cnt=0;
	for(int i=2;i<=1000;i++){
		if(!NotPrime[i-1]){
			cnt++;
			printf("%d\n",i);
			for(int j=2;i*j<=1000;j++){
				NotPrime[i*j-1]=true;
			}
		}
	}
	printf("The all primes are:%d\n",cnt);
	end=clock();
	printf("time cost:%ldms",end-start);
}
//1000:144 196 139 165 153 168
//2000:268 293 296 288 239 246
//4000:467 447 462 455 438 455
//8000:746 808 813 700 807 777
//从实际运行来看似乎更像O(N)诶...因为没有实际遍历完数组（看来省掉的部分还挺多）
