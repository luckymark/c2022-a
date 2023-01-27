//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"
#include "AI.h"

using namespace std;

vector<int>points;
int c = 1;

vector<int> genboard(int color,int deep) {

    vector<int>temp;
    vector<int>fives;
    vector<int>fours;
    vector<int>doubleThrees;
    vector<int>threes;
    vector<int>twos;
    vector<int>neighbors;
    vector<int>nextNeighbors;

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
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
                    } else if (scoreHum >= FOUR_LIVE_SCORE){
                        fours.push_back(i);
                        fours.push_back(j);
                    }else if(scoreCom >= FOUR_LIVE_SCORE){
                        fours.insert(fours.begin(),j);
                        fours.insert(fours.begin(),i);
                    }else if(scoreHum >= 2*THREE_LIVE_SCORE){
                        doubleThrees.push_back(i);
                        doubleThrees.push_back(j);
                    }else if(scoreCom >= 2*THREE_LIVE_SCORE){
                        doubleThrees.insert(doubleThrees.begin(),j);
                        doubleThrees.insert(doubleThrees.begin(),i);
                    } else if(scoreCom >= THREE_LIVE_SCORE){
                        threes.insert(threes.begin(),j);
                        threes.insert(threes.begin(),i);
                    }else if(scoreHum >= THREE_LIVE_SCORE){
                        threes.push_back(i);
                        threes.push_back(j);
                    }else if (scoreCom >= TOW_SCORE){
                        twos.insert(twos.begin(),j);
                        twos.insert(twos.begin(),i);
                    } else if (scoreHum >= TOW_SCORE){
                        twos.push_back(i);
                        twos.push_back(j);
                    } else {
                        neighbors.push_back(i);
                        neighbors.push_back(j);
                    }
                }else if(deep >= 2 && HasNeighbor(i,j,2,2)){
                    nextNeighbors.push_back(i);
                    nextNeighbors.push_back(j);
                };
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
    pos points[MOSTPOS];
    genboard(color,points);
    for (int i = 0; i < MOSTPOS && points[i].x != -1; ++i) {
        board[points[i].x][points[i].y] = color;
        v = minn(deep - 1, alpha, best > beta ? best : beta);
        board[points[i].x][points[i].y] = 0;
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
    pos points[MOSTPOS];
    genboard(color, points);
    for (int i = MOSTPOS - 1; i >= 0 ; --i) {
        if (points[i].x == -1) {
            continue;
        }
        board[points[i].x][points[i].y] = R.hum;
        v = maxx(deep - 1,best<alpha ? best : alpha, beta);
        board[points[i].x][points[i].y] = 0;
        if (v < best) {
            best = v;
        }
        if (v < beta) {
            break;
        }
    }
    return best;
}

void maxmin(int deep, int color) {
    int best = MIN;
    int beta = MIN;
    int alpha = MAX;
    int v;
    int end = 0;
    pos points[MOSTPOS];
    //Init position
    for(int i = 0; i < MOSTPOS; ++i){
        position[i].x = -1;
        position[i].y = -1;
    }
    //body
    genboard(color, points);
    for (int i = 0; i < MOSTPOS && points[i].x != -1; ++i){
        board[points[i].x][points[i].y] = color;
        v = maxx(deep - 1, alpha, beta, color);
        if (v == best){//将新的节点加入position中
            position[end].x = points[i].x;
            position[end].y = points[i].y;
            end++;
        } else if(v > best){//清除之前的节点，将新的节点加入position中
            best = v;
            for (int j = 0; j < MOSTPOS; ++j) {
                position[j].x = -1;
                position[j].y = -1;
            }
            end = 0;
            position[end].x = points[i].x;
            position[end].y = points[i].y;
            end++;
        }
        board[points[i].x][points[i].y] = 0;
    }
    //produce random node
    int k = 1;
    for (int i = 0; i < MOSTPOS; ++i) {
        if (position[i].x == -1) {
            k = i - 1;
            break;
        }
    }
    //生成随机数
    int randnum;
    while(true) {
        randnum = random();
        if(position[randnum].x != -1) {
            bestpos.x = position[randnum].x;
            bestpos.y = position[randnum].y;
            break;
        }
    }
}

void AI() {
    maxmin(4);
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
        solidcircle(X[bestpos.x], Y[bestpos.y], 28);
        board[bestpos.x][bestpos.y] = R.com;
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

int random() {
    std::random_device rd;
    auto gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0,MOSTPOS);
    int randk = dis(gen);
    return randk;
}

void AIdo(){
    AI();
    finish();
}

int HasNeighbor(int i, int j, int length, int wideth) {
    for(int m = i - length ; m < i+length; m++){
        for(int n = i - length ; n < i+length; n++){
            if(m != n && board[m][n] != 0){
                return 1;
            }
        }
    }
    return 0;
}
