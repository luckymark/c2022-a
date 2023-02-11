//
// Created by XuanCheng on 2023/2/6.
//

#ifndef CHESSAI_BOARD_H
#define CHESSAI_BOARD_H

#include <easyx.h>
#include <utility>
#include <vector>
#include "role.h"
#include "point.h"

class Board {
public:
    int board[15][15]{};

    Board();
    bool GenerateBoard(int deep, int role, std::vector<point> &points);
    void put(std::pair<int, int> p, int role);
    void remove(std::pair<int, int> p, int role);
    int score(int role);
    bool find(int color, int score, std::vector<point> &points);

private:
    std::pair<int,int>LastStep;
    int ComScore[15][15]{};
    int HumScore[15][15]{};
    int comMaxScore{};
    int humMaxScore{};

    bool HasNeighbor(int i, int j, int length, int wideth);
    int ScorePoint(int x, int y, int role);
    int CountScore(int count, int block, int empty);
    static bool cmp(point x, point y);
};


#endif //CHESSAI_BOARD_H
