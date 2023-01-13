#include "Chess.h"
#include <windows.h>

int board[20][20];
col R;

int main(){
    Init();

    while(true) {
        if (R.com == 1) {
            AIdo();
            Humdo();
        } else if (R.com == 2) {
            Humdo();
            AIdo();
        }
    }
    system("pause");
    return 0;
}