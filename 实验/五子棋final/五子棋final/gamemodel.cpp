#include "GameModel.h"
#include <time.h>
#include <stdlib.h>
#include "GameModel.h"
void initChessData(ChessData* data)
{
    if (!data)return;
    memset(data->chessMap, 0, sizeof(data->chessMap));
    memset(data->scoreMap, 0, sizeof(data->scoreMap));
    data->playerSign = true;
}

void updateGameMap(ChessData* data, int row, int col)
{
    if (!data)return;
    if (data->playerSign)
        data->chessMap[row][col] = 1;
    else
        data->chessMap[row][col] = -1;

    data->playerSign = !data->playerSign; // 换手
}

bool isWin(ChessData* data, int row, int col)
{
    // 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
    // 水平方向
    for (int i = 0; i < 5; i++)
    {
        // 往左5个，往右匹配4个子，20种情况
        if (col - i > 0 &&
            col - i + 4 < BOARD_SIZE &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 1] &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 2] &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 3] &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 4])
            return true;
    }

    // 竖直方向(上下延伸4个)
    for (int i = 0; i < 5; i++)
    {
        if (row - i > 0 &&
            row - i + 4 < BOARD_SIZE &&
            data->chessMap[row - i][col] == data->chessMap[row - i + 1][col] &&
            data->chessMap[row - i][col] == data->chessMap[row - i + 2][col] &&
            data->chessMap[row - i][col] == data->chessMap[row - i + 3][col] &&
            data->chessMap[row - i][col] == data->chessMap[row - i + 4][col])
            return true;
    }

    // “/"方向
    for (int i = 0; i < 5; i++)
    {
        if (row + i < BOARD_SIZE &&
            row + i - 4 > 0 &&
            col - i > 0 &&
            col - i + 4 < BOARD_SIZE &&
            // 第[row+i]行，第[col-i]的棋子，与右上方连续4个棋子都相同
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 1][col - i + 1] &&
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 2][col - i + 2] &&
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 3][col - i + 3] &&
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 4][col - i + 4])
            return true;
    }

    // “\“ 方向
    for (int i = 0; i < 5; i++)
    {
        // 第[row+i]行，第[col-i]的棋子，与右下方连续4个棋子都相同
        if (row - i > 0 &&
            row - i + 4 < BOARD_SIZE &&
            col - i > 0 &&
            col - i + 4 < BOARD_SIZE &&
            data->chessMap[row - i][col - i] == data->chessMap[row - i + 1][col - i + 1] &&
            data->chessMap[row - i][col - i] == data->chessMap[row - i + 2][col - i + 2] &&
            data->chessMap[row - i][col - i] == data->chessMap[row - i + 3][col - i + 3] &&
            data->chessMap[row - i][col - i] == data->chessMap[row - i + 4][col - i + 4])
            return true;
    }

    return false;
}




position AI_GO(ChessData* data)
{
    // 计算评分
    calculateScore(data);

    // 从评分中找出最大分数的位置
    int maxScore = 0;
    position maxPoints[BOARD_SIZE * BOARD_SIZE] = { 0, };
    int k = 0;

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // 前提是这个坐标是空的
            if (data->chessMap[row][col] == 0)
            {
                if (data->scoreMap[row][col] > maxScore)          // 找最大的数和坐标
                {
                   
                    memset(maxPoints, 0, sizeof(maxPoints));
                    k = 0;
                    maxScore = data->scoreMap[row][col];
                  
                    maxPoints[k].row = row;
                    maxPoints[k].col = col;
                    k++;
                }
                else if (data->scoreMap[row][col] == maxScore) {   // 如果有多个最大的数，都存起来
                    maxPoints[k].row = row;
                    maxPoints[k].col = col;
                    k++;
                }
            }
        }

    // 随机落子，如果有多个点的话
    srand((unsigned)time(0));
    int index = rand() % k;
    return maxPoints[index];
}

