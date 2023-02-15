#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAX 1024
int textlen;

int s[256];
char T[256];
int key[256];
int keyStream[256];
char plainText[MAX];
char crayptoText[MAX];
const char* wordlist = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void randmiyao();


void creatmiyao(int textlen);     //������Կ��

void RC4EncryptText(char* text);


int main()
{
	//char text[MAX]={"Talk is cheap show me the code"};
	char text[MAX];
	printf("�������ı���\n");
	scanf_s("%s", text, MAX);
	//printf("\n����:%s  \n",text);
	randmiyao();
	RC4EncryptText(text);
	system("pause");
}
void randmiyao()
{
	for (int i = 0; i < 256; i++)
		s[i] = i;
	int i;
	srand(time(NULL));      //�����Կ����  or�ֶ�����key
	int keylen = (int)((double)rand() / (double)RAND_MAX * 256);
	for (i = 0; i <= keylen; i++)
	{
		int index = (int)((double)rand() / (double)RAND_MAX * 62);
		key[i] = wordlist[index];
	}
	for (i = 0; i < 256; i++)
		T[i] = key[i % keylen];
	int j = 0;
	for (i = 0; i < 256; i++)
	{
		int temp;
		j = (j + s[i] + T[i]) % 256;        //д�˸�ֵ�����ѭ�������˰��죡
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}
void creatmiyao(int textlen)
{
	int i = 0, j = 0, index = 0, t, temp;
	while (textlen--)
	{
		i = (i + 1) % 256;
		j = (s[j] + j) % 256;
		temp = s[i];
		s[i] = s[j];
		s[j] = s[i];
		t = (s[j] + s[i]) % 256;
		keyStream[index] = s[t];
		index++;
	}
}
void RC4EncryptText(char* text)
{
	textlen = strlen(text);
	randmiyao();
	creatmiyao(textlen);
	for (int i = 0; i < textlen; i++)
		crayptoText[i] = char(text[i] ^ keyStream[i]);
	printf("\n========���ڼ���======\n");
	for (int i = 0; i < textlen; i++)
		printf("%c", crayptoText[i]);
	printf("\n========���ܳɹ�======\n");
	printf("\n========���ڽ���======\n");
	for (int i = 0; i < textlen; i++)
		plainText[i] = char(crayptoText[i] ^ keyStream[i]);
	for (int i = 0; i < textlen; i++)
		printf("%c", plainText[i]);
	printf("\n========���ܳɹ�======\n\n\n");
}
