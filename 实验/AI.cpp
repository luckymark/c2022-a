//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"
#include "AI.h"

using namespace std;

int c = 1;

bool genboard(int deep, vector<poi>  &points) {
    vector<poi> fives;
    vector<poi> fours;
    vector<poi> doubleThrees;
    vector<poi> threes;
    vector<poi> twos;
    vector<poi> neighbors;
    vector<poi> nextNeighbors;
    poi temp;

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
                        temp.coor = {i,j};
                        points.push_back(temp);
                        return true;
                    }else if(scoreHum >= FIVE_SCORE){
                        temp.coor = {i,j};
                        fives.push_back(temp);
                    } else if (scoreHum >= FOUR_SCORE){
                        temp.coor = {i,j};
                        fours.push_back(temp);
                    }else if(scoreCom >= FOUR_SCORE){
                        temp.coor = {i,j};
                        fours.insert(fours.begin(),temp);
                    }else if(scoreHum >= 2*THREE_SCORE){
                        temp.coor = {i,j};
                        doubleThrees.push_back(temp);
                    }else if(scoreCom >= 2*THREE_SCORE){
                        temp.coor = {i,j};
                        doubleThrees.insert(doubleThrees.begin(),temp);
                    } else if(scoreCom >= THREE_SCORE){
                        temp.coor = {i,j};
                        threes.insert(threes.begin(),temp);
                    }else if(scoreHum >= THREE_SCORE){
                        temp.coor = {i,j};
                        threes.push_back(temp);
                    }else if (scoreCom >= TWO_SCORE){
                        temp.coor = {i,j};
                        twos.insert(twos.begin(),temp);
                    } else if (scoreHum >= TWO_SCORE){
                        temp.coor = {i,j};
                        twos.push_back(temp);
                    } else {
                        temp.coor = {i,j};
                        neighbors.push_back(temp);
                    }
                    //change
                }else if(deep >= 2 && HasNeighbor(i,j,2,2)){
                    temp.coor = {i,j};
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

int negamax(int deep, int alpha, int beta, int color, std::vector<poi> &candidates) {
    int v = score(color);
    if(deep <= 0 || wincondition()){
        return v;
    }

    int best = MIN;

    for (int i = 0; i < candidates.size(); ++i) {
        pair<int,int>p = candidates[i].coor;
        board[p.first][p.second] = color;
        alpha = max(best, alpha);
        v = -r(deep - 1, -beta, -alpha, R.trans(color));
        board[p.first][p.second] = R.emp;
        candidates[i].score = v;
        if(v > best){
            best = v;
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
        poi bestpos = GiveBestPoint();
        solidcircle(X[bestpos.coor.first], Y[bestpos.coor.second], 28);
        board[bestpos.coor.first][bestpos.coor.second] = R.com;
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

bool deeppp(int deep, int color, vector<poi> &result, vector<poi> &candidates) {
    int bestscore;
    for(int i = 2;i <=deep;i += 2){
        bestscore = negamax(i,MIN,MAX,color,candidates);
        if(bestscore == FIVE_SCORE){
            break;
        }
    }
    sort(candidates.begin(), candidates.end(), cmp);
    result.push_back((candidates[0]));
    for (int i = 0; i < candidates.size(); ++i) {
        if(candidates[i].score == candidates[i+1].score){
            result.push_back(candidates[i + 1]);
        }else{
            break;
        }
    }
    return false;
}

poi GiveBestPoint(int color, int deep) {
    vector<poi> candidates;
    genboard(deep, candidates);

    vector<poi> result;
    deeppp(deep, color, result, candidates);

    int k = (int)(((int)(result.size()-1))*random());
    return result[k];
}

int r(int deep, int alpha, int beta, int color) {
    //去除candidates干扰，集成算杀
    int v = score(color);
    if(deep <= 0 || wincondition()){
        return v;
    }

    int best = MIN;

    vector<poi>candidates;
    genboard(deep,candidates);

    for (int i = 0; i < candidates.size(); ++i) {
        pair<int,int>p = candidates[i].coor;
        board[p.first][p.second] = color;
        alpha = max(best, alpha);
        v = -r(deep - 1, -beta, -alpha, R.trans(color));
        board[p.first][p.second] = R.emp;
        if(v > best){
            best = v;
        }
        if(v >= beta){
            return v;
        }
        if(deep <= 2 && color == R.com && best < FOUR_SCORE && best > (FOUR_SCORE*(-1))){
            vector<poi>mate;
            bool m = kill(color, 8, mate);
            if(m){
                return FIVE_SCORE * pow(0.8,(double)mate.size());
            }
        }
    }
    return best;
}
