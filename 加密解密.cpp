#include<stdio.h>
#include<string.h>
int main(){
	char a;
	int c; 
	int con;
	scanf("%d",&con);
	switch(con){
		case 1:c=1;break;
		case 2:c=-1;break;
	}
	while((a=getchar())!=EOF){
		a+=c;
		putchar(a);
	}
//乱码不知道怎么解决 

















	}
