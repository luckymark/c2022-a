#include"all.h"

int n;


void manu()
{
	printf("1,��ʾ����б�\n2.���\n3.����\n4.�˳�����\n");
}




void show()
{
	readout("./resource/message.txt");
	sh();
}


void in()
{
	printf("������Ҫ��¼�Ļ���Ĵ���");
	scanf("%d", &n);
	goods[n].member = n;
	printf("������������ֺ���Ӧ����");
	getchar();
	scanf("%s", goods[n].name);
	getchar();
	scanf("%d", &goods[n].amount);
	writein("./resource/message.txt");
}


void out()
{
	printf("������Ҫ����������Ļ���Ĵ���");
	scanf("%d", &n);
	printf("������������������Ӧ����(�����ø���)");
	int num;
	scanf("%d", &num);
	goods[n].amount  = goods[n].amount + num;
	writein("./resource/message.txt");
}






void end()
{
	return;
}




void writein(const char* filename)
{
	FILE* fp = fopen(filename, "w");
	while (!fp)
	{
		perror("error:");
		return;
	}
	for (int i = 1; i <= 10; i++)
	{
		if (goods[i].amount == 0)
			break;
		fprintf(fp, "%d.%s %d\n", goods[i].member, goods[i].name, goods[i].amount);
	}
	fclose(fp);
}



void readout(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	while (!fp)
	{
		perror("error:");
		return;
	}
	for (int i = 1; i <= 10; i++)
	{
		fscanf(fp, "%d.%s %d", &goods[i].member, &goods[i].name, &goods[i].amount);
		if (goods[i].member == 0)
			break;
	}
	fclose(fp);
}


void sh()
{
	for (int i = 1; i <= 10; i++)
	{
		if (goods[i].amount == 0)
			break;
		printf("%d,%s %d\n", goods[i].member, goods[i].name, goods[i].amount);
	}
}