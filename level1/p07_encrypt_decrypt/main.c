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
    printf("1.����\n2.����\n");
    scanf("%d",&number);
    switch (number) {//�����ܻ���������������Ҳ��֪����ô���¡�
        case 1:
            printf("������Ҫ���ܵ�����\n");
            scanf("%s\n",&command);
            encryption(command);
            printf("%s\n",command);
            break;
        case 2:
            printf("������Ҫ���ܵ�����\n");
            scanf("%s\n",&command);
            decode(command);
            printf("%s\n",command);
    }
    return 0;
}
