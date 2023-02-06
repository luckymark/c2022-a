//
// Created by XuanCheng on 2023/2/5.
//

#ifndef CHESSAI_KILL_H
#define CHESSAI_KILL_H

#include "Chess.h"

bool cmp(poi x, poi y);
bool find(int color, int score, std::vector<poi> &points);
bool maxx(int color, int deep, std::vector<poi> &result);
bool minn(int color, int deep, std::vector<poi> &result);
bool kill(int color, int deep, std::vector<poi> &result);
#endif //CHESSAI_KILL_H