//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"
#include "AI.h"
#include <random>


pos position[MOSTPOS];
pos bestpos;
int c = 1;

void genboard(int color, pos *points) {
    //Init pos
    for (int i = 0; i < MOSTPOS; ++i) {
        points[i].x = -1;
        points[i].y = -1;
        points[i].score = -1;
    }

    //Get empty position
    int flag = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board[i][j] != 0) {
                for (int m = i - 1; m < i + 1; ++m) {
                    for (int n = j - 1; n < j + 1; ++n) {
                        if (m > 0 && m < 15 && n > 0 && n < 15 && board[m][n] == 0) {
                            points[flag].x = m;
                            points[flag].y = n;
                            board[m][n] = color;
                            points[flag].score = score(color);
                            board[m][n] = 0;
                            flag++;
                        }
                    }
                }
            }
        }
    }

    //Bubble Sort
    BubbleSort(points);
}

int maxx(int deep, int alpha, int beta, int color) {
    int v = score(color);
    //迭代终止
    if (deep <= 0 || v >= FIVE_SCORE) {
        return v;
    }

    int best = MIN;
    pos points[MOSTPOS];
    genboard(color,points);
    for (int i = 0; i < MOSTPOS && points[i].x != -1; ++i) {
        board[points[i].x][points[i].y] = color;
        v = minn(deep - 1, alpha, best > beta ? best : beta);
        board[points[i].x][points[i].y] = 0;
        if (v > best) {
            best = v;
        }
        if (v > alpha) {
            break;
        }
    }
    return best;
}

int minn(int deep, int alpha, int beta, int color) {
    int v = score(color);
    //迭代终止
    if (deep <= 0 || v >= 999999) {
        return v;
    }

    int best = MAX;
    pos points[MOSTPOS];
    genboard(color, points);
    for (int i = MOSTPOS - 1; i >= 0 ; --i) {
        if (points[i].x == -1) {
            continue;
        }
        board[points[i].x][points[i].y] = R.hum;
        v = maxx(deep - 1,best<alpha ? best : alpha, beta);
        board[points[i].x][points[i].y] = 0;
        if (v < best) {
            best = v;
        }
        if (v < beta) {
            break;
        }
    }
    return best;
}

void maxmin(int deep, int color) {
    int best = MIN;
    int beta = MIN;
    int alpha = MAX;
    int v;
    int end = 0;
    pos points[MOSTPOS];
    //Init position
    for(int i = 0; i < MOSTPOS; ++i){
        position[i].x = -1;
        position[i].y = -1;
        position[i].score = -1;
    }
    //body
    genboard(color, points);
    for (int i = 0; i < MOSTPOS && points[i].x != -1; ++i){
        board[points[i].x][points[i].y] = color;
        v = maxx(deep - 1, alpha, beta, color);
        if (v == best){//将新的节点加入position中
            position[end].x = points[i].x;
            position[end].y = points[i].y;
            end++;
        } else if(v > best){//清除之前的节点，将新的节点加入position中
            best = v;
            for (int j = 0; j < MOSTPOS; ++j) {
                position[j].x = -1;
                position[j].y = -1;
            }
            end = 0;
            position[end].x = points[i].x;
            position[end].y = points[i].y;
            end++;
        }
        board[points[i].x][points[i].y] = 0;
    }
    //produce random node
    int k = 1;
    for (int i = 0; i < MOSTPOS; ++i) {
        if (position[i].x == -1) {
            k = i - 1;
            break;
        }
    }
    //生成随机数
    int randnum;
    while(true) {
        randnum = random();
        if(position[randnum].x != -1) {
            bestpos.x = position[randnum].x;
            bestpos.y = position[randnum].y;
            break;
        }
    }
}

void AI() {
    maxmin(4);
    fontset(BLACK, 24, ANTIALIASED_QUALITY, _T("黑体"));
    outtextxy(913, 0, _T("伟大机器人正在推翻人类暴政 "));
    if (R.com == 1) {
        setfillcolor(BLACK);
    }
    else {
        setfillcolor(WHITE);
    }

    if(c>1)
    {
        solidcircle(X[bestpos.x], Y[bestpos.y], 28);
        board[bestpos.x][bestpos.y] = R.com;
        clearrectangle(913, 0, 1500, 30);
    }
    else if(c == 1) {
        if (board[8][8] == 0) {
            solidcircle(X[8], Y[8], 28);
            board[8][8] = R.com;
            clearrectangle(913, 0, 1500, 30);
        }
        else {
            solidcircle(X[9], Y[9], 28);
            board[9][9] = R.com;
            clearrectangle(913, 0, 1500, 30);
        }
    }
    c++;
}

void BubbleSort(pos *points) {
    pos temp;
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19 - i; ++j) {
            if (points[j].x == points[j + 1].x && points[j].y == points[j + 1].y) {
                points[j + 1].x = -1;
                points[j + 1].y = -1;
                points[j + 1].score = -1;
            }
            if (points[j].score < points[j + 1].score) {
                temp.score = points[j].score;
                points[j].score = points[j + 1].score;
                points[j + 1].score = temp.score;
            }
        }
    }
}

int random() {
    std::random_device rd;
    auto gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0,MOSTPOS);
    int randk = dis(gen);
    return randk;
}

void AIdo(){
    AI();
    finish();
}