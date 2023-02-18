//
// Created by XuanCheng on 2023/2/11.
//

#include <algorithm>
#include <random>
#include "AI.h"
#include "Board.h"
#include "Chess.h"

using namespace std;

int AI::negamax(int deep, int alpha, int beta, int role, std::vector<point> &candidates) {
    int v;
    int best = MIN;

    for (auto & candidate : candidates) {
        pair<int,int>p = candidate.coor;
        board.put(p, role);
        v = -r(deep - 1, -beta, -alpha, R.trans(role));
        board.remove(p,role);
        alpha = max(best, alpha);
        candidate.score = v;
        if(v > best){
            best = v;
        }
    }
    return alpha;
}

int AI::r(int deep, int alpha, int beta, int role) {
    int v = board.score(role);
    if(deep <= 0 || GUI::WinCondition()){
        return v;
    }

    int best = MIN;

    vector<point>candidates;
    board.GenerateBoard(deep, role, candidates);

    for (auto & candidate : candidates) {
        pair<int,int>p = candidate.coor;
        board.put(p, role);
        alpha = max(best, alpha);
        v = -r(deep - 1, -beta, -alpha, R.trans(role));
        board.remove(p,role);
        if(v > best){
            best = v;
        }
        if(v >= beta){
            return v;
        }
        if(deep <= 2 && role == R.com && best < FOUR_SCORE && best > (FOUR_SCORE * (-1))){
            vector<point>mate;
            bool m = kill(role, 8, mate);
            if(m){
                return FIVE_SCORE * pow(0.8,(double)mate.size());
            }
        }
    }
    return best;
}

bool AI::deeppp(int deep, int color, std::vector<point> &result, std::vector<point> &candidates) {
    int bestscore;
    for(int i = 2;i <=deep;i += 2){
        bestscore = negamax(i,MIN,MAX,color,candidates);
        if(bestscore == FIVE_SCORE){
            break;
        }
    }
    sort(candidates.begin(), candidates.end(), cmp);
    result.push_back((candidates[0]));
    for (int i = 0; i < candidates.size() - 1; ++i) {
        if(candidates[i].score == candidates[i+1].score){
            result.push_back(candidates[i + 1]);
        }else{
            break;
        }
    }
    return false;
}

point AI::GiveBestPoint(int color, int deep) {
    vector<point> candidates;
    board.GenerateBoard(deep, color, candidates);

    vector<point> result;
    deeppp(deep, color, result, candidates);

    int k = (int)(((int)(result.size()-1))*random());
    return result[k];
}

bool AI::maxx(int role, int deep, vector<point> &result) {
    int w = GUI::WinCondition();
    if(w == role){
        return true;
    }
    if(w == R.trans(role) || deep < 0){
        return false;
    }

    vector<point>points;
    board.find(role, FOUR_DIE_SCORE, points);
    if(points.empty()){
        return false;
    }
    for(auto & point : points){
        result.clear();
        pair<int,int>p = point.coor;
        board.put(p, role);
        bool m = minn(role, deep - 1, result);
        board.remove(p,role);
        if(m){
            result.insert(result.begin(),point);
            return true;
        }
    }
    return false;
}

bool AI::minn(int role, int deep, vector<point> &result) {
    result.clear();
    int w = GUI::WinCondition();
    if(w == role){
        return true;
    }
    if(w == R.trans(role) || deep < 0){
        return false;
    }

    vector<point>points;
    board.find(role, FOUR_DIE_SCORE, points);
    if(points.empty()){
        return false;
    }
    vector<vector<point>> candidates;
    for(auto & point : points){
        result.clear();
        pair<int,int>p = point.coor;
        board.put(p,R.trans(role));
        bool m = minn(role, deep - 1, result);
        board.remove(p,R.trans(role));
        if(m){
            result.insert(result.begin(),point);
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

bool AI::kill(int color, int deep, vector<point> &result) {
    result.clear();
    for (int i = 2; i <= deep; i += 2) {
        bool m = maxx(color, i, result);
        if(m){
            return true;
        }
    }
    return false;
}

double AI::random() {
    random_device rd;
    auto gen = default_random_engine(rd());
    uniform_real_distribution<double> dis(0,1);
    double randk = dis(gen);
    return randk;
}

void AI::AIdo() {
    GUI::fontset(BLACK, 24, ANTIALIASED_QUALITY, _T("黑体 "));
    outtextxy(913, 0, _T("伟推翻人类暴政！ "));
    if (R.com == 1) {
        setfillcolor(BLACK);
    }
    else {
        setfillcolor(WHITE);
    }

    if(GameRound>1)
    {
        point bestpos = GiveBestPoint(R.com,6);
        solidcircle(X[bestpos.coor.first], Y[bestpos.coor.second], 28);
        board.put(bestpos.coor,R.com);
        clearrectangle(913, 0, 1500, 30);
    }
    else if(GameRound == 1) {
        if (board.board[7][7] == 0) {
            solidcircle(X[7], Y[7], 28);
            board.put({7,7},R.com);
            clearrectangle(913, 0, 1500, 30);
        }
        else {
            solidcircle(X[8], Y[8], 28);
            board.put({7,7},R.com);
            clearrectangle(913, 0, 1500, 30);
        }
    }
    GameRound++;
    //
    int k = board.score(R.com);
    printf("com:%d\n",k);
    //
}

bool AI::cmp(point x, point y) {
    return x.score > y.score;
}
