#include <stdio.h>
#include <string.h>

void encrypt(char* str, int key) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] ^= key;
    }
}

void decrypt(char* str, int key) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] ^= key;
    }
}

int main() {
    char str[] = "secret message";
    int key = 128;
    encrypt(str, key);
    printf("Encrypted message: %s\n", str);
    decrypt(str, key);
    printf("Decrypted message: %s\n", str);
    return 0;
}
