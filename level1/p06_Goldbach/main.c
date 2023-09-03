#include <stdio.h>

int team[25];
int Prime(int prime,int times) {
    for (prime = 2; prime <= 100; prime++) {
        for (int time = 2; time <= prime; ++time) {
            if (prime % time == 0)
                if (time == prime){
                    team[times]=prime;
                    times++;}
                else
                    break;
        }
    }
}

int main() {
    int limit=0;
    Prime(2,1);
    for (int n = 2; n <= 50; ++n) {
        for (int i = 1; i < 26; ++i) {
            for (int j = 1; j < 26; ++j) {
            if(team[i]+team[j] == 2*n)
            limit++;
            }
        }
        printf("%d有%d个哥德巴赫组合\n",2*n,limit);
        limit=0;
    }
    return 0;
}
