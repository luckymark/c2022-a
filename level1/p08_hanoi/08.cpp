//只记得汉诺塔好像是递归...
//此处默认初始立柱为A柱
#include<stdio.h>
void hanoi_move(int n,int* cnt,char x,char y);
int main(){
	int cnt=0;
	hanoi_move(3,&cnt,'A','C');//用64跑卡住了，加个cnt才发现次数是2^n-1
	printf("count:%d",cnt);
	return 0;
}
void hanoi_move(int n,int* pcnt,char x,char y){
	if(n==1){
		printf("%c -> %c\n",x,y);
		(*pcnt)++;
	}else if(n>1){
		hanoi_move(n-1,pcnt,x,'A'+'B'+'C'-x-y);//这表达式怪怪的，但是想不到更好的统合的方法了
		printf("%c -> %c\n",x,y);
		(*pcnt)++;
		hanoi_move(n-1,pcnt,y,'A'+'B'+'C'-x-y);
	}
}
