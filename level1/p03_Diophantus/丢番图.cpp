#include<stdio.h>
int main()
{
	float Diophantus=0;
	for(Diophantus=20.0;Diophantus<=100;Diophantus++)
	{
		if(Diophantus/12+Diophantus/6+Diophantus/7+5+Diophantus/2+4==Diophantus)
		break;
	}
	printf("������ʱ����ͼΪ%.2f��",Diophantus-4);
	return 0;
}
