#include <stdio.h>

int Number,Factor;
void Judge(void){
    while (Number>Factor){
        Factor++;
        if (Number % Factor == 0)
            break;
    }
    if (Number == Factor)
        printf("%d??????\n",Number);
    else
        printf("%d????????\n",Number);
}
int main(void ) {
    while (1) {
        Factor=2;
        printf("???????????§Ø???????\n");
        scanf("%d", &Number);
        Judge();
        continue;
    }
}