// 最关键的计算评分函数
void calculateScore(ChessData* data)
{
    if (!data) return;

    // 统计玩家或者电脑连成的子
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0; // AI连成子的个数
    int emptyNum = 0; // 各方向空白位的个数

    // 清空评分数组
    memset(data->scoreMap, 0, sizeof(data->scoreMap));
    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // 空白点就算
            if (row >= 0 && col >= 0 && data->chessMap[row][col] == 0)
            {
               
                int directs[4][2] = {
                    1,0,
                    1,1,
                    0,1,
                    -1,1 };
                for (int k = 0; k < 4; k++) {

                    int x = directs[k][0];
                    int y = directs[k][1];

                    // 重置
                    personNum = 0;
                    botNum = 0;
                    emptyNum = 0;

                        // 对黑棋评分（正反两个方向）
                    for (int i = 1; i <= 4; i++)
                    {
                        if (row + i * y >= 0 && row + i * y < BOARD_SIZE &&
                            col + i * x >= 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == 1) // 真人玩家的子
                        {
                            personNum++;
                        }
                        else if (row + i * y >= 0 && row + i * y < BOARD_SIZE &&
                            col + i * x >= 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == 0) // 空白位
                        {
                            emptyNum++;
                            break;
                        }
                        else            // 出边界
                            break;
                    }

                    for (int i = 1; i <= 4; i++)
                    {
                        if (row - i * y >= 0 && row - i * y < BOARD_SIZE &&
                            col - i * x >= 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == 1) // 玩家的子
                        {
                            personNum++;
                        }
                        else if (row - i * y >= 0 && row - i * y < BOARD_SIZE &&
                            col - i * x >= 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == 0) // 空白位
                        {
                            emptyNum++;
                            break;
                        }
                        else            // 出边界，或者有AI自己的棋子
                            break;
                    }

                    if (personNum == 1)                      // 杀二
                        data->scoreMap[row][col] += 10;
                    else if (personNum == 2)                 // 杀三
                    {
                        if (emptyNum == 1)
                            data->scoreMap[row][col] += 30;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 40;
                    }
                    else if (personNum == 3)                 // 杀四
                    {
                        // 量变空位不一样，优先级不一样
                        if (emptyNum == 1)
                            data->scoreMap[row][col] += 60;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 200;
                    }
                    else if (personNum == 4)                 // 杀五
                        data->scoreMap[row][col] += 20000;

                    // 进行一次清空
                    emptyNum = 0;

                    // 对白棋评分
                    for (int i = 1; i <= 4; i++)
                    {
                        if (row + i * y > 0 && row + i * y < BOARD_SIZE &&
                            col + i * x > 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == -1) // 玩家的子
                        {
                            botNum++;
                        }
                        else if (row + i * y > 0 && row + i * y < BOARD_SIZE &&
                            col + i * x > 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == 0) // 空白位
                        {
                            emptyNum++;
                            break;
                        }
                        else            // 出边界
                            break;
                    }

                    for (int i = 1; i <= 4; i++)
                    {
                        if (row - i * y > 0 && row - i * y < BOARD_SIZE &&
                            col - i * x > 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == -1) // AI的子
                        {
                            botNum++;
                        }
                        else if (row - i * y > 0 && row - i * y < BOARD_SIZE &&
                            col - i * x > 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == 0) // 空白位
                        {
                            emptyNum++;
                            break;
                        }
                        else            // 出边界
                            break;
                    }

                    if (botNum == 0)                      // 普通下子
                        data->scoreMap[row][col] += 5;
                    else if (botNum == 1)                 // 活二
                        data->scoreMap[row][col] += 10;
                    else if (botNum == 2)
                    {
                        if (emptyNum == 1)                // 死三
                            data->scoreMap[row][col] += 25;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 50;  // 活三
                    }
                    else if (botNum == 3)
                    {
                        if (emptyNum == 1)                // 死四
                            data->scoreMap[row][col] += 55;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 300; // 活四
                    }
                    else if (botNum >= 4)
                        data->scoreMap[row][col] += 30000;   // 活五，应该具有最高优先级

                    //}
                }

            }
        }
}

bool checkWin(ChessData* game, int row, int col)
{
    // 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
    // 水平方向
    for (int i = 0; i < 5; i++)
    {
        // 往左5个，往右匹配4个子，20种情况
        if (col - i >= 0 &&
            col - i + 4 < BOARD_SIZE &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 1] &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 2] &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 3] &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 4])
            return true;
    }

    // 竖直方向(上下延伸4个)
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 &&
            row - i + 4 < BOARD_SIZE &&
            game->chessMap[row - i][col] == game->chessMap[row - i + 1][col] &&
            game->chessMap[row - i][col] == game->chessMap[row - i + 2][col] &&
            game->chessMap[row - i][col] == game->chessMap[row - i + 3][col] &&
            game->chessMap[row - i][col] == game->chessMap[row - i + 4][col])
            return true;
    }

    // “/"方向
    for (int i = 0; i < 5; i++)
    {
        if (row + i < BOARD_SIZE &&
            row + i - 4 >= 0 &&
            col - i >= 0 &&
            col - i + 4 < BOARD_SIZE &&
            // 第[row+i]行，第[col-i]的棋子，与右上方连续4个棋子都相同
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 1][col - i + 1] &&
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 2][col - i + 2] &&
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 3][col - i + 3] &&
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 4][col - i + 4])
            return true;
    }

    // “\“ 方向
    for (int i = 0; i < 5; i++)
    {
        // 第[row+i]行，第[col-i]的棋子，与右下方连续4个棋子都相同
        if (row - i >= 0 &&
            row - i + 4 < BOARD_SIZE &&
            col - i >= 0 &&
            col - i + 4 < BOARD_SIZE &&
            game->chessMap[row - i][col - i] == game->chessMap[row - i + 1][col - i + 1] &&
            game->chessMap[row - i][col - i] == game->chessMap[row - i + 2][col - i + 2] &&
            game->chessMap[row - i][col - i] == game->chessMap[row - i + 3][col - i + 3] &&
            game->chessMap[row - i][col - i] == game->chessMap[row - i + 4][col - i + 4])
            return true;
    }

    return false;
}
