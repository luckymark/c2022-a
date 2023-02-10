//1. 打印2-1000以内的所有素数
//1. 打印出总的计算时间
//1. 尽可能优化算法的效率
#include<stdio.h>
#include<math.h>
#include<time.h>
clock_t start,stop;
double duration;
int main()

{
	start=clock();
	for(int a=2;a<=1000;a++)
	{
		int  k=(int)sqrt(a);	int s=1;
		for(int j=2;j<=k;j++){
	
		if(a%j==0) {s=0;
		break;
		}	
		}
		if(s==1) {
		printf("%d ",a);
		}
		
		
		
	}
	stop=clock();
	printf("%.1f",((double)(stop-start)/CLK_TCK));
	return 0;
}
