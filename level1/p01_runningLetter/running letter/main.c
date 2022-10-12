#include <stdio.h>
#include "windows.h"

int Step,Time,MagicNumber1,MagicNumber2;
void Cycle(void){
    while (Step>MagicNumber2){
        printf(" ");
        Step--;
    }
}
void Walk(void) {
    if (Time <= MagicNumber1 && Time >= MagicNumber2)
        while (Time <= MagicNumber1 && Time >= MagicNumber2){
            Time++;
            Step=Time;
            Cycle();
            printf("RUNNING LETTER");
            system("cls");
        }
    else
        Time=-Time;
        while (Time<MagicNumber2){
            Time++;
            Step= abs(Time);
            Cycle();
            printf("RUNNING LETTER");
            system("cls");
    }
}
int main(void ) {
    MagicNumber1=100;
    MagicNumber2=0;
    Step=Time=0;
    while (1){
        Walk();
    }
    return 0;
}
