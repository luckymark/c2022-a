#include <stdio.h>
#include<math.h>
#include<time.h> 
int main() {
	int start,end;
	start=clock();
	int x = 2, yushu = 0, n = 0, i = 2, count = 0;//xΪҪ�������n�����ж��ǲ������� 


	for (x = 2; count < 1000; x++) {
		n = 0;
		for (int i = 2; i < sqrt((double)x); i++) { //ÿ�ν����ﶼ�����¶���i
			yushu = x % i;
			if (yushu == 0) { //��������˴���if ���Ӵ�����ֻ��һ��
				n = 1;
				break;
			}
		}


		if (n == 0) {
			printf("%d\t", x);
			count++;


			if (count % 10 == 0) { //0��5����0��Ҳ���Կ�count�ܲ��ܱ�����
				printf("\n");
			}
		} 

	}
	end=clock(); 
	printf("����%d������\n", count);
	printf("%d",end-start);
	return 0 ;
}
