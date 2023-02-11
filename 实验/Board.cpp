//
// Created by XuanCheng on 2023/2/6.
//

#include <algorithm>
#include "Board.h"
#include "score.h"
#include "Chess.h"

using namespace std;

Board::Board() {
    for (auto &i: board) {
        for (int &j: i) {
            j = 0;
        }
    }
    for (auto &i: HumScore) {
        for (int &j: i) {
            j = 0;
        }
    }
    for (auto &i: ComScore) {
        for (int &j: i) {
            j = 0;
        }
    }
    LastStep = {-1, -1};
    comMaxScore = 0;
    humMaxScore = 0;
}

bool Board::GenerateBoard(int deep, int role, std::vector<point> &points) {
    vector<point> fives;
    vector<point> HumFours;
    vector<point> ComFours;
    vector<point> HumDieFour;
    vector<point> ComDieFour;
    vector<point> doubleThrees;
    vector<point> threes;
    vector<point> twos;
    vector<point> neighbors;
    vector<point> nextNeighbors;
    point temp;

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board[i][j] == R.emp) {
                if (HasNeighbor(i, j, 1, 1)) {
                    board[i][j] = R.hum;
                    int scoreHum = ScorePoint(i, j, R.hum);
                    board[i][j] = R.emp;

                    board[i][j] = R.com;
                    int scoreCom = ScorePoint(i, j, R.com);
                    board[i][j] = R.emp;

                    if (scoreCom >= FIVE_SCORE) {
                        temp.coor = {i, j};
                        points.push_back(temp);
                        return true;
                    } else if (scoreHum >= FIVE_SCORE) {
                        temp.coor = {i, j};
                        fives.push_back(temp);
                    } else if (scoreHum >= FOUR_SCORE) {
                        temp.coor = {i, j};
                        HumFours.push_back(temp);
                    } else if (scoreCom >= FOUR_SCORE) {
                        temp.coor = {i, j};
                        ComFours.push_back(temp);
                    } else if (scoreHum >= FOUR_DIE_SCORE) {
                        temp.coor = {i, j};
                        HumDieFour.push_back(temp);
                    } else if (scoreCom >= FOUR_DIE_SCORE) {
                        temp.coor = {i, j};
                        ComDieFour.push_back(temp);
                    } else if (scoreHum >= 2 * THREE_SCORE) {
                        temp.coor = {i, j};
                        doubleThrees.push_back(temp);
                    } else if (scoreCom >= 2 * THREE_SCORE) {
                        temp.coor = {i, j};
                        doubleThrees.insert(doubleThrees.begin(), temp);
                    } else if (scoreCom >= THREE_SCORE) {
                        temp.coor = {i, j};
                        threes.insert(threes.begin(), temp);
                    } else if (scoreHum >= THREE_SCORE) {
                        temp.coor = {i, j};
                        threes.push_back(temp);
                    } else if (scoreCom >= TWO_SCORE) {
                        temp.coor = {i, j};
                        twos.insert(twos.begin(), temp);
                    } else if (scoreHum >= TWO_SCORE) {
                        temp.coor = {i, j};
                        twos.push_back(temp);
                    } else {
                        temp.coor = {i, j};
                        neighbors.push_back(temp);
                    }
                } else if (deep >= 2 && HasNeighbor(i, j, 2, 2)) {
                    temp.coor = {i, j};
                    nextNeighbors.push_back(temp);
                }
            }
        }
    }

    if (!fives.empty()) {
        points = fives;
        return true;
    }

    if (role == R.com && !ComFours.empty()) {
        points = ComFours;
        return true;
    }
    if (role == R.hum && !HumFours.empty()) {
        points = HumFours;
        return true;
    }

    if (role == R.com && !HumFours.empty() && ComFours.empty()) {
        points = HumFours;
        return true;
    }
    if (role == R.hum && !ComFours.empty() && HumFours.empty()) {
        points = ComFours;
        return true;
    }

    vector<point> fours;
    if (role == R.com) {
        ComFours.insert(ComFours.end(), HumFours.begin(), HumFours.end());
        fours.insert(fours.end(), ComFours.begin(), ComFours.end());
    } else {
        HumFours.insert(HumFours.end(), ComFours.begin(), ComFours.end());
        fours.insert(fours.end(), HumFours.begin(), HumFours.end());
    }
    vector<point> DieFours;
    if (role == R.com) {
        ComDieFour.insert(ComDieFour.end(), HumDieFour.begin(), HumDieFour.end());
        fours.insert(fours.end(), ComDieFour.begin(), ComDieFour.end());
    } else {
        HumDieFour.insert(HumDieFour.end(), ComDieFour.begin(), ComDieFour.end());
        fours.insert(fours.end(), HumDieFour.begin(), HumDieFour.end());
    }
    if (!fours.empty()) {
        fours.insert(fours.end(), DieFours.begin(), DieFours.end());
        points = fours;
        return true;
    }

    if (role == R.com && !HumDieFour.empty() && ComDieFour.empty() && ComFours.empty()) {
        points = HumDieFour;
        return true;
    }
    if (role == R.hum && !ComDieFour.empty() && HumDieFour.empty() && HumFours.empty()) {
        points = ComDieFour;
        return true;
    }

    points.insert(points.end(), threes.begin(), threes.end());
    points.insert(points.end(), twos.begin(), twos.end());
    points.insert(points.end(), neighbors.begin(), neighbors.end());
    points.insert(points.end(), nextNeighbors.begin(), nextNeighbors.end());

    return false;
}

