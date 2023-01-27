//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"
#include "AI.h"

using namespace std;

vector<int>position;
int c = 1;

vector<int> genboard(int deep) {

    vector<int>temp;
    vector<int>fives;
    vector<int>fours;
    vector<int>doubleThrees;
    vector<int>threes;
    vector<int>twos;
    vector<int>neighbors;
    vector<int>nextNeighbors;

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(board[i][j] == R.emp){
                if (HasNeighbor(i,j,1,1)){
                    int scoreHum = score_point(i,j,R.hum);
                    int scoreCom = score_point(i,j,R.com);

                    if(scoreCom >= FIVE_SCORE){
                        temp.push_back(i);
                        temp.push_back(j);
                        return temp;
                    }else if(scoreHum >= FIVE_SCORE){
                        fives.push_back(i);
                        fives.push_back(j);
                    } else if (scoreHum >= FOUR_SCORE){
                        fours.push_back(i);
                        fours.push_back(j);
                    }else if(scoreCom >= FOUR_SCORE){
                        fours.insert(fours.begin(),j);
                        fours.insert(fours.begin(),i);
                    }else if(scoreHum >= 2*THREE_SCORE){
                        doubleThrees.push_back(i);
                        doubleThrees.push_back(j);
                    }else if(scoreCom >= 2*THREE_SCORE){
                        doubleThrees.insert(doubleThrees.begin(),j);
                        doubleThrees.insert(doubleThrees.begin(),i);
                    } else if(scoreCom >= THREE_SCORE){
                        threes.insert(threes.begin(),j);
                        threes.insert(threes.begin(),i);
                    }else if(scoreHum >= THREE_SCORE){
                        threes.push_back(i);
                        threes.push_back(j);
                    }else if (scoreCom >= TWO_SCORE){
                        twos.insert(twos.begin(),j);
                        twos.insert(twos.begin(),i);
                    } else if (scoreHum >= TWO_SCORE){
                        twos.push_back(i);
                        twos.push_back(j);
                    } else {
                        neighbors.push_back(i);
                        neighbors.push_back(j);
                    }
                }else if(deep >= 2 && HasNeighbor(i,j,2,2)){
                    nextNeighbors.push_back(i);
                    nextNeighbors.push_back(j);
                }
            }
        }
    }

    if(!fives.empty()) return fives;
    if(!fours.empty()) return fours;
    if(!doubleThrees.empty()) return doubleThrees;

    //此处temp用于储存拼接结果
    temp.insert(temp.end(),threes.begin(),threes.end());
    temp.insert(temp.end(),twos.begin(),twos.end());
    temp.insert(temp.end(),neighbors.begin(),neighbors.end());
    temp.insert(temp.end(),nextNeighbors.begin(),nextNeighbors.end());
    return temp;
}

int maxx(int deep, int alpha, int beta, int color) {
    int v = score(color);
    //迭代终止
    if (deep <= 0 || v >= FIVE_SCORE) {
        return v;
    }

    int best = MIN;
    vector<int>points = genboard(deep);

    for (int i = 0; i < points.size(); i += 2) {
        board[points[i]][points[i + 1]] = color;
        v = minn(deep - 1, alpha, best > beta ? best : beta);
        board[points[i]][points[i + 1]] = 0;
        if (v > best) {
            best = v;
        }
        if (v > alpha) {
            break;
        }
    }
    return best;
}

int minn(int deep, int alpha, int beta, int color) {
    int v = score(color);
    //迭代终止
    if (deep <= 0 || v >= 999999) {
        return v;
    }

    int best = MAX;
    vector<int>points = genboard(deep);

    for (int i = 0; i < points.size(); i += 2) {
        board[points[i]][points[i + 1]] = R.hum;
        v = maxx(deep - 1,best<alpha ? best : alpha, beta);
        board[points[i]][points[i + 1]] = 0;
        if (v < best) {
            best = v;
        }
        if (v < beta) {
            break;
        }
    }
    return best;
}

vector<int> maxmin(int deep, int color) {
    int best = MIN;
    int beta = MIN;
    int alpha = MAX;
    vector<int>temp;
    int v;

    vector<int>points = genboard(deep);
    for (int i = 0; i < points.size(); i += 2){
        board[points[i]][points[i + 1]] = color;
        v = maxx(deep - 1, alpha, beta, color);
        if (v == best){//将新的节点加入position中
            position.push_back(points[i]);
            position.push_back(points[i+1]);
        } else if(v > best){//清除之前的节点，将新的节点加入position中
            best = v;
            position.clear();
            position.push_back(points[i]);
            position.push_back(points[i+1]);
        }
        board[points[i]][points[i+1]] = 0;
    }
    //生成随机数
    int k;
    k = random(position);
    if(k % 2 != 0){
        k = k - 1;
    }
    temp.push_back(position[k]);
    temp.push_back(position[k+1]);
    return temp;
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
        vector<int>bestpos = maxmin(4);
        solidcircle(X[bestpos[0]], Y[bestpos[1]], 28);
        board[bestpos[0]][bestpos[1]] = R.com;
        clearrectangle(913, 0, 1500, 30);
    }
    else if(c == 1) {
        if (board[8][8] == 0) {
            solidcircle(X[8], Y[8], 28);
            board[8][8] = R.com;
            clearrectangle(913, 0, 1500, 30);
        }
        else {
            solidcircle(X[9], Y[9], 28);
            board[9][9] = R.com;
            clearrectangle(913, 0, 1500, 30);
        }
    }
    c++;
    //
    int k = score(R.com);
    printf("com:%d\n",k);
    //
}

int random(const vector<int>& vec) {
    random_device rd;
    auto gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(0,(int )vec.size());
    int randk = dis(gen);
    return randk;
}

void AIdo(){
    AI();
    finish();
}

int HasNeighbor(int i, int j, int length, int wideth)   {
    for(int m = i - length ;m>0 && m<15 && m <= i+length; m++){
        for(int n = j - length ;n>0 && n<15 && n <= j+length; n++){
            if(m != n && board[m][n] != 0){
                return 1;
            }
        }
    }
    return 0;
}
