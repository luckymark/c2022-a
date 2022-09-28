#include <stdio.h>
#include <stdlib.h>

int main(){
	int isPrime=0,a=0;
	scanf("%d",&a);
	if(a==5||a==3||a==2||a==7){
		isPrime=0;
	}else if(a!=1){
		for(int i=3;i<((a/3)+1);i=i+2){
			if(a%i==0){
			isPrime++;
			}
		}
	}
	if(isPrime!=0){
		printf("not ");
	}
	printf("prime\n");
	system("pause");
	return 0;
}
