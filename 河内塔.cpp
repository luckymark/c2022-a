#include<stdio.h>
void swap(int n, char a, char b, char c);
int count = 0;
int main(void) {
	char a = 'A', b = 'B', c = 'C';
	int n;
	scanf("%d", &n);
	swap(n, a, b, c);

}
void swap(int n, char a, char b, char c) {
	if (n > 1) {
		swap(n - 1, a, c, b);

		printf("%c->%c\t", a, b);
		printf("%d\n", ++count);
		swap(n - 1, c, b, a);
	} else {
		printf("%c->%c\t", a, b);
		printf("%d\n", ++count);
	}
}
//不知道咋写注释了，因为是穷举出来的
