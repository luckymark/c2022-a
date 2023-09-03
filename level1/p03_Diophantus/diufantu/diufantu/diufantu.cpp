#include <stdio.h>

int main() {
	int manAge = 0;
	int left= manAge / 6 + manAge / 12 + manAge / 7 + 5 + manAge / 2 + 4;
	do {
		where: manAge = (left + manAge) / 2;
	left = manAge / 6 + manAge / 12 + manAge / 7 + 5 + manAge / 2 + 4;
	} while (left < manAge);
	if (left > manAge) {
		left += 200;
		goto where;
	}
	printf("diufantu's age was %d", manAge);
	return 0;
}