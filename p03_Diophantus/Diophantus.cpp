#include<stdio.h>
int main() {
	int age;
	for (age = 1; ;age++)
	{
		if (age * 1.0 / 6 + age * 1.0 / 12 + age * 1.0 / 7 + 5 + 4 == age * 1.0 / 2){
			printf("儿子死时丢番图是%d岁", age);
			break;}

	}
	return 0;
}