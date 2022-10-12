#include <stdio.h>
#include <string.h>

void encrypt();
void decrypt();
int main()
{
    int n;
    printf("如果想要加密，请按0\n如果想要解密，请按1\n");
    scanf_s("%d", &n);
    if (n == 0)
        encrypt();
    else if (n == 1)
        decrypt();
    else printf("error");

    return 0;
}

void encrypt()
{
    int text,i;
    char m[1000] = { '\0' }, c[1000] = { '\0' };;
    printf("请输入您想加密的内容\n");
    scanf_s("%s", &m,1000);
    for (i = 0; m[i]!=0; i++)
        c[i] = m[i] + i + 41;
    printf("加密后的密文是(请记录下密文)%s\n", c);

}
void decrypt() {
    int text, i;
    char m[1000] = { '\0' }, c[1000] = { '\0' };
    printf("请输入密文\n");
    scanf_s("%s", &c,1000);
    for (i = 0; c[i]!=0; i++)
        m[i] = c[i] -i - 41;
    printf("解密后的内容是%s\n", m);
}