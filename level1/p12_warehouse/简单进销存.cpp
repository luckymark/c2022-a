//1. ʵ�����µĲ˵���������ѡ��˵����ܣ���
//- ��ʾ����б�
//- ���
//- ����
//- �˳�����
//1. ʵ�ֲ˵���Ӧ���ܣ����¼������ͺš���������Ϣ����
//1. ��������ʱ���ļ��ж�ȡ��ǰ������ݣ��˳�ʱ���������ݣ�
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
	fp = fopen("�򵥽�����.txt", "r+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��");
	}
	else
	{
		printf("�ļ��򿪳ɹ�");
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