void Board::put(std::pair<int, int> p, int role) {
    board[p.first][p.second] = role;
    if(role == R.com){
        ComScore[p.first][p.second] = ScorePoint(p.first, p.second, role);
        HumScore[p.first][p.second] = 0;
    }else{
        ComScore[p.first][p.second] = 0;
        HumScore[p.first][p.second] = ScorePoint(p.first, p.second, role);
    }
}

void Board::remove(std::pair<int, int> p, int role) {
    board[p.first][p.second] = R.emp;
    if(role == R.com){
        ComScore[p.first][p.second] = ScorePoint(p.first, p.second, role);
        HumScore[p.first][p.second] = 0;
    }else{
        ComScore[p.first][p.second] = 0;
        HumScore[p.first][p.second] = ScorePoint(p.first, p.second, role);
    }
}

//unsure
int Board::score(int role) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(board[i][j] == R.com){
                comMaxScore += ComScore[i][j];
            }else if(board[i][j] == R.hum){
                humMaxScore += HumScore[i][j];
            }
        }
    }
    int result = (role == R.com ? 1 : -1) * (comMaxScore - humMaxScore);
    return result;
}

bool Board::find(int color, int score, vector<point> &points) {
    vector<point>result;
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 14; ++j) {
            if(board[i][j] == R.emp){
                point p;
                if(HasNeighbor(i,j,2,2)){
                    if(color == R.emp){
                        board[i][j] = R.hum;
                        int scoreHum = ScorePoint(i,j,R.hum);
                        board[i][j] = R.emp;
                        board[i][j] = R.com;
                        int scoreCom = ScorePoint(i,j,R.com);
                        board[i][j] = R.emp;

                        int s = scoreHum + scoreHum;
                        if(s > score){
                            p.score = s;
                            result.push_back(p);
                        }
                    }else{
                        board[i][j] = color;
                        int s = ScorePoint(i,j,color);
                        board[i][j] = R.emp;
                        if(s >= score){
                            p.score = s;
                            result.push_back(p);
                        }
                    }
                }
            }
        }
    }
    sort(result.begin(), result.end(), cmp);
    points = result;
    return true;
}

bool Board::HasNeighbor(int i, int j, int length, int wideth) {
    for (int m = i - length; m >= 0 && m < 15 && m <= i + length; m++) {
        for (int n = j - wideth; n >= 0 && n < 15 && n <= j + wideth; n++) {
            if (m != n && board[m][n] != 0) {
                return true;
            }
        }
    }
    return false;
}

