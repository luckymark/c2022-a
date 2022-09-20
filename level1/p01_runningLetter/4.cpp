#include  <stdio.h>
#include  <windows.h>
#include <stdlib.h>
int main ()
{    
	
	char str[]="‡À∫¶‡À£¨Œ“TM¿¥¿±£°\t";
	int i=0,j=0,k=0,len=0;
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		k++;
		Sleep(20);
		printf("%c",str[i]);
		if(i==len-1)
		{
			Sleep(20);
				for(j=0;j<strlen(str);j++)
					printf("\b");
				for(j=0;j<strlen(str);j++)
				{
					putchar(' ');
				}
				i=-1;
		}
		if(k==150)
		{
			for(j=0;j<strlen(str);j++)
				printf("\b");
			for(j=0;j<strlen(str);j++)
			{
				putchar(' ');
			}
			printf("\r");
			k=0;
			i=-1;
			
			
		}
	}
	return 0;
}
