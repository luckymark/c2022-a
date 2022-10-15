#include <stdio.h>

int Number,Factor;
void Judge(void){
    while (Number>Factor){
        Factor++;
        if (Number % Factor == 0)
            break;
    }
    if (Number == Factor)
        printf("%d是素数\n",Number);
    else
        printf("%d不是素数\n",Number);
}
int main(void ) {
    while (1) {
        Factor=2;
        printf("请输入你想判断的数字：\n");
        scanf("%d", &Number);
        Judge();
        continue;
    }
}
