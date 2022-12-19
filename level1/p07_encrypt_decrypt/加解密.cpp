#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#define Max 10000
char OUT[Max], IN[Max];
void encrypt(int len, int pass, char IN[], char OUT[]) {
	for (int i = 0;i < len;i++) {
		OUT[i] = IN[i] + pass;
		cout << 1 << endl;
	}
}
void decrypt(int len, int pass, char IN[], char OUT[]) {
	for (int i = 0;i < len;i++) {
		OUT[i] = IN[i] - pass;
	}
}
int main() {
	int pass;
	char c;
	printf("'E' to encrypt,'D' to decrypt");
	scanf_s("%c", &c);
	printf("Input your string");
	scanf_s("%s", IN,1000);
	int len = strlen(IN);
	printf("Input your pass");
	scanf_s("%d", &pass);
	cout << len << endl;
	if (c == 'E') {
		encrypt(len, pass,IN, OUT);
	}
	else if (c == 'D') {
		decrypt(len, pass,IN,OUT);
	}
	for (int i = 0;i < len;i++) {
		printf("%c", OUT[i]);
	}
	return 0;
}

