#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
# define _CRT_SECURE_NO_WARNINGS 1
#define num 100

char  enc1[num], dec1[num];
void enc( char arr[num],char ran[num],int n)
{
	for(int i=0;i<n;i++)
	enc1[i] = arr[i] ^ ran[i];
}
void dec(char arr[num], char ran[num], int n)
{
	for (int i = 0; i < n; i++)
		dec1[i] = enc1[i] ^ ran[i];
}
int main()
{
	char arr[num], ran[num];
	srand((unsigned)time(NULL));
	int n=0,i = 0;
	scanf("%s", arr);
	n = strlen(arr);
	for (i = 0; i < n; i++)
		ran[i] = rand();
	enc(arr,ran,n);
	printf("%s\n", enc1  );
	dec(arr, ran, n);
	printf("%s\n", dec1);
	return 0;
}
