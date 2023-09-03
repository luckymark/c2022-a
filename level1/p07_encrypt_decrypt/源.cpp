#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int main() {
	int result = 1;
	int i;
	int count = 0;
	char text[128] = { '\0' };//存放明文字符串
	char cryptograph[128] = { '\0' };//存放密文字符串

	while (1)
	{
		if (result == 1)
		{
			printf("请输出要加密的明文：\n");
			scanf_s("%s", &text);
			count = strlen(text);
			for (i = 0; i < count; i++)
			{
				cryptograph[i] = text[i] + i + 5;//加密
			}
			cryptograph[i] = '\0';
			printf("加密后的密文是:%s\n", cryptograph);
		}
		else if (result == 2)
		{
			count = strlen(text);
			for (i = 0; i < count; i++)
			{
				text[i] = cryptograph[i] - i - 5;//解密
			}
			text[i] = '\0';
			printf("解密后的明文是：%s\n", text);
		}
		else if (result == 3)
		{
			break;
		}
		else
		{
			printf("请按提示输入：\n");
		}

		printf("输入1加密明文，输入2对刚加密的明文进行解密，输入3退出程序：\n");
		printf("请按提示输入：\n");
		scanf_s("%d", &result);
	}

	return 0;
}
