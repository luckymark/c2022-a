#include<stdio.h>
int main()
{
int a;
scanf("%d",&a);
switch(a)
{
	case 0:
	printf("a既不是正数，也不是负数，但a是偶数");
	break;
	default:
		if(a>0){
			
			if(a%2){
				
				printf("a既是奇数，也是正数");
				
			}
			
			else printf("a既是偶数，也是正数");
			
		}
		else{
			if(a%2){
				
				printf("a既是奇数，也是负数");
				
			}
			
			else printf("a既是偶数，也是负数");
		}
	
}
return 0;
}
