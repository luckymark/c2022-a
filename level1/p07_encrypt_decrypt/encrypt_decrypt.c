#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
int main()
{
	int n = 2;
	void encrypt(int num);
	void decrypt(int num);
	while (1) {
		char enter;
		printf("enter 1 to encrypt, enter 2 to decrypt, enter otner key to quit\n");
		scanf("%c", &enter);
		rewind(stdin);
		fflush(stdin);
		if (enter == '1') encrypt(n);
		else if (enter == '2') decrypt(n);
		else break;
	}
	return 0;
}
void encrypt(int num)
{		
	char sentence1[10005];
	int up = 32;
	scanf("%[^\n]", sentence1);
	rewind(stdin);
	int len = strlen(sentence1);
	for (int i = 0; i < len; i++) {
		if ((int)sentence1[i] + num <= 126) sentence1[i] += num;
		else sentence1[i] = sentence1[i] - 127 + up + num;
	}
	printf("%s\n", sentence1);
}

void decrypt(int num)
{
	char sentence2[10005];
	int up = 32;
	scanf("%[^\n]", sentence2);
	rewind(stdin);
	int len = strlen(sentence2);
	for (int i = 0; i < len; i++) {
		if ((int)sentence2[i] - num >= up) sentence2[i] -= num;
		else sentence2[i] = 126-sentence2[i]-num+up;
	}
	printf("%s\n", sentence2);
}