#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    for (n = 4; n <= 100; n += 2) {
        int flag = 0;
        for (int i = 2; i <= n / 2; i++) {
            if (is_prime(i) && is_prime(n - i)) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf("%d cannot be written as the sum of two prime numbers.\n", n);
            return 0;
        }
    }
    printf("All even numbers between 4 and 100 can be written as the sum of two prime numbers.\n");
    return 0;
}