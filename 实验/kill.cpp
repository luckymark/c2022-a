//
// Created by XuanCheng on 2023/2/5.
//

#include "kill.h"

using namespace std;

bool cmp(const poi x, const poi y) {
    return x.score > y.score;
}

bool find(int color, int score, vector<poi> &points) {
    vector<poi>result;
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 14; ++j) {
            if(board[i][j] == R.emp){
                poi p;
                if(HasNeighbor(i,j,2,2)){
                    if(color == R.emp){
                        board[i][j] = R.hum;
                        int scoreHum = score_point(i,j,R.hum);
                        board[i][j] = R.emp;
                        board[i][j] = R.com;
                        int scoreCom = score_point(i,j,R.com);
                        board[i][j] = R.emp;

                        int s = scoreHum + scoreHum;
                        if(s > score){
                            p.score = s;
                            result.push_back(p);
                        }
                    }else{
                        board[i][j] = color;
                        int s = score_point(i,j,color);
                        board[i][j] = R.emp;
                        if(s >= score){
                            p.score = s;
                            result.push_back(p);
                        }
                    }
                }
            }
        }
    }
    sort(result.begin(), result.end(), cmp);
    points = result;
    return true;
}

bool maxx(int color, int deep, vector<poi> &result) {
    int w = wincondition();
    if(w == color){
        return true;
    }
    if(w == R.trans(color) || deep < 0){
        return false;
    }
    
    vector<poi>points;
    find(color, FOUR_DIE_SCORE, points);
    if(points.empty()){
        return false;
    }
    for(int i = 0;i < points.size();++i){
        result.clear();
        pair<int,int>p = points[i].coor;
        board[p.first][p.second] = color;
        bool m = minn(color, deep-1, result);
        if(m){
            result.insert(result.begin(),points[i]);
            return true;
        }
    }
    return false;
}

bool minn(int color, int deep, vector<poi> &result) {
    result.clear();
    int w = wincondition();
    if(w == color){
        return true;
    }
    if(w == R.trans(color) || deep < 0){
        return false;
    }

    vector<poi>points;
    find(color, FOUR_DIE_SCORE, points);
    if(points.empty()){
        return false;
    }
    vector<vector<poi>> candidates;
    for(int i = 0;i < points.size();++i){
        result.clear();
        pair<int,int>p = points[i].coor;
        board[p.first][p.second] = R.trans(color);
        bool m = minn(color, deep-1, result);
        if(m){
            result.insert(result.begin(),points[i]);
            candidates.push_back(result);
            continue;
        }else{
            return false;
        }
    }
    int k = (int)(((int)(candidates.size()-1))*random());
    result = candidates[k];
    return true;
}

bool kill(int color, int deep, vector<poi> &result) {
    result.clear();
    if(deep <= 0){
        return false;
    }
    for (int i = 2; i <= deep; i += 2) {
        bool m = maxx(color, i, result);
        if(m){
            return true;
        }
    }
    return false;
}

