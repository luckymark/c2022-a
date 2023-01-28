//
// Created by XuanCheng on 2023/1/2.
//

#include "Chess.h"
#include "Score.h"

//未处理边缘评分问题

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
                score += FOUR_SCORE;
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
                score += THREE_SCORE;
            }
        }
    }
    //活二
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == 0) && (i + 3 < 15));
            judgeW = ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == 0)  && (j + 3< 15));
            judgeD = ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == 0) && (i + 3 < 15) && (j + 3 < 15));
            if (judgeL || judgeW || judgeD) {
                score += TWO_SCORE;
            }
        }
    }
    //活一
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] == 0) && (i + 2 < 15));
            judgeW = ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] == 0) && (j + 2 < 15));
            judgeD = ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == 0) && (i + 2 < 15) && (j + 2 < 15));
            if (judgeL || judgeW || judgeD) {
                score += ONE_SCORE;
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
    //死二
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] == 0) && (i + 3 < 15)) ||
                     ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] == color) && (board[i + 3][j] != 0) && (board[i + 3][j] != color) && (i + 3 < 15));
            judgeW = ((board[i][j] != 0) && (board[i][j] != color) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] == 0) && (j + 3 < 15)) ||
                     ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] == color) && (board[i][j + 3] != 0) && (board[i][j + 3] != color) && (j + 3 < 15));
            judgeD = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == 0) && (i + 3 < 15) && (j + 3 < 15)) ||
                     ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] != 0) && (board[i + 3][j + 3] != color) && (i + 3 < 15) && (j + 3 < 15));
            if (judgeL || judgeW || judgeD) {
                score += TWO_DIE_SCORE;
            }
        }
    }
    //死一
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            judgeL = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j] == color) && (board[i + 2][j] == 0) && (i + 2 < 15)) ||
                     ((board[i][j] == 0) && (board[i + 1][j] == color) && (board[i + 2][j] != 0) && (board[i + 2][j] != color) && (i + 2 < 15));
            judgeW = ((board[i][j] != 0) && (board[i][j] != color) && (board[i][j + 1] == color) && (board[i][j + 2] == 0) && (j + 2 < 15)) ||
                     ((board[i][j] == 0) && (board[i][j + 1] == color) && (board[i][j + 2] != 0) && (board[i][j + 2] != color) && (j + 2 < 15));
            judgeD = ((board[i][j] != 0) && (board[i][j] != color) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] == 0) && (i + 2 < 15) && (j + 2 < 15)) ||
                     ((board[i][j] == 0) && (board[i + 1][j + 1] == color) && (board[i + 2][j + 2] != 0) && (board[i + 2][j + 2] != color) && (i + 2 < 15) && (j + 2 < 15));
            if (judgeL || judgeW || judgeD) {
                score += ONE_DIE_SCORE;
            }
        }
    }


    return score;
}

