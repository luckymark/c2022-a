#include<stdio.h>
#include<stdlib.h>
int main()
{
	int age;
	for (age = 1; age < 150; age++)

		if (age / 2 + age / 6 + age / 12 + age / 7 + 5 + 4 == age)
		{

			printf("%d", age);
			break;
		}
}
