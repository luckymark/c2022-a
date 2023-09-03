#include"ChessData.h"
#include<string.h>
#include<time.h>
#include<stdlib.h>

void initChessData(ChessData* data){
	if (!data) { 
		return; }
	memset(data->chessmap, 0, sizeof(data->chessmap));
	memset(data->chesspoint, 0, sizeof(data->chesspoint));
	data->sideflag = true;
}
void newChessmap(ChessData*data, int row, int col) {
	if (!data) {
		return;
	}
	if (data->sideflag) {
		data->chessmap[row][col] = 1;
	}
	else {
		data->chessmap[row][col] = -1;
	}
	data->sideflag = !data->sideflag;
}
void value(ChessData* data) {

	if (!data) {
		return;
	}
	int playernum = 0;
	int ainum = 0;
	int emptynum = 0;
	memset(data->chesspoint, 0, sizeof(data->chesspoint));
	for (int row = 0;row < boardsize;row++)
		for (int col = 0;col < boardsize;col++) {
			if (row >= 0 && col >= 0 && data->chessmap[row][col] == 0) {
				int pos[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int k = 0;k < 4;k++) {
					int x = pos[k][0];
					int y = pos[k][1];
					playernum = 0;
					ainum = 0;
					emptynum = 0;
					for (int i = 1;i <= 4;i++) {
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->chessmap[row + i * y][col + i * x] == 1) {
							playernum++;
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->chessmap[row + i * y][col + i * x] == 0) {
							emptynum++;
							break;
						}
						else break;
					}
					for (int i = 1;i <= 4;i++) {
						if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->chessmap[row - i * y][col - i * x] == 1) {
							playernum++;
						}
						else if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->chessmap[row - i * y][col - i * x] == 0) {
							emptynum++;
							break;
						}
						else break;
					}

					if (playernum == 1) {
						data->chesspoint[row][col] += 10;
					}
					else if (playernum == 2) {
						if (emptynum == 1) {
							data->chesspoint[row][col] += 30;
						}
						else if (emptynum == 2) {
							data->chesspoint[row][col] += 40;
						}
					}
					else if (playernum == 3) {
						if (emptynum == 1) {
							data->chesspoint[row][col] += 60;
						}
						else if (emptynum == 2) {
							data->chesspoint[row][col] += 200;
						}
					}
					else if (playernum == 4) {
						data->chesspoint[row][col] += 20000;
					}
					emptynum = 0;

					for (int i = 0;i <= 4;i++) {
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->chessmap[row + i * y][col + i * x] == -1) {
							ainum++;
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->chessmap[row + i * y][col + i * x] == 0) {
							emptynum++;
							break;
						}
						else break;
					}
					for (int i = 0;i <= 4;i++) {
						if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->chessmap[row - i * y][col - i * x] == -1) {
							ainum++;
						}
						else if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->chessmap[row - i * y][col - i * x] == 0) {
							emptynum++;
							break;
						}
						else break;
					}
					if (ainum == 0) {
						data->chesspoint[row][col] += 5;
					}
					else if (ainum == 1) {
						data->chesspoint[row][col] += 10;
					}
					else if (ainum == 2) {
						if (emptynum == 1) {
							data->chesspoint[row][col] += 25;
						}
						else if (emptynum == 2) {
							data->chesspoint[row][col] += 50;
						}
					}
					else if (ainum == 3) {
						if (emptynum == 1) {
							data->chesspoint[row][col] += 55;
						}
						else if (emptynum == 2) {
							data->chesspoint[row][col] += 300;
						}
					}
					else if (ainum >= 4) {
						data->chesspoint[row][col] += 30000;
					}
				}
			}
		}
	}
Cpoint move(ChessData* data) {
	value(data);
	int maxscore = 0;
	Cpoint maxpoints[boardsize * boardsize] = { 0 };
	int k = 0;
	for (int row = 0;row < boardsize;row++) 
		for (int col = 0;col < boardsize;col++) {
			if (data->chessmap[row][col] == 0) {
				if (data->chesspoint[row][col] > maxscore) {
					memset(maxpoints, 0, sizeof(maxpoints));
					k = 0;
					maxscore = data->chesspoint[row][col];
					maxpoints[k].row = row;
					maxpoints[k].col = col;
				}
				else if (data->chesspoint[row][col] == maxscore) {
					k++;
					maxpoints[k].row = row;
					maxpoints[k].col = col;
				}
			}
		}
	if (k > 0) {
		srand((unsigned)time(0));  
		int renju = rand() % k;
		return maxpoints[renju];
	}
	else {return maxpoints[k];}
}

bool Win(ChessData* game, int row, int col) {
	for (int i = 0;i <= 4;i++) {
		if (col - i >= 0 && col - i + 4 < boardsize && game->chessmap[row][col - i] == game->chessmap[row][col - i + 1] && game->chessmap[row][col - i] == game->chessmap[row][col - i + 2] && game->chessmap[row][col - i] == game->chessmap[row][col - i + 3] && game->chessmap[row][col - i] == game->chessmap[row][col - i + 4])
			return true;
	}
	for (int i = 0;i <= 4;i++) {
		if (row - i >= 0 && row - i + 4 < boardsize && game->chessmap[row - i][col] == game->chessmap[row - i + 1][col] && game->chessmap[row - i][col] == game->chessmap[row - i + 2][col] && game->chessmap[row - i][col] == game->chessmap[row - i + 3][col] && game->chessmap[row - i][col] == game->chessmap[row - i + 4][col])
			return true;
	}
	for (int i = 0;i <= 4;i++) {
		if (row + i - 4 >= 0 && row + i < boardsize && col - i >= 0 && col - i + 4 < boardsize && game->chessmap[row + i][col - i] == game->chessmap[row + i - 1][col - i + 1] && game->chessmap[row + i][col - i] == game->chessmap[row + i - 2][col - i + 2] && game->chessmap[row + i][col - i] == game->chessmap[row + i - 3][col - i + 3] && game->chessmap[row + i][col - i] == game->chessmap[row + i - 4][col - i + 4])
			return true;
	}
	for (int i = 0;i <= 4;i++) {
		if (row - i >= 0 && row - i + 4 < boardsize && col - i > 0 && col - i + 4 < boardsize && game->chessmap[row - i][col - i] == game->chessmap[row - i + 1][col - i + 1] && game->chessmap[row - i][col - i] == game->chessmap[row - i + 2][col - i + 2] && game->chessmap[row - i][col - i] == game->chessmap[row - i + 3][col - i + 3] && game->chessmap[row - i][col - i] == game->chessmap[row - i + 4][col - i + 4])
			return true;
	}
	return false;
}