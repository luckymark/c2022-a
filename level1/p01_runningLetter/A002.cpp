#include <stdio.h>
#include <stdlib.h>
int main()
{
	const int LENTH=118;
	int single=1;
	int pos=0;
	while(1)
	{
		pos+=single;
		if(pos==0||pos==LENTH)
		{
			single=-single;
		}
		for(int i=1;i<=pos;i++)
		{
			printf(" ");
		}
		printf("hello");
		system("cls");
	}
	return 0;
}
