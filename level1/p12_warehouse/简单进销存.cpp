//1. 实现如下的菜单（按数字选择菜单功能）：
//- 显示存货列表
//- 入库
//- 出库
//- 退出程序
//1. 实现菜单对应功能（需记录货物的型号、数量等信息）；
//1. 程序启动时从文件中读取当前库存数据，退出时保存库存数据；
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<Windows.h>
void SwitchFunction(int num);
void ShowInformaiton();
void PushStore();
void PopStore();
void Exit();
int main()
{
	FILE* fp;
	fp = fopen("简单进销存.txt", "r+");
	if (fp == NULL)
	{
		printf("文件打开失败");
	}
	else
	{
		printf("文件打开成功");
	}
	//int n = 0;
	//scanf_s("%d", &n);
	//SwitchFunction(n);
	//fclose();
	system("pause");
	return 0;
}
void SwitchFunction(int num)
{
	switch (num)
	{
	case 1:ShowInformaiton();
		break;
	case 2:PushStore();
		break;
	case 3:PopStore();
		break;
	case 4:Exit();
		break;
	default:printf("Your input is error");
		break;
	}
}
void ShowInformaiton()
{
	;
}
void PushStore()
{
	;
}
void PopStore()
{
	;
}
void Exit()
{
	exit(1);
}