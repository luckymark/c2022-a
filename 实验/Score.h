//
// Created by XuanCheng on 2023/1/2.
//

#ifndef CHESSAI_SCORE_H
#define CHESSAI_SCORE_H

#define ONE_SCORE 10
#define TWO_SCORE 100
#define THREE_SCORE 1000
#define FOUR_SCORE 100000
#define FIVE_SCORE 1000000
#define ONE_DIE_SCORE 1
#define TWO_DIE_SCORE 10
#define THREE_DIE_SCORE 100
#define FOUR_DIE_SCORE 50000



int score(int color);
int score_point(int i, int j, int color);
int CountScore(int count, int block, int empty);

#endif //CHESSAI_SCORE_H
