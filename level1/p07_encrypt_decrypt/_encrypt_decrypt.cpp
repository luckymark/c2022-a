#include<stdio.h>
#include<string.h>
#define max 0x7fffffff
char str[max],res[max];

void encrypt(int key,int len)
{
	for (int i = 0; i <= len; i++)
	{
		str[i] = str[i] + key;
	}
}

void decrypt(int key,int len)
{
	for (int i = 0; i <= len; i++)
	{
		str[i] = str[i] - key;
	}
}

int main()
{
	int choice,key,len,password;
	while (1)
	{
		printf("\npress '1' to encrypt, press '2' to decrypt，press '3' to leave\n");
		scanf_s("%d", &choice);
		if (choice == 1)
		{
			printf("Your string is:");
			scanf_s("%s", str);
			printf("Your key is:");
			scanf_s("%d", &key);
			len = strlen(str);
			encrypt(key, len);
			printf("Encrypting Finished\n");
		}
		if (choice == 2)
		{
			printf("Enter your key:");
			scanf_s("%d", &password);
			if (password != key)
			{
				printf("error\n");
			}
			else
			{
				decrypt(key, len);
				printf("%s\n", str);
			}
		}
		if (choice == 3)
		{
			break;
		}
		if ((choice != 1) && (choice != 2))
		{
			printf("error\n");
		}
	}
	

	return 0;

}