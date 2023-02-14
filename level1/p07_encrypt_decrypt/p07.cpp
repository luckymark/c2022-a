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


void creatmiyao(int textlen);     //生成密钥流

void RC4EncryptText(char* text);


int main()
{
	//char text[MAX]={"Talk is cheap show me the code"};
	char text[MAX];
	printf("请输入文本；\n");
	scanf_s("%s", text, MAX);
	//printf("\n密文:%s  \n",text);
	randmiyao();
	RC4EncryptText(text);
	system("pause");
}
void randmiyao()
{
	for (int i = 0; i < 256; i++)
		s[i] = i;
	int i;
	srand(time(NULL));      //随机密钥种子  or手动输入key
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
		j = (j + s[i] + T[i]) % 256;        //写了个值不变的循环，卡了半天！
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
	printf("\n========正在加密======\n");
	for (int i = 0; i < textlen; i++)
		printf("%c", crayptoText[i]);
	printf("\n========加密成功======\n");
	printf("\n========正在解密======\n");
	for (int i = 0; i < textlen; i++)
		plainText[i] = char(crayptoText[i] ^ keyStream[i]);
	for (int i = 0; i < textlen; i++)
		printf("%c", plainText[i]);
	printf("\n========解密成功======\n\n\n");
}
