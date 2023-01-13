//
// Created by XuanCheng on 2023/1/2.
//

#ifndef CHESSAI_AI_H
#define CHESSAI_AI_H

#define MIN 0
#define MAX FIVE_SCORE
#define MOSTPOS 250

typedef struct {
    int x;
    int y;
    int score;
}pos;

void genboard(int color, pos* points);
int maxx(int deep,int alpha, int beta,int color = R.com);
int minn(int deep,int alpha,int beta,int color = R.hum);
void maxmin(int deep, int color = R.com);
void AI();
void AIdo();
void BubbleSort(pos *points);
int random();

#endif //CHESSAI_AI_H
