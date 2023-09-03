#include<stdio.h>

void move(int n, char A, char B) {
	printf("%-2d %c -> %c\n", n, A, B);
}
void helper(int n, char A, char B, char C) {
	void move(int n, char A, char C);
	if (n == 1) {
		move(1, A, C);
	}
	else {
		helper(n - 1, A, C, B);
		move(n, A, C);
		helper(n - 1, B, A, C);
	}

}
int main() {
	int MAX = 10;
	char A = 'a', B = 'b', C = 'c';
	helper(MAX, A, B, C);
	return 0;
}

