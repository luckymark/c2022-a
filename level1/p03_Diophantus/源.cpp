#include <stdio.h>
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}
int lcm(int a, int b) {
	return a * b / gcd(a, b);
}
int main() {
	int y, x1, x2;
	x1 = lcm(6, 12);
	x2 = lcm(7, 2);
	y = lcm(x1, x2);
	printf("%d", y);
	return 0;
}