//
// Created by XuanCheng on 2023/1/2.
//

#ifndef CHESSAI_AI_H
#define CHESSAI_AI_H

#define MIN (-1)
#define MAX (FIVE_SCORE+1)

#include "poi.h"
#include "col.h"

bool genboard(int deep, std::vector<poi> &points);
int negamax(int deep, int alpha, int beta, int color, std::vector<poi> &candidates);
int r(int deep, int alpha, int beta, int color);
void AI();
void AIdo();
double random();
int HasNeighbor(int i, int j, int length, int wideth);
bool deeppp(int deep, int color, std::vector<poi> &result, std::vector<poi> &candidates);
poi GiveBestPoint(int color = R.com, int deep = 4);

#endif //CHESSAI_AI_H
