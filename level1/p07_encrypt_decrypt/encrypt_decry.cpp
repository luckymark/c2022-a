#include<stdio.h>
#include<string.h>
#define long 20

void encode(char x[],int i);
void decode(char x[],int i);
void encode(char x[],int i);


int main()
{
	char a[long];
	scanf("%s",a);
	for(int i = 0;i < long;i++)
	{
		encode(a,i);
	}
	printf("%s\n",a);
	for(int i = 0;i < long;i++)
	{
		decode(a,i);
	}
	printf("%s",a);
	return 0;
 } 

void encode(char x[],int i);
void decode(char x[],int i);
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
