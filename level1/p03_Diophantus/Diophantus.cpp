#include<stdio.h>
int main() {
	float fraction = 1 / 6.0 + 1 / 12.0 + 1 / 7.0+ 1 / 2.0;//将分数的计算赋值给浮点型变量fraction
	for(int age = 1.0; age<100.0; ++age) {
		float temp = 5.0 + 4.0 + age*fraction;
		if (temp== age) {
			printf("父亲的年龄为：%d\n", age);
		}
	}return 0;
}