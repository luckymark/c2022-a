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
#include<string.h>
void ShowInformaiton(char&ch,FILE*&fp);
void PushStore(char infor[], FILE*& fp);
void PopStore(char& ch, char without[],FILE*&fp);
void Exit();
int main()
{
	FILE* fp;
	char ch = '1';
	char information[40] = { 0 };
	char withoutobject[40] ={0};
	fopen_s(&fp,"简单进销存.txt", "r+");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
	}
	else
	{
		printf("文件打开成功\n");
	}
	int n = 0;
	do
	{
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:ShowInformaiton(ch, fp);
			break;
		case 2:PushStore(information, fp);
			break;
		case 3:PopStore(ch, withoutobject, fp);
			break;
		case 4:Exit();
			break;
		default:printf("Your input is error");
			break;
		}
	} while (1);
	fclose(fp);
	system("pause");
	return 0;
}

void ShowInformaiton(char& ch, FILE*&fp)
{
	fseek(fp, 0, SEEK_SET);
	while (ch != '.')
	{
		ch = fgetc(fp);
		printf("%c", ch);
	};
}
void PushStore(char infor[], FILE*& fp)
{
	fseek(fp, -2 * sizeof(char), SEEK_END);
	gets_s(infor,40);
	fwrite(infor, sizeof(char) * 40, 1, fp);
}
void PopStore(char& ch, char without[], FILE*& fp)
{
	fseek(fp, 0, SEEK_SET);
	fwrite(without, sizeof(char) * 40, 1, fp);
}
void Exit()
{
	exit(1);
}