#include <stdio.h>

int main()
{int x=0,n=0,max=1,min=0,limit=1,e=0,sum=0,a=1,b=0,c=0;//nΪλ���� 


printf("����\n");
scanf("%d",&n);
e=n;//�ݴ� 

for(;n>0;n--){
	limit=limit*10;
}

min=limit/10;
max=limit-1;//�ҷ�Χ 

for(x=min;x<=max;){
	
	c=x;//�ݴ� 
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
	sum=0;//��ʼ��׼����һ���������� 
	x=c+1;
	
}





	

return 0;

}
//���д���ˣ���ʦ�Ĺ��� 
