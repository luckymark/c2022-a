#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define key 3
#define strLen 5
void extend(char s[], int len) {
	int l = strLen;
	while (l < len) {
		s = (char*)realloc(s, sizeof(char*) * (++l));
	}
}
void encrypt(char s[], char a[], int length) {
	for (int j = 0; j < strlen(s); j++) {
		if ('a' <= s[j] && s[j] <= 'z') a[j] = (s[j] - 'a' + key) % 26 + 'a';
		else if ('A' <= s[j] && s[j] <= 'Z') a[j] = (s[j] - 'A' + key) % 26 + 'A';
	}
}
void decrypt(char a[], char b[], int length) {
	for (int i = 0; i < strlen(a); i++) {
		if ('a' <= a[i] && a[i] <= 'z') b[i] = (a[i] - 'a' + 26 - key) % 26 + 'a';
		else if ('A' <= a[i] && a[i] <= 'Z') b[i] = (a[i] - 'A' + 26 - key) % 26 + 'A';
	}
}
int main() {
	int length = 0, c_strLen = strLen; //c_strLen：默认字符数组初始长度，可改变
	char ch;
	char* str = (char*)malloc(sizeof(char*) * strLen);
	char* crypt = (char*)malloc(sizeof(char*) * strLen);
	char* original = (char*)malloc(sizeof(char*) * strLen);

	do {
		ch = getchar();
		length++;
		if (length >= c_strLen){
			str = (char*)realloc(str, sizeof(char*) * (++c_strLen));
		}
		str[length - 1] = ch;
	} while (ch != '\n');

	extend(crypt, length);
	extend(original, length);

	encrypt(str, crypt, length);
	decrypt(crypt, original, length);
	
	for (int i = 0; i < strlen(str); i++) printf("%c", crypt[i]);
	printf("\n");
	for (int i = 0; i < strlen(str); i++) printf("%c", original[i]);
	return 0;
}