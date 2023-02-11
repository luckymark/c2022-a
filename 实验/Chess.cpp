//
// Created by XuanCheng on 2023/2/11.
//

#include "Chess.h"

Board board;
role R;
int GameRound = 1;

int main(){
    GUI::Init();
    int w = 0;
    while(true) {
        if (R.com == 1) {

            AI::AIdo();
            w = GUI::win();
            if(w){
                break;
            }

            GUI::HumanDo();
            w = GUI::win();
            if(w){
                break;
            }
        } else if (R.com == 2) {

            GUI::HumanDo();
            w = GUI::win();
            if(w){
                break;
            }

            AI::AIdo();
            w = GUI::win();
            if(w){
                break;
            }
        }
    }
    system("pause");
    return 0;
}