#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int main() {
	int result = 1;
	int i;
	int count = 0;
	char text[128] = { '\0' };//��������ַ���
	char cryptograph[128] = { '\0' };//��������ַ���

	while (1)
	{
		if (result == 1)
		{
			printf("�����Ҫ���ܵ����ģ�\n");
			scanf_s("%s", &text);
			count = strlen(text);
			for (i = 0; i < count; i++)
			{
				cryptograph[i] = text[i] + i + 5;//����
			}
			cryptograph[i] = '\0';
			printf("���ܺ��������:%s\n", cryptograph);
		}
		else if (result == 2)
		{
			count = strlen(text);
			for (i = 0; i < count; i++)
			{
				text[i] = cryptograph[i] - i - 5;//����
			}
			text[i] = '\0';
			printf("���ܺ�������ǣ�%s\n", text);
		}
		else if (result == 3)
		{
			break;
		}
		else
		{
			printf("�밴��ʾ���룺\n");
		}

		printf("����1�������ģ�����2�Ըռ��ܵ����Ľ��н��ܣ�����3�˳�����\n");
		printf("�밴��ʾ���룺\n");
		scanf_s("%d", &result);
	}

	return 0;
}
