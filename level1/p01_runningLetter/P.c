#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
	const int SCREENWIDTH=80,SLEEPTIME=20;
	int move=1,i=1,x=1;
	while(1){
		system("cls");
		if(i==SCREENWIDTH||i==0){
			move=-move;
		}
		for(x=1;x<=i;x++){
			printf(" ");
		}
		i=i+move;
		printf("hello world!\n");
		Sleep(SLEEPTIME);
	}
	return 0;
}
