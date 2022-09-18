//只记得汉诺塔好像是递归...
//此处默认初始立柱为A柱
#include<stdio.h>
void hanoi_A2C(int n,int* cnt);
void hanoi_C2A(int n,int* cnt);
void hanoi_A2B(int n,int* cnt);
void hanoi_B2A(int n,int* cnt);
void hanoi_B2C(int n,int* cnt);
void hanoi_C2B(int n,int* cnt);
int main(){
	int cnt=0;
	hanoi_A2C(3,&cnt);//用64跑卡住了，加个cnt才发现次数是2^n-1
	printf("count:%d",cnt);
	return 0;
}
void hanoi_A2C(int n,int* pcnt){
	if(n==1){
		printf("A -> C\n");
		(*pcnt)++;
	}else if(n>1){
		hanoi_A2B(n-1,pcnt);
		printf("A -> C\n");
		(*pcnt)++;
		hanoi_B2C(n-1,pcnt);
	}
}
void hanoi_C2A(int n,int* pcnt){
	if(n==1){
		printf("C -> A\n");
		(*pcnt)++;
	}else if(n>1){
		hanoi_C2B(n-1,pcnt);
		printf("C -> A\n");
		(*pcnt)++;
		hanoi_B2A(n-1,pcnt);
	}
}
void hanoi_A2B(int n,int* pcnt){
	if(n==1){
		printf("A -> B\n");
		(*pcnt)++;
	}else if(n>1){
		hanoi_A2C(n-1,pcnt);
		printf("A -> B\n");
		(*pcnt)++;
		hanoi_C2B(n-1,pcnt);
	}
}
void hanoi_B2A(int n,int* pcnt){
	if(n==1){
		printf("B -> A\n");
		(*pcnt)++;
	}else if(n>1){
		hanoi_B2C(n-1,pcnt);
		printf("B -> A\n");
		(*pcnt)++;
		hanoi_C2A(n-1,pcnt);
	}
}
void hanoi_B2C(int n,int* pcnt){
	if(n==1){
		printf("B -> C\n");
		(*pcnt)++;
	}else if(n>1){
		hanoi_B2A(n-1,pcnt);
		printf("B -> C\n");
		(*pcnt)++;
		hanoi_A2C(n-1,pcnt);
	}
}
void hanoi_C2B(int n,int* pcnt){
	if(n==1){
		printf("C -> B\n");
		(*pcnt)++;
	}else if(n>1){
		hanoi_C2A(n-1,pcnt);
		printf("C -> B\n");
		(*pcnt)++;
		hanoi_A2B(n-1,pcnt);
	}
}
