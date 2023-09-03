#include <stdio.h>

char encryption(char import){
    while (1) {
        import = getchar();
        if (import == '\n')
            break;
        putchar(import + 4);
    }
    return import;
}

char decode(char output){
    while (1){
        output = getchar();
        if (output == '\n')
            break;
        putchar(output - 4);
    }
    printf("%s\n",output);
}
int main() {
    int number;
    char command;
    printf("1.加密\n2.解密\n");
    scanf("%d",&number);
    switch (number) {//这里总会让你输两遍口令，我也不知道怎么回事。
        case 1:
            printf("请输入要加密的内容\n");
            scanf("%s\n",&command);
            encryption(command);
            printf("%s\n",command);
            break;
        case 2:
            printf("请输入要解密的内容\n");
            scanf("%s\n",&command);
            decode(command);
            printf("%s\n",command);
    }
    return 0;
}
