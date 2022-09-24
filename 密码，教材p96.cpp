#include<stdio.h>
#include<string.h> 
int main() {
	char num[100];
	char chi[54]="0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	scanf("%s",num);
	int len=strlen(num);
	for(int i=0;i<len;i++){
		for(int n=1;n<53/*53指数组最后一个*/;n++){
			if(num[i]==chi[n]){
				num[i]=chi[((n*3)%52)];
				break;
			}
		}
	}
	for(int i=0;i<len;i++){
		printf("%c",num[i]);
	}


	return 0;
}
//但是这个不会解密 
