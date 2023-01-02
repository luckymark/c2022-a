#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#define KEY 2
void encrypt();
void decrypt();
int main()
{
	while (1) {
		char enter;
		printf("enter 1 to encrypt, enter 2 to decrypt, enter otner key to quit\n");
		scanf("%1c", &enter);
		rewind(stdin);
		if (enter == '1') encrypt();
		else if (enter == '2') decrypt();
		else break;
	}
	return 0;
}
void encrypt()
{		
	char sentence1[10005];
	int up = 32;
	printf("plz input the sentence that U want to encrypt\n");
	scanf("%[^\n]", sentence1);
	rewind(stdin);
	int len = strlen(sentence1);
	for (int i = 0; i < len; i++) {
		if ((int)sentence1[i] + KEY <= 126) sentence1[i] += KEY;
		else sentence1[i] = sentence1[i] - 127 + up + KEY;
	}
	printf("%s\n", sentence1);
}

void decrypt()
{
	char sentence2[10005];
	int up = 32;
	printf("plz input the sentence that U want to decrypt\n");
	scanf("%[^\n]", sentence2);
	rewind(stdin);
	int len = strlen(sentence2);
	for (int i = 0; i < len; i++) {
		if ((int)sentence2[i] - KEY >= up) sentence2[i] -= KEY;
		else sentence2[i] = 127-(up-(sentence2[i]- KEY));
	}
	printf("%s\n", sentence2);
}