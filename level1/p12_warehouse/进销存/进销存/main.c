#define	_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Cargo.h"

int CargoCount = 0;

char* change(Type type)
{
	switch (type)
	{
	case large:return "large";
	case middle:return "middle";
	case small:return "small";
	default:return "error!";
	}
}
//枚举类型与字符串类型的转换

int menu()
{
	int choice = 0;
	printf("欢迎进入仓库,请选择你的操作：\n");
	printf("1.显示存货列表\n");
	printf("2.入库\n");
	printf("3.出库\n");
	printf("4.修改货物信息\n");
	printf("5.退出程序\n");
	scanf("%d", &choice);
	return choice;
}

int main()
{
	char alter[4];
	int choice=0;
	char helperarr[40];
	char getfromflie[40];
	FILE* fp=NULL ;
	int isfirst = 0;
	CargoNode* phead = NULL;
	CargoNode help;

	printf("是否第一次使用？(是请输入1，不是输入2)\n");
	printf("温馨提示：如果选1，之前的记录都会被清空\n");
	scanf("%d", &isfirst);
	while (1)
	{
		if (isfirst == 1)
		{
			phead = CreateLinkChain(2);
			break;
		}
		else if (isfirst == 2)
		{
			phead=MakeExistChain();
			break;
		}
		else
			printf("无效输入!请重新输入！\n");
	}

	CargoNode helper = {0,0,small,NULL};
	CargoNode* Phelper = &helper;
	while (1) {
		printf("CargoCount:%d\n", CargoCount);
		switch (menu())
		{
		case 1:
			//显示存货列表
			system("cls");
			fp = fopen("存货列表.txt", "r");
			rewind(fp);
			for (int a = 0; a < CargoCount; a++)
			{
				printf("%d. ", a + 1);
				fread(&help, sizeof(CargoNode), 1, fp);
				printf("价格：%-5d数量：%-5d种类：%-7s\n", help.price, help.quantity, change(help.type));
			}
			fclose(fp);
			break;
		case 2:
			//入库
			printf("请依次输入价格，数量，型号\n");
			scanf("%d", &helper.price);
			printf("价格输入成功！\n");
			scanf("%d", &helper.quantity);
			printf("数量输入成功！\n");
			scanf("%s", helperarr);
			if (!(strcmp(helperarr, "large")))
			{
				helper.type = large;
			}
			else if (!(strcmp(helperarr, "middle")))
			{
				helper.type = middle;
			}
			else if (!(strcmp(helperarr, "small")))
			{
				helper.type = small;
			}
			else
			{
				printf("输入型号错误！\n\a");
				exit(0);
			}
			printf("型号输入成功！\n");
			addcargo(phead,helper.price,helper.quantity,helper.type );
			break;
		case 3:
			//出库
			if(CargoCount!=2)
			fclose(fp);
			printf("请输入你要删除第几批货物：\n");
			scanf("%d", &choice);
			delcargo(phead, choice);
			printf("已成功出库！\n");
			break;
		case 4:
			//修改货物信息
			if (CargoCount != 2)
				fclose(fp);
			printf("请输入你要修改第几批货物：\n");
			scanf("%d", &choice);
			getchar();
			printf("请选择需要修改的信息：（按顺序依次是价格、数量、种类）\n");
			printf("需要修改输入y,不需要修改输入n\n");
			scanf("%c %c %c", &alter[0], &alter[1], &alter[2]);
			getchar();
			if (alter[0] == 'y')
			{
				printf("请输入修改后的价格：\n");
				scanf("%d", &helper.price);
			}
			if (alter[1] == 'y')
			{
				printf("请输入修改后的数量：\n");
				scanf("%d", &helper.quantity);
			}
			if (alter[2] == 'y')
			{
				printf("请输入修改后的种类：\n");
				scanf("%s", helperarr);
				if (!(strcmp(helperarr, "large")))
				{
					helper.type = large;
				}
				else if (!(strcmp(helperarr, "middle")))
				{
					helper.type = middle;
				}
				else if (!(strcmp(helperarr, "small")))
				{
					helper.type = small;
				}
				else
				{
					printf("输入型号错误！\n\a");
					exit(0);
				}
				printf("型号输入成功！\n");
			}
			altercargo(phead, choice,Phelper,alter);
			printf("已成功修改！\n");
			break;
		case 5:
			//退出
			printf("你已成功退出！\n");
			goto exit;
			break;
		default:
			printf("无效输入！请重新输入！\n");
			break;
		}
	}
	exit:
	fclose(fp);
	//记录货物件数
	FILE*number = fopen("货物件数.txt", "w");
	fprintf(number, "%d", CargoCount);
	fclose(number);
	printf("CargoCount:%d\n", CargoCount);
	return 0;
}
