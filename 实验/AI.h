//
// Created by XuanCheng on 2023/1/2.
//

#ifndef CHESSAI_AI_H
#define CHESSAI_AI_H

#define MIN (-1)
#define MAX (FIVE_SCORE+1)

bool genboard(int deep, std::vector<int> &points);
int maxx(int deep,int alpha, int beta,int color = R.com);
int minn(int deep,int alpha,int beta,int color = R.hum);
std::vector<int> maxmin(int deep, int color = R.com);
void AI();
void AIdo();
int random();
int HasNeighbor(int i, int j, int length, int wideth);

#endif //CHESSAI_AI_H
