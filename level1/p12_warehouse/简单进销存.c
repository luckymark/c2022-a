#include "all.h"



int main()
{
	int a;
	do
	{
		system("cls");
	manu();
	scanf("%d", &a);
	getchar();
	readout("./resource/message.txt");
	system("cls");
		switch (a)
		{
		case 1:
			show();
			break;
		case 2:
			in();
			break;
		case 3:
			out();
			break;
		case 4:
			return 0;
		default:
			printf("error");
			break;
		}
		printf("\n");
		printf("按任意键继续");
	} while (getchar());
	return 0;
}