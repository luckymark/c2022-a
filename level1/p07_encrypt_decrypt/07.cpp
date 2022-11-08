#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ASCII 127;
//写个凯撒密码..
//密文中，从首位开始加密，后一位以前一位为密钥：密文a位字符编码=原文a位字符编码+密文a-1位字符编码
//其中，密文1位和原文1位相同，当密文字符编码溢出时，对其取模127
char* encrypt(char* password,int strlen){
	int cnt=0;
	char* Piterator=password;
	Piterator++;
	cnt++;
	while(cnt<strlen){
		*Piterator=(*(Piterator-1)+*Piterator)%ASCII;
		Piterator++;
		cnt++;
	}
	return password;
}
//解密反过来，从末位开始解密，就是加密的逆运算（对称加密）
char* decrypt(char* ciphertext,int strlen){
	int cnt=strlen;
	char* Citerator=ciphertext+strlen-1;
	while(cnt>1){
		*Citerator=(*Citerator-*(Citerator-1));
		if(*Citerator<0){
			*Citerator+=ASCII;
		}
		Citerator--;
		cnt--;
	}
	return Citerator;
}
int main(){
	char* text;//原文
	char* ciphertext;//密文
	scanf("%s",text);
	ciphertext=encrypt(text,strlen(text));
	printf("%s\n",ciphertext);//展示密文..
	printf("%s",decrypt(text,strlen(text)));//还原
	return 0;
}
