//
// Created by XuanCheng on 2023/1/2.
//

#ifndef CHESSAI_AI_H
#define CHESSAI_AI_H

#define MIN (-1)
#define MAX (FIVE_SCORE+1)

bool genboard(int deep, std::vector<std::pair<int,int>> &points);
int negamax(int deep, int alpha, int beta, int color);
void AI();
void AIdo();
double random();
int HasNeighbor(int i, int j, int length, int wideth);

#endif //CHESSAI_AI_H
