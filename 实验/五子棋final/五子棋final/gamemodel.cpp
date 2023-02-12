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

    data->playerSign = !data->playerSign; // ����
}

bool isWin(ChessData* data, int row, int col)
{
    // ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
    // ˮƽ����
    for (int i = 0; i < 5; i++)
    {
        // ����5��������ƥ��4���ӣ�20�����
        if (col - i > 0 &&
            col - i + 4 < BOARD_SIZE &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 1] &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 2] &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 3] &&
            data->chessMap[row][col - i] == data->chessMap[row][col - i + 4])
            return true;
    }

    // ��ֱ����(��������4��)
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

    // ��/"����
    for (int i = 0; i < 5; i++)
    {
        if (row + i < BOARD_SIZE &&
            row + i - 4 > 0 &&
            col - i > 0 &&
            col - i + 4 < BOARD_SIZE &&
            // ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 1][col - i + 1] &&
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 2][col - i + 2] &&
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 3][col - i + 3] &&
            data->chessMap[row + i][col - i] == data->chessMap[row + i - 4][col - i + 4])
            return true;
    }

    // ��\�� ����
    for (int i = 0; i < 5; i++)
    {
        // ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
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
    // ��������
    calculateScore(data);

    // ���������ҳ���������λ��
    int maxScore = 0;
    position maxPoints[BOARD_SIZE * BOARD_SIZE] = { 0, };
    int k = 0;

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // ǰ������������ǿյ�
            if (data->chessMap[row][col] == 0)
            {
                if (data->scoreMap[row][col] > maxScore)          // ��������������
                {
                   
                    memset(maxPoints, 0, sizeof(maxPoints));
                    k = 0;
                    maxScore = data->scoreMap[row][col];
                  
                    maxPoints[k].row = row;
                    maxPoints[k].col = col;
                    k++;
                }
                else if (data->scoreMap[row][col] == maxScore) {   // ����ж������������������
                    maxPoints[k].row = row;
                    maxPoints[k].col = col;
                    k++;
                }
            }
        }

    // ������ӣ�����ж����Ļ�
    srand((unsigned)time(0));
    int index = rand() % k;
    return maxPoints[index];
}

// ��ؼ��ļ������ֺ���
void calculateScore(ChessData* data)
{
    if (!data) return;

    // ͳ����һ��ߵ������ɵ���
    int personNum = 0; // ��������ӵĸ���
    int botNum = 0; // AI�����ӵĸ���
    int emptyNum = 0; // ������հ�λ�ĸ���

    // �����������
    memset(data->scoreMap, 0, sizeof(data->scoreMap));
    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // �հ׵����
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

                    // ����
                    personNum = 0;
                    botNum = 0;
                    emptyNum = 0;

                        // �Ժ������֣�������������
                    for (int i = 1; i <= 4; i++)
                    {
                        if (row + i * y >= 0 && row + i * y < BOARD_SIZE &&
                            col + i * x >= 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == 1) // ������ҵ���
                        {
                            personNum++;
                        }
                        else if (row + i * y >= 0 && row + i * y < BOARD_SIZE &&
                            col + i * x >= 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == 0) // �հ�λ
                        {
                            emptyNum++;
                            break;
                        }
                        else            // ���߽�
                            break;
                    }

                    for (int i = 1; i <= 4; i++)
                    {
                        if (row - i * y >= 0 && row - i * y < BOARD_SIZE &&
                            col - i * x >= 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == 1) // ��ҵ���
                        {
                            personNum++;
                        }
                        else if (row - i * y >= 0 && row - i * y < BOARD_SIZE &&
                            col - i * x >= 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == 0) // �հ�λ
                        {
                            emptyNum++;
                            break;
                        }
                        else            // ���߽磬������AI�Լ�������
                            break;
                    }

                    if (personNum == 1)                      // ɱ��
                        data->scoreMap[row][col] += 10;
                    else if (personNum == 2)                 // ɱ��
                    {
                        if (emptyNum == 1)
                            data->scoreMap[row][col] += 30;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 40;
                    }
                    else if (personNum == 3)                 // ɱ��
                    {
                        // �����λ��һ�������ȼ���һ��
                        if (emptyNum == 1)
                            data->scoreMap[row][col] += 60;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 200;
                    }
                    else if (personNum == 4)                 // ɱ��
                        data->scoreMap[row][col] += 20000;

                    // ����һ�����
                    emptyNum = 0;

                    // �԰�������
                    for (int i = 1; i <= 4; i++)
                    {
                        if (row + i * y > 0 && row + i * y < BOARD_SIZE &&
                            col + i * x > 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == -1) // ��ҵ���
                        {
                            botNum++;
                        }
                        else if (row + i * y > 0 && row + i * y < BOARD_SIZE &&
                            col + i * x > 0 && col + i * x < BOARD_SIZE &&
                            data->chessMap[row + i * y][col + i * x] == 0) // �հ�λ
                        {
                            emptyNum++;
                            break;
                        }
                        else            // ���߽�
                            break;
                    }

                    for (int i = 1; i <= 4; i++)
                    {
                        if (row - i * y > 0 && row - i * y < BOARD_SIZE &&
                            col - i * x > 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == -1) // AI����
                        {
                            botNum++;
                        }
                        else if (row - i * y > 0 && row - i * y < BOARD_SIZE &&
                            col - i * x > 0 && col - i * x < BOARD_SIZE &&
                            data->chessMap[row - i * y][col - i * x] == 0) // �հ�λ
                        {
                            emptyNum++;
                            break;
                        }
                        else            // ���߽�
                            break;
                    }

                    if (botNum == 0)                      // ��ͨ����
                        data->scoreMap[row][col] += 5;
                    else if (botNum == 1)                 // ���
                        data->scoreMap[row][col] += 10;
                    else if (botNum == 2)
                    {
                        if (emptyNum == 1)                // ����
                            data->scoreMap[row][col] += 25;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 50;  // ����
                    }
                    else if (botNum == 3)
                    {
                        if (emptyNum == 1)                // ����
                            data->scoreMap[row][col] += 55;
                        else if (emptyNum == 2)
                            data->scoreMap[row][col] += 300; // ����
                    }
                    else if (botNum >= 4)
                        data->scoreMap[row][col] += 30000;   // ���壬Ӧ�þ���������ȼ�

                    //}
                }

            }
        }
}

bool checkWin(ChessData* game, int row, int col)
{
    // ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
    // ˮƽ����
    for (int i = 0; i < 5; i++)
    {
        // ����5��������ƥ��4���ӣ�20�����
        if (col - i >= 0 &&
            col - i + 4 < BOARD_SIZE &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 1] &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 2] &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 3] &&
            game->chessMap[row][col - i] == game->chessMap[row][col - i + 4])
            return true;
    }

    // ��ֱ����(��������4��)
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

    // ��/"����
    for (int i = 0; i < 5; i++)
    {
        if (row + i < BOARD_SIZE &&
            row + i - 4 >= 0 &&
            col - i >= 0 &&
            col - i + 4 < BOARD_SIZE &&
            // ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 1][col - i + 1] &&
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 2][col - i + 2] &&
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 3][col - i + 3] &&
            game->chessMap[row + i][col - i] == game->chessMap[row + i - 4][col - i + 4])
            return true;
    }

    // ��\�� ����
    for (int i = 0; i < 5; i++)
    {
        // ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
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
