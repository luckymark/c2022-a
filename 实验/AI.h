//
// Created by XuanCheng on 2023/1/2.
//

#ifndef CHESSAI_AI_H
#define CHESSAI_AI_H

#define MIN 0
#define MAX FIVE_SCORE

std::vector<int> genboard(int deep);
int maxx(int deep,int alpha, int beta,int color = R.com);
int minn(int deep,int alpha,int beta,int color = R.hum);
std::vector<int> maxmin(int deep, int color = R.com);
void AI();
void AIdo();
int random(const std::vector<int>& vec);
int HasNeighbor(int i, int j, int length, int wideth);

#endif //CHESSAI_AI_H
