//
// Created by XuanCheng on 2023/2/11.
//

#ifndef CHESSAI_AI_H
#define CHESSAI_AI_H

#include <vector>
#include "point.h"

#define MIN INT_MIN
#define MAX INT_MAX

class AI {
private:
    static int negamax(int deep, int alpha, int beta, int role, std::vector<point> &candidates);
    static int r(int deep, int alpha, int beta, int role);
    static bool deeppp(int deep, int color, std::vector<point> &result, std::vector<point> &candidates);
    static point GiveBestPoint(int color, int deep);
    static bool maxx(int role, int deep, std::vector<point> &result);
    static bool minn(int role, int deep, std::vector<point> &result);
    static bool kill(int color, int deep, std::vector<point> &result);
    static double random();
public:
    static void AIdo();
    static bool cmp(point x, point y);
};


#endif //CHESSAI_AI_H
