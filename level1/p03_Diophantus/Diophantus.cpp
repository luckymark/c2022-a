#include<stdio.h>
int main() {
	float fraction = 1 / 6.0 + 1 / 12.0 + 1 / 7.0+ 1 / 2.0;//�������ļ��㸳ֵ�������ͱ���fraction
	for(int age = 1.0; age<100.0; ++age) {
		float temp = 5.0 + 4.0 + age*fraction;
		if (temp== age) {
			printf("���׵�����Ϊ��%d\n", age);
		}
	}return 0;
}