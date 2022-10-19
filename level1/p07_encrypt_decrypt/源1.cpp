#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int main()
{
	int i;
	char passage[128] = {};
	char hide[128] = {};
	int n;
	int m = 0, y = 0, flag = 0;
	while (1)
	{
		printf("输入1，执行加密字符并显示加密字符\n""输入2对字符解密并显示解密字符\n"
			"输入3，结束程序\n");
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:
			scanf_s("%s", passage, 126);
			m = strlen(passage);
			for (i = 0; i < m; i++)
			{
				hide[i] = passage[i] + i - 3;
			}
			printf("%s\n", hide);
			break;
		case 2:
			scanf_s("%s", hide, 126);
			y = strlen(hide);
			for (i = 0; i < y; i++)
			{
				passage[i] = hide[i] + 3 - i;
			}
			printf("%s\n", passage);
			break;
		case 3:
			flag = 1;
			break;
		default:
			break;
		}
		while (flag == 1)
			break;
	}
}