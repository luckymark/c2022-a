//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"
#include "AI.h"

using namespace std;

int c = 1;

bool genboard(int deep, vector<pair<int,int>> &points) {
    vector<pair<int,int>>fives;
    vector<pair<int,int>>fours;
    vector<pair<int,int>>doubleThrees;
    vector<pair<int,int>>threes;
    vector<pair<int,int>>twos;
    vector<pair<int,int>>neighbors;
    vector<pair<int,int>>nextNeighbors;
    pair<int,int>temp;

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(board[i][j] == R.emp){
                if (HasNeighbor(i,j,1,1)){
                    board[i][j] = R.hum;
                    int scoreHum = score_point(i,j,R.hum);
                    board[i][j] = R.emp;

                    board[i][j] = R.com;
                    int scoreCom = score_point(i,j,R.com);
                    board[i][j] = R.emp;

                    if(scoreCom >= FIVE_SCORE){
                        temp.first = i;
                        temp.second = j;
                        points.push_back(temp);
                        return true;
                    }else if(scoreHum >= FIVE_SCORE){
                        temp.first = i;
                        temp.second = j;
                        fives.push_back(temp);
                    } else if (scoreHum >= FOUR_SCORE){
                        temp.first = i;
                        temp.second = j;
                        fours.push_back(temp);
                    }else if(scoreCom >= FOUR_SCORE){
                        temp.first = i;
                        temp.second = j;
                        fours.insert(fours.begin(),temp);
                    }else if(scoreHum >= 2*THREE_SCORE){
                        temp.first = i;
                        temp.second = j;
                        doubleThrees.push_back(temp);
                    }else if(scoreCom >= 2*THREE_SCORE){
                        temp.first = i;
                        temp.second = j;
                        doubleThrees.insert(doubleThrees.begin(),temp);
                    } else if(scoreCom >= THREE_SCORE){
                        temp.first = i;
                        temp.second = j;
                        threes.insert(threes.begin(),temp);
                    }else if(scoreHum >= THREE_SCORE){
                        temp.first = i;
                        temp.second = j;
                        threes.push_back(temp);
                    }else if (scoreCom >= TWO_SCORE){
                        temp.first = i;
                        temp.second = j;
                        twos.insert(twos.begin(),temp);
                    } else if (scoreHum >= TWO_SCORE){
                        temp.first = i;
                        temp.second = j;
                        twos.push_back(temp);
                    } else {
                        temp.first = i;
                        temp.second = j;
                        neighbors.push_back(temp);
                    }
                    //change
                }else if(deep >= 2 && HasNeighbor(i,j,2,2)){
                    temp.first = i;
                    temp.second = j;
                    nextNeighbors.push_back(temp);
                }
            }
        }
    }

    if(!fives.empty()){
        points = fives;
        return true;
    }
    if(!fours.empty()){
        points = fours;
        return true;
    }
    if(!doubleThrees.empty()){
        points = doubleThrees;
        return true;
    }

    //此处temp用于储存拼接结果
    points.insert(points.end(),threes.begin(),threes.end());
    points.insert(points.end(),twos.begin(),twos.end());
    points.insert(points.end(),neighbors.begin(),neighbors.end());
    points.insert(points.end(),nextNeighbors.begin(),nextNeighbors.end());
    return true;
}

int negamax(int deep, int alpha, int beta, int color) {
    int v = score(color);
    if(deep <= 0 || wincondition()){
        return v;
    }

    int best = MIN;
    vector<pair<int,int>>points;
    genboard(deep, points);

    for (int i = 0; i < points.size(); ++i) {
        pair<int,int>p = points[i];
        board[p.first][p.second] = color;
        alpha = max(best, alpha);
        v = -negamax(deep - 1, -beta, -alpha, R.trans(color));
        board[p.first][p.second] = R.emp;
        if(v > best){
            best = v;
        }
        if(v >= beta){
            return v;
        }
    }
    return best;
}

void AI() {
    fontset(BLACK, 24, ANTIALIASED_QUALITY, _T("黑体"));
    outtextxy(913, 0, _T("伟大机器人正在推翻人类暴政 "));
    if (R.com == 1) {
        setfillcolor(BLACK);
    }
    else {
        setfillcolor(WHITE);
    }

    if(c>1)
    {
        //vector<int>bestpos = maxmin(4);
        solidcircle(X[bestpos[0]], Y[bestpos[1]], 28);
        board[bestpos[0]][bestpos[1]] = R.com;
        clearrectangle(913, 0, 1500, 30);
    }
    else if(c == 1) {
        if (board[7][7] == 0) {
            solidcircle(X[7], Y[7], 28);
            board[7][7] = R.com;
            clearrectangle(913, 0, 1500, 30);
        }
        else {
            solidcircle(X[8], Y[8], 28);
            board[8][8] = R.com;
            clearrectangle(913, 0, 1500, 30);
        }
    }
    c++;
    //
    int k = score(R.com);
    printf("com:%d\n",k);
    //
}

double random() {
    random_device rd;
    auto gen = default_random_engine(rd());
    uniform_real_distribution<double> dis(0,1);
    double randk = dis(gen);
    return randk;
}
void AIdo(){
    AI();
    finish();
}

int HasNeighbor(int i, int j, int length, int wideth)   {
    for(int m = i - length ;m>=0 && m<15 && m <= i+length; m++){
        for(int n = j - wideth ;n>=0 && n<15 && n <= j+wideth; n++){
            if(m != n && board[m][n] != 0){
                return 1;
            }
        }
    }
    return 0;
}
