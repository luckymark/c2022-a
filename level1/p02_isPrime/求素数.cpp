//1. ��ӡ2-1000���ڵ���������
//1. ��ӡ���ܵļ���ʱ��
//1. �������Ż��㷨��Ч��
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