int score_point(int x, int y, int color) {
    int count = 0, block = 0, secondCount = 0, empty = -1;
    int score =0;
    //上下
    for(int i = y + 1; TRUE; ++i){
        if(i >= 15){
            block++;
            break;
        }
        int t = board[x][i];
        if(t == R.emp){
            if(empty == -1 && i<14 && board[x][i+1] == color){
                empty = count;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            count++;
            continue;
        }else{
            block++;
            break;
        }
    }

    for(int i = y - 1; TRUE; --i){
        if(i < 0){
            block++;
            break;
        }
        int t = board[x][i];
        if(t == R.emp){
            if(empty == -1 && i > 0 && board[x][i-1] == color){
                empty = 0;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            secondCount++;
            empty ++;
            continue;
        }else{
            block++;
            break;
        }
    }

    count += secondCount;
    score += CountScore(count, block, empty);

    //左右
    count = 0;
    block = 0;
    secondCount = 0;
    empty = -1;
    for(int i = x + 1; TRUE; ++i){
        if(i >= 15){
            block++;
            break;
        }
        int t = board[i][y];
        if(t == R.emp){
            if(empty == -1 && i<14 && board[i + 1][y] == color){
                empty = count;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            count++;
            continue;
        }else{
            block++;
            break;
        }
    }

    for(int i = x - 1; TRUE; --i){
        if(i < 0){
            block++;
            break;
        }
        int t = board[i][y];
        if(t == R.emp){
            if(empty == -1 && i > 0 && board[i-1][y] == color){
                empty = 0;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            secondCount++;
            empty ++;
            continue;
        }else{
            block++;
            break;
        }
    }

    count += secondCount;
    score += CountScore(count, block, empty);

    //斜向右下
    count = 0;
    block = 0;
    secondCount = 0;
    empty = -1;
    for(int i = 1; TRUE; ++i){
        int tx = x + i, ty = y + i;
        if(tx >= 15 || ty >= 15){
            block++;
            break;
        }
        int t = board[i][y];
        if(t == R.emp){
            if(empty == -1 && (tx<14 && ty<14) && board[tx + 1][ty + 1] == color){
                empty = count;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            count++;
            continue;
        }else{
            block++;
            break;
        }
    }

    for(int i = 1; TRUE; ++i){
        int tx = x - i, ty = y - i;
        if(tx < 0 || ty < 0){
            block++;
            break;
        }
        int t = board[i][y];
        if(t == R.emp){
            if(empty == -1 && (tx>0 && ty>0) && board[tx-1][ty-1] == color){
                empty = 0;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            secondCount++;
            empty ++;
            continue;
        }else{
            block++;
            break;
        }
    }

    count += secondCount;
    score += CountScore(count, block, empty);

    //斜向左上
    count = 0;
    block = 0;
    secondCount = 0;
    empty = -1;
    for(int i = 1; TRUE; ++i){
        int tx = x + i, ty = y - i;
        if(tx < 0||ty < 0||tx >= 15 || ty >= 15){
            block++;
            break;
        }
        int t = board[i][y];
        if(t == R.emp){
            if(empty == -1 && (tx<14 && ty>0) && board[tx + 1][ty - 1] == color){
                empty = count;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            count++;
            continue;
        }else{
            block++;
            break;
        }
    }

    for(int i = 1; TRUE; ++i){
        int tx = x - i, ty = y + i;
        if(tx < 0||ty < 0||tx >= 15 || ty >= 15){
            block++;
            break;
        }
        int t = board[i][y];
        if(t == R.emp){
            if(empty == -1 && (tx>0 && ty<14) && board[tx-1][ty+1] == color){
                empty = 0;
                continue;
            }else{
                break;
            }
        }else if(t == color){
            secondCount++;
            empty ++;
            continue;
        }else{
            block++;
            break;
        }
    }

    count += secondCount;
    score += CountScore(count, block, empty);

    return score;
}

int CountScore(int count, int block, int empty) {
    //没有空位
    if(empty <= 0) {
        if(count >= 5) return FIVE_SCORE;
        if(block == 0) {
            switch(count) {
                case 1: return ONE_SCORE;
                case 2: return TWO_SCORE;
                case 3: return THREE_SCORE;
                case 4: return FOUR_SCORE;
            }
        }

        if(block == 1) {
            switch(count) {
                case 1: return ONE_DIE_SCORE;
                case 2: return TWO_DIE_SCORE;
                case 3: return THREE_DIE_SCORE;
                case 4: return FOUR_DIE_SCORE;
            }
        }

    } else if(empty == 1 || empty == count-1) {
        //第1个是空位
        if(count >= 6) {
            return FIVE_SCORE;
        }
        if(block == 0) {
            switch(count) {
                case 2: return TWO_SCORE/2;
                case 3: return THREE_SCORE;
                case 4: return FOUR_DIE_SCORE;
                case 5: return FOUR_SCORE;
            }
        }

        if(block == 1) {
            switch(count) {
                case 2: return TWO_DIE_SCORE;
                case 3: return THREE_DIE_SCORE;
                case 4: return FOUR_DIE_SCORE;
                case 5: return FOUR_DIE_SCORE;
            }
        }
    } else if(empty == 2 || empty == count-2) {
        //第二个是空位
        if(count >= 7) {
            return FIVE_SCORE;
        }
        if(block == 0) {
            switch(count) {
                case 3: return THREE_SCORE;
                case 4:
                case 5: return FOUR_DIE_SCORE;
                case 6: return FOUR_SCORE;
            }
        }

        if(block == 1) {
            switch(count) {
                case 3: return THREE_DIE_SCORE;
                case 4: return FOUR_DIE_SCORE;
                case 5: return FOUR_DIE_SCORE;
                case 6: return FOUR_SCORE;
            }
        }

        if(block == 2) {
            switch(count) {
                case 4:
                case 5:
                case 6: return FOUR_DIE_SCORE;
            }
        }
    } else if(empty == 3 || empty == count-3) {
        if(count >= 8) {
            return FIVE_SCORE;
        }
        if(block == 0) {
            switch(count) {
                case 4:
                case 5: return THREE_SCORE;
                case 6: return FOUR_DIE_SCORE;
                case 7: return FOUR_SCORE;
            }
        }

        if(block == 1) {
            switch(count) {
                case 4:
                case 5:
                case 6: return FOUR_DIE_SCORE;
                case 7: return FOUR_SCORE;
            }
        }

        if(block == 2) {
            switch(count) {
                case 4:
                case 5:
                case 6:
                case 7: return FOUR_DIE_SCORE;
            }
        }
    } else if(empty == 4 || empty == count-4) {
        if(count >= 9) {
            return FIVE_SCORE;
        }
        if(block == 0) {
            switch(count) {
                case 5:
                case 6:
                case 7:
                case 8: return FOUR_SCORE;
            }
        }

        if(block == 1) {
            switch(count) {
                case 4:
                case 5:
                case 6:
                case 7: return FOUR_DIE_SCORE;
                case 8: return FOUR_SCORE;
            }
        }

        if(block == 2) {
            switch(count) {
                case 5:
                case 6:
                case 7:
                case 8: return FOUR_DIE_SCORE;
            }
        }
    } else if(empty == 5 || empty == count-5) {
        return FIVE_SCORE;
    }

    return 0;
}

