#include<stdio.h>
int main()
{
int a;
scanf("%d",&a);
switch(a)
{
	case 0:
	printf("a�Ȳ���������Ҳ���Ǹ�������a��ż��");
	break;
	default:
		if(a>0){
			
			if(a%2){
				
				printf("a����������Ҳ������");
				
			}
			
			else printf("a����ż����Ҳ������");
			
		}
		else{
			if(a%2){
				
				printf("a����������Ҳ�Ǹ���");
				
			}
			
			else printf("a����ż����Ҳ�Ǹ���");
		}
	
}
return 0;
}
