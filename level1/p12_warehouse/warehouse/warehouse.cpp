#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void manu();

typedef struct cargo {
	char name[20];
	int amount;
	int num;
}cargo;

cargo AllCargo[100]; int i;


void input()
{
	cargo Cargo;

	//FILE* pCargoData;

	//fopen_s(&pCargoData,"CargoData.txt", "a");
	
	printf("请输入货物编号:\n");
	scanf_s("%d", &Cargo.num);
	//fprintf(pCargoData, "货物编号：%d\n",Cargo.num);
	printf("请输入货物型号:\n");
	scanf_s("%s",Cargo.name,20);
	//fprintf(pCargoData, "货物型号：%s\n",Cargo.name);
	printf("请输入货物数量:\n");
	scanf_s("%d",&Cargo.amount);
	//fprintf(pCargoData, "货物数量：%d\n\n",Cargo.amount);
	//fclose(pCargoData);
	i++;
	AllCargo[i] = Cargo;

	manu();
}

void output()
{
	int temp;
	printf("请输入出库货物编号：\n");
	scanf_s("%d", &temp);
	for(int n=0;n<=i;n++)
	{
		if (AllCargo[n].num == temp)
		{
			for (int m = n; m <= i; m++)
			{
				AllCargo[m] = AllCargo[m + 1];
			}
			i=i-1;
			break;
		}
	}
	manu();
}

void show()
{
	for (int n = 0; n <= i; n++)
	{
		printf("%d（商品编号）\n", AllCargo[n].num);
		printf("商品名称：%s\n", AllCargo[n].name);
		printf("商品数量：%d\n\n", AllCargo[n].amount);
	}
	manu();
}

void manu()
{
	int n;

	puts("\t\t             欢迎来到仓库货物管理系统              ");
	puts("\t\t***********************菜单**********************\n");
	puts("\t\t*                  1.显示货存列表               *\n");
	puts("\t\t*                  2.货物入库                   *\n");
	puts("\t\t*                  3.货物出库                   *\n");
	puts("\t\t*                  4.退出程序                   *\n");
	puts("\t\t*************************************************\n");
	printf("                请选择你要输入数(1-4): \n");
	scanf_s("%d", &n);
	while (n < 1 || n>4)
	{
		printf("输入指令有误，请重新输入：\n");
		scanf_s("%d", &n);
	}
	switch (n)
	{
	case 1:show(); break;
	case 2:input(); break;
	case 3:output(); break;
	case 4:printf("THANK YOU !\n");
		FILE* pCargoDataUpdate;
		fopen_s(&pCargoDataUpdate, "CargoData.txt", "w");
		for (int a = 0; a <= i; a++)
		{
			fprintf(pCargoDataUpdate, "%d\n%s\n%d\n\n", AllCargo[a].num, AllCargo[a].name, AllCargo[a].amount);
		}
		fclose(pCargoDataUpdate);
		exit(0);
	}
}


int main()
{
	//FILE* pCargoData;
	//fopen_s(&pCargoData,"CargoData.txt", "r");
	//
	//fclose(pCargoData);
	i = -1;
	manu();

}