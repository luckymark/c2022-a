#include<stdio.h>
int main()
{
	float span_dad,span_son;
	float happy = 5, sorrow = 4;
	span_dad = (1/(1 - (float)1 / 6 - (float)1 / 12 - (float)1 / 7 - (float)1 / 2))*(happy + sorrow);
	//(1/6+1/12+1/7)span_dad+5+span_son+4==span_dad;
	printf("%f", span_dad);
	return 0;

}