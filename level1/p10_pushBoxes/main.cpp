#include <cstdlib>
#include "Init.h"

int main() {
    system("chcp 65001");
    system("cls");
    Init();
    while (1){
        movewbox();
    }
    system("pause");
    return 0;
}
