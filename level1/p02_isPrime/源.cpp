#include <stdio.h>
#include <math.h>
int main() {
	int n,flag=1;
	scanf("%d",&n);
	if(n>1){
		for (int i = 2; i <= sqrt((double)n); i++) {
			if(n % i == 0) flag = 0;
			if(!flag) break;
		}
	}
	if (flag==0 || n==1) printf("%d is not prime", n);
	else printf("%d is prime",n);
	return 0;
}