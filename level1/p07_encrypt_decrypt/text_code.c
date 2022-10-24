//加密规则：每个字符加上它在字符串中的位置和偏移量5——对应ASCII码表
#include<stdio.h>
#include<string.h>
void en(char text[100]);
void de(char code[100]);
int main()
{
	int result;
	char text[1000], code[1000];
	printf("要加密请输入0，要解密请输入1：\n");
	scanf_s("%d", &result);
	if (result == 0)
	{
		printf("请输入需要加密的字符串:\n");
		scanf_s("%s", text,1000);
		en(text);
	}
	else
	{
		printf("请输入需要解密的字符串:\n");
		scanf_s("%s", code,1000);
		de(code);
	}
	return 0;
}
void en(char text[1000])
{
	int i, length;
	char code[1000];
	length = strlen(text);
	for (i = 0; i < length; i++)
	{
		code[i] = text[i] + i + 5;
	}
	code[i] = '\0';
	printf("加密后的密码是：%s", code);
}
void de(char code[1000])
{
	int i,length;
	char text[1000];
	length = strlen(code);
	for (i = 0; i < length; i++)
	{
		text[i] = code[i] - i - 5;
	}
	text[i] = '\0';
	printf("解密后的明文是：%s", text);
}
