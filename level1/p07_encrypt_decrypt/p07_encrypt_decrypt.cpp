#include<stdio.h>
#include<string.h>
#define LEN 20

void encode(char x[],int i);
void decode(char x[],int i);

int main()
{
	char arr[LEN];
	scanf("%s",arr);
	for(int i = 0;i < LEN;i++)
	{
		encode(arr,i);
	}
	printf("%s\n",arr);
	for(int i = 0;i < LEN;i++)
	{
		decode(arr,i);
	}
	printf("%s",arr);
	return 0;
 } 
 
void encode(char x[],int i)
{
	if( (x[i] >= 'a' && x[i] <= 'z' ) || ( x[i] >= 'A' && x[i] <= 'Z'))
	{
		if((x[i] >= 'a' && x[i] <= 'v' ) || ( x[i] >= 'A' && x[i] <= 'V'))
		{
			x[i] = x[i] + 4;				
			i++;
		}
		else
		{
		x[i] = x[i] - 22;				
		i++;
		}
	}
}

void decode(char x[],int i)
{
	if( (x[i] >= 'a' && x[i] <= 'z' ) || ( x[i] >= 'A' && x[i] <= 'Z'))
	{
		if((x[i] >= 'a' && x[i] <= 'v' ) || ( x[i] >= 'A' && x[i] <= 'V'))
		{
			x[i] = x[i] - 4;				
			i++;
		}
		else
		{
		x[i] = x[i] + 22;				
		i++;
		}
	}
}