int Board::ScorePoint(int x, int y, int role) {
    int count = 0, block = 0, secondCount = 0, empty = -1;
    int score = 0;
    //上下
    for (int i = y; TRUE; ++i) {
        if (i >= 15) {
            block++;
            break;
        }
        int t = board[x][i];
        if (t == R.emp) {
            if (empty == -1 && i < 14 && board[x][i + 1] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            count++;
            continue;
        } else if (i == y && t != role && t != R.emp) {
            block++;
        } else {
            block++;
            break;
        }
    }

    for (int i = y - 1; TRUE; --i) {
        if (i < 0) {
            block++;
            break;
        }
        int t = board[x][i];
        if (t == R.emp) {
            if (empty == -1 && i > 0 && board[x][i - 1] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            secondCount++;
            empty++;
            continue;
        } else {
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
    for (int i = x; TRUE; ++i) {
        if (i >= 15) {
            block++;
            break;
        }
        int t = board[i][y];
        if (t == R.emp) {
            if (empty == -1 && i < 14 && board[i + 1][y] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            count++;
            continue;
        } else if (i == x && t != role && t != R.emp) {
            block++;
        } else {
            block++;
            break;
        }
    }

    for (int i = x - 1; TRUE; --i) {
        if (i < 0) {
            block++;
            break;
        }
        int t = board[i][y];
        if (t == R.emp) {
            if (empty == -1 && i > 0 && board[i - 1][y] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            secondCount++;
            empty++;
            continue;
        } else {
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
    for (int i = 0; TRUE; ++i) {
        int tx = x + i, ty = y + i;
        if (tx >= 15 || ty >= 15) {
            block++;
            break;
        }
        int t = board[tx][ty];
        if (t == R.emp) {
            if (empty == -1 && (tx < 14 && ty < 14) && board[tx + 1][ty + 1] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            count++;
            continue;
        } else if (i == 0 && t != role && t != R.emp) {
            block++;
        } else {
            block++;
            break;
        }
    }

    for (int i = 1; TRUE; ++i) {
        int tx = x - i, ty = y - i;
        if (tx < 0 || ty < 0) {
            block++;
            break;
        }
        int t = board[tx][ty];
        if (t == R.emp) {
            if (empty == -1 && (tx > 0 && ty > 0) && board[tx - 1][ty - 1] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            secondCount++;
            empty++;
            continue;
        } else {
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
    for (int i = 0; TRUE; ++i) {
        int tx = x + i, ty = y - i;
        if (tx < 0 || ty < 0 || tx >= 15 || ty >= 15) {
            block++;
            break;
        }
        int t = board[tx][ty];
        if (t == R.emp) {
            if (empty == -1 && (tx < 14 && ty > 0) && board[tx + 1][ty - 1] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            count++;
            continue;
        } else if (i == 0 && t != role && t != R.emp) {
            block++;
        } else {
            block++;
            break;
        }
    }

    for (int i = 1; TRUE; ++i) {
        int tx = x - i, ty = y + i;
        if (tx < 0 || ty < 0 || tx >= 15 || ty >= 15) {
            block++;
            break;
        }
        int t = board[tx][ty];
        if (t == R.emp) {
            if (empty == -1 && (tx > 0 && ty < 14) && board[tx - 1][ty + 1] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            secondCount++;
            empty++;
            continue;
        } else {
            block++;
            break;
        }
    }

    count += secondCount;
    score += CountScore(count, block, empty);
    //printf("x:%d y:%d score:%d\n",x,y,score);
    return score;
    return 0;
}

int Board::CountScore(int count, int block, int empty) {
    if (empty <= 0) {
        if (count >= 5) return FIVE_SCORE;
        if (block == 0) {
            switch (count) {
                case 1:
                    return ONE_SCORE;
                case 2:
                    return TWO_SCORE;
                case 3:
                    return THREE_SCORE;
                case 4:
                    return FOUR_SCORE;
            }
        }

        if (block == 1) {
            switch (count) {
                case 1:
                    return ONE_DIE_SCORE;
                case 2:
                    return TWO_DIE_SCORE;
                case 3:
                    return THREE_DIE_SCORE;
                case 4:
                    return FOUR_DIE_SCORE;
            }
        }

    } else if (empty == 1 || empty == count - 1) {
        //第1个是空位
        if (count >= 6) {
            return FIVE_SCORE;
        }
        if (block == 0) {
            switch (count) {
                case 2:
                    return TWO_SCORE / 2;
                case 3:
                    return THREE_SCORE;
                case 4:
                    return FOUR_DIE_SCORE;
                case 5:
                    return FOUR_SCORE;
            }
        }

        if (block == 1) {
            switch (count) {
                case 2:
                    return TWO_DIE_SCORE;
                case 3:
                    return THREE_DIE_SCORE;
                case 4:
                    return FOUR_DIE_SCORE;
                case 5:
                    return FOUR_DIE_SCORE;
            }
        }
    } else if (empty == 2 || empty == count - 2) {
        //第二个是空位
        if (count >= 7) {
            return FIVE_SCORE;
        }
        if (block == 0) {
            switch (count) {
                case 3:
                    return THREE_SCORE;
                case 4:
                case 5:
                    return FOUR_DIE_SCORE;
                case 6:
                    return FOUR_SCORE;
            }
        }

        if (block == 1) {
            switch (count) {
                case 3:
                    return THREE_DIE_SCORE;
                case 4:
                    return FOUR_DIE_SCORE;
                case 5:
                    return FOUR_DIE_SCORE;
                case 6:
                    return FOUR_SCORE;
            }
        }

        if (block == 2) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                    return FOUR_DIE_SCORE;
            }
        }
    } else if (empty == 3 || empty == count - 3) {
        if (count >= 8) {
            return FIVE_SCORE;
        }
        if (block == 0) {
            switch (count) {
                case 4:
                case 5:
                    return THREE_SCORE;
                case 6:
                    return FOUR_DIE_SCORE;
                case 7:
                    return FOUR_SCORE;
            }
        }

        if (block == 1) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                    return FOUR_DIE_SCORE;
                case 7:
                    return FOUR_SCORE;
            }
        }

        if (block == 2) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                case 7:
                    return FOUR_DIE_SCORE;
            }
        }
    } else if (empty == 4 || empty == count - 4) {
        if (count >= 9) {
            return FIVE_SCORE;
        }
        if (block == 0) {
            switch (count) {
                case 5:
                case 6:
                case 7:
                case 8:
                    return FOUR_SCORE;
            }
        }

        if (block == 1) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                case 7:
                    return FOUR_DIE_SCORE;
                case 8:
                    return FOUR_SCORE;
            }
        }

        if (block == 2) {
            switch (count) {
                case 5:
                case 6:
                case 7:
                case 8:
                    return FOUR_DIE_SCORE;
            }
        }
    } else if (empty == 5 || empty == count - 5) {
        return FIVE_SCORE;
    }

    return 0;
}

bool Board::cmp(point x, point y) {
    return x.score > y.score;
}
