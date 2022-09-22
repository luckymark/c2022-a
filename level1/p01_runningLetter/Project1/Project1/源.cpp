#include <stdio.h>
#include <Windows.h>
int main() {
	const int LEFT = 0, RIGHT = 119, speed = 1;
	int n = 0, flag = -1;
	char x;
	scanf_s("%c", &x, 1);
	while (1) {
		if (n == LEFT || n == RIGHT) flag = -flag;
		for (int i = 0; i < n; i++) printf(" ");
		printf("%c", x);
		Sleep(speed);
		system("cls");
		n += flag;
	}
	return 0;
}