//循环打空格，本来还想用个链表啥，写着写着就结束了。想多了
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	char string[100];
	scanf("%s",string);
	int i=0;
	while(1){
	for(;i<118-(int)strlen(string);i++){
		for(int j=0;j<i;j++){
			putchar(' ');
		}
		printf("%s",string);
		system("cls");
	}
	for(;i>0;i--){
		for(int j=0;j<i;j++){
			putchar(' ');
		}
		printf("%s",string);
		system("cls");
	}
	}
	return 0;
}
