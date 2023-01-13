//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"

int score(int color)
{
    int score = 0;
    short judgeL = 0, judgeW = 0, judgeD = 0;
    //成5
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = (board[i][j] == color) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == color) && (board[i + 4][j] == color);
            judgeW = (board[i][j] == color) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == color) && (board[i][j + 4] == color);
            judgeD = (board[i][j] == color) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color) && (board[i + 4][j + 4] == color);
            if (judgeL || judgeW || judgeD) {
                score += FIVE_SCORE;
                return score;
            }
        }
    }
    //活四
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == color) && (board[i + 4][j] == color) && (board[i + 5][j] == 0) && (i + 4 < 15));
            judgeW = ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == color) && (board[i][j + 4] == color) && (board[i][j + 5] == 0) && (j + 4 < 15));
            judgeD = ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color) && (board[i + 4][j + 4] == color) && (board[i + 5][j + 5] == 0) && (i + 4 < 15) && (j + 4 < 15));
            if (judgeL || judgeW || judgeD) {
                score += FOUR_LIVE_SCORE;
            }
        }
    }
    //活三
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == color) && (board[i + 4][j] == 0) && (i + 4 < 15));
            judgeW = ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == color) && (board[i][j + 4] == 0) && (j + 4 < 15));
            judgeD = ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color) && (board[i + 4][j + 4] == 0) && (i + 4 < 15) && (j + 4 < 15));
            if (judgeL || judgeW || judgeD) {
                score += THREE_LIVE_SCORE;
            }
        }
    }
    //死四
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == color) && (board[i + 4][j] == color) && (board[i + 5][j] == 0) && (i + 4 < 15)) ||
                    ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == color) && (board[i + 4][j] == color) && (board[i + 5][j] != 0) && (board[i + 5][j] != color) && (i + 4 < 15));
            judgeW = ((board[i][j] != 0) && (board[i][j] != color) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == color) && (board[i][j + 4] == color) && (board[i][j + 5] == 0) && (j + 4 < 15)) ||
                    ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == color) && (board[i][j + 4] == color) && (board[i][j + 5] != 0) && (board[i][j + 5] != color) && (j + 4 < 15));
            judgeD = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color) && (board[i + 4][j + 4] == color) && (board[i + 5][j + 5] == 0) && (i + 4 < 15) && (j + 4 < 15)) ||
                    ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color) && (board[i + 4][j + 4] == color) && (board[i + 5][j + 5] != 0) && (board[i + 5][j + 5] != color) && (i + 4 < 15) && (j + 4 < 15));
            if (judgeL || judgeW || judgeD) {
                score += FOUR_DIE_SCORE;
            }
        }
    }
    //死三
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == color) && (board[i + 4][j] == 0) && (i + 4 < 15)) ||
                    ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == color) && (board[i + 4][j] != 0) && (board[i + 4][j] != color) && (i + 4 < 15));
            judgeW = ((board[i][j] != 0) && (board[i][j] != color) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == color) && (board[i][j + 4] == 0) && (j + 4 < 15)) ||
                    ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == color) && (board[i][j + 4] != 0) && (board[i][j + 4] != color) && (j + 4 < 15));
            judgeD = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color) && (board[i + 4][j + 4] == 0) && (i + 4 < 15) && (j + 4 < 15)) ||
                    ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color) && (board[i + 4][j + 4] != 0) && (board[i + 4][j + 4] != color) && (i + 4 < 15) && (j + 4 < 15));
            if (judgeL || judgeW || judgeD) {
                score += THREE_DIE_SCORE;
            }
        }
    }

    return score;
}