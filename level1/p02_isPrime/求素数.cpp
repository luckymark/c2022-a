//1. ��ӡ2-1000���ڵ���������
//1. ��ӡ���ܵļ���ʱ��
//1. �������Ż��㷨��Ч��
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<windows.h>
//enum Color{black,blue,green,lakeblue,red,purple,yellow,white,gray};
//void setClock(unsigned short backColor=0,unsigned short backColor=7){
//char command[9]="color 07";
//command[6]='0'+backColor;
//command[7]='0'+backColor;
//}
//clock_t start,stop;
//double duration;
int main()
////{
	//setColor(1,2);
//}
{
	//start=clock();
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
	//stop=clock();
	//printf("%.1f",((double)(stop-start)/CLK_TCK));
	return 0;
}
