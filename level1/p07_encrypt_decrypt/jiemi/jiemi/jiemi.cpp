//分别编写“加密”、“解密”函数，输入为任意长度的字符串
#include <stdio.h>
int jiami() {};
int jiemi() {};
int main() {char tempCharacter;
printf("加密方式：英文字母的ascii码除以26的余数，大写用1，小写用2作为前缀，@表示读取终止，可以输入空格");
printf("解密方式：三位数字，同上，空格为332，@为364");
	do{
	tempCharacter =getchar();
		jiami(tempCharacter);
	} while ((int) tempCharacter != 64);
	do {

	} while ();
	return 0;
}
int jiami(char c) {
		if ((c == 64) || (c== 32)) {
			printf("%d\n", 300 + (int)c / 26);
		}
		else {
			if (c < 95) {
				printf("%d\n", 100 + (int)c / 26);
			}
			else {
				printf("%d\n", 200 + (int)c / 26);
			}
		}
}
int jiemi(char tempCharacter) {
	if (((int ) tempCharacter)/100==3) {
		printf("")
		((int)tempCharacter) % 100;
	}
	else if (((int)tempCharacter) / 100 == 2) {

	}
	else{

	}
}