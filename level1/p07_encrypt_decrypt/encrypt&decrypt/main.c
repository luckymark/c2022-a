#include<stdio.h>
#define LEN 20

void encrypt(char x[],int i);
void decrypt(char x[],int i);

int main(void)
{
    char arr[LEN];
    int c;
    printf("push '1' to encrypt, '2' to decrypt.\n");
    scanf("%d",&c);
    if(c==1) {
        scanf("%s",arr);
        for (int i = 0; i < LEN; i++) {
            encrypt(arr, i);
        }
        printf("%s\n", arr);
    }
    if(c==2) {
        scanf("%s",arr);
        for (int i = 0; i < LEN; i++) {
            decrypt(arr, i);
        }
        printf("%s\n", arr);
    }
    return 0;
}

void decrypt(char x[],int i){
    if( (x[i] >= 'a' && x[i] <= 'z' ) || ( x[i] >= 'A' && x[i] <= 'Z'))
    {
        if((x[i] >= 'a' && x[i] <= 'v' ) || ( x[i] >= 'A' && x[i] <= 'V'))
        {
            x[i] = x[i] +1;
            i++;
        }
        else
        {
            x[i] = x[i] - 2;
            i++;
        }
    }
}

void encrypt(char x[],int i){
    if( (x[i] >= 'a' && x[i] <= 'z' ) || ( x[i] >= 'A' && x[i] <= 'Z'))
    {
        if((x[i] >= 'a' && x[i] <= 'v' ) || ( x[i] >= 'A' && x[i] <= 'V'))
        {
            x[i] = x[i] - 1;
            i++;
        }
        else
        {
            x[i] = x[i] + 2;
            i++;
        }
    }
}