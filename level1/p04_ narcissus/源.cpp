#include <stdio.h>
#include <math.h>
int main() {
	int x, s = 0;
	for (int i = 100; i < 1000; i++) {
		x = i;
		for (int j = 0; j < 3; j++) {
			s += pow(x % 10, 3);
			x /= 10;
		}
		if (i == s) printf("%d ", i);
		s = 0;
	}
	return 0;
}