#include <stdio.h>

int main()
{int x=0,n=0,max=1,min=0,limit=1,e=0,sum=0,a=1,b=0,c=0;//n为位数， 


printf("输入\n");
scanf("%d",&n);
e=n;//暂存 

for(;n>0;n--){
	limit=limit*10;
}

min=limit/10;
max=limit-1;//找范围 

for(x=min;x<=max;){
	
	c=x;//暂存 
	for(;x>0;){
		n=e;
		b=x%10;
		x=x/10;
		for(a=1;n>0;n--){
			a=a*b;
		}
		sum=sum+a;
	}
	if(c==sum){
		printf("%d\n",sum); 
		
	}
	sum=0;//初始化准备下一个数的运算 
	x=c+1;
	
}





	

return 0;

}
//暑假写的了，老师饶过我 
