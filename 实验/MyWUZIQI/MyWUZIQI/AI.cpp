#include "AI.h"

void AI::init(Chess* chess)
{
 
  this->chess = chess;
  int size = chess->getGradeSize();
   for (int i = 0; i < size; i++)
    {
     vector<int> row;
     for (int j = 0; j < size; j++) 
      {
       row.push_back(0);
      }
     scoreMap.push_back(row);
    }
}

void AI::go()
{
    ChessPos pos = think();
	Sleep(500);//
    chess->chessDown(&pos, CHESS_WHITE);
}

void AI::calculateScore()
{
	int personNum = 0; //棋手方（黑棋）多少个连续的棋子
	int aiNum = 0; //AI方（白棋）连续有多少个连续的棋子
	int emptyNum = 0; // 该方向上空白位的个数

	// 评分向量数组清零
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//对每个点进行计算
			if (chess->getChessData(row, col)) continue;

			for (int y = -1; y <= 0; y++) {        //Y的范围还是-1， 0
				for (int x = -1; x <= 1; x++) {    //X的范围是 -1,0,1
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue; //当y=0时，仅允许x=1

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// 假设黑棋在该位置落子，会构成什么棋型
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					// 反向继续计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (personNum == 1) { //连2
						//CSDN  程序员Rock
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] = 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] = 5000; //200
						}
					}
					else if (personNum == 4) {
						scoreMap[row][col] = 20000;
					}

					// 假设白棋在该位置落子，会构成什么棋型
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (aiNum == 0) {
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;
						}
					}
					else if (aiNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum >= 4) {
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}
ChessPos AI::think()
{
    // 计算评分
    calculateScore();

    // 从评分中找出最大分数的位置
    int maxScore = 0;
    //std::vector<std::pair<int, int>> maxPoints;
    vector<ChessPos> maxPoints;
    int k = 0;

    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++)
        {
            // 前提是这个坐标是空的
            if (chess->getChessData(row, col) == 0) {
                if (scoreMap[row][col] > maxScore)          // 找最大的数和坐标
                {
                    maxScore = scoreMap[row][col];
                    maxPoints.clear();
                    maxPoints.push_back(ChessPos(row, col));
                }
                else if (scoreMap[row][col] == maxScore) {   // 如果有多个最大的数，都存起来
                    maxPoints.push_back(ChessPos(row, col));
                }
            }
        }
    }

    // 随机落子，如果有多个点的话
    int index = rand() % maxPoints.size();
    return maxPoints[index];
}
