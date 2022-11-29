#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

char arr1[128],arr2[128];

void jiami(char*p,int size)
{
	for (int a = 0; a < size; a++)
	{
		p[a] = p[a] + a + 1;
	}
}

void jiemi(char* p, int size)
{
	for (int a = 0; a < size; a++)
	{
		p[a] = p[a] - a - 1;
	}
}

int main()
{
	char arr[128];
	printf("please enter your string:\n");
	scanf("%s", arr);
	jiami(arr,strlen(arr));
	printf("%s",arr);
	putchar('\n');
	jiemi(arr, strlen(arr));
	printf(arr);
	return 0;
}