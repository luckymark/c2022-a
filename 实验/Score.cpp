#include "Score.h"
#include "GameInit.h"
//score has BUG!!!!!!!!!!!!!!
int score(int color)
{
	int score = 0;
	short judgeLb = 0, judgeWb = 0, judgeDb = 0;
	short judgeLa = 0, judgeWa = 0, judgeDa = 0;
	if(score == 1)
	{
		//成5
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLb = (Board[i][j] == 1) && (Board[i + 1][j] == 1) && (Board[i + 2][j] == 1) && (Board[i + 3][j] == 1) && (Board[i + 4][j] == 1);
				judgeWb = (Board[i][j] == 1) && (Board[i][j + 1] == 1) && (Board[i][j + 2] == 1) && (Board[i][j + 3] == 1) && (Board[i][j + 4] == 1);
				judgeDb = (Board[i][j] == 1) && (Board[i + 1][j + 1] == 1) && (Board[i + 2][j + 2] == 1) && (Board[i + 3][j + 3] == 1) && (Board[i + 4][j + 4] == 1);
				if (judgeLb || judgeWb || judgeDb) {
					score += 1000000;
				}
			}
		}
		//活四
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLb = ((Board[i][j] == 0) && (Board[i + 1][j] == 1) && (Board[i + 2][j] == 1) && (Board[i + 3][j] == 1) && (Board[i + 4][j] == 1) && (Board[i + 5][j] == 0) && (i + 4 < 15));
				judgeWb = ((Board[i][j] == 0) && (Board[i][j + 1] == 1) && (Board[i][j + 2] == 1) && (Board[i][j + 3] == 1) && (Board[i][j + 4] == 1) && (Board[i][j + 5] == 0) && (j + 4 < 15));
				judgeDb = ((Board[i][j] == 0) && (Board[i + 1][j + 1] == 1) && (Board[i + 2][j + 2] == 1) && (Board[i + 3][j + 3] == 1) && (Board[i + 4][j + 4] == 1) && (Board[i + 5][j + 5] == 0) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLb || judgeWb || judgeDb) {
					score += 100000;
				}
			}
		}
		//活三
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLb = ((Board[i][j] == 0) && (Board[i + 1][j] == 1) && (Board[i + 2][j] == 1) && (Board[i + 3][j] == 1) && (Board[i + 4][j] == 0) && (i + 4 < 15));
				judgeWb = ((Board[i][j] == 0) && (Board[i][j + 1] == 1) && (Board[i][j + 2] == 1) && (Board[i][j + 3] == 1) && (Board[i][j + 4] == 0) && (j + 4 < 15));
				judgeDb = ((Board[i][j] == 0) && (Board[i + 1][j + 1] == 1) && (Board[i + 2][j + 2] == 1) && (Board[i + 3][j + 3] == 1) && (Board[i + 4][j + 4] == 0) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLb || judgeWb || judgeDb) {
					score += 1000;
				}
			}
		}
		//死四
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLb = ((Board[i][j] == 2) && (Board[i + 1][j] == 1) && (Board[i + 2][j] == 1) && (Board[i + 3][j] == 1) && (Board[i + 4][j] == 1) && (Board[i + 5][j] == 0) && (i + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j] == 1) && (Board[i + 2][j] == 1) && (Board[i + 3][j] == 1) && (Board[i + 4][j] == 1) && (Board[i + 5][j] == 2) && (i + 4 < 15));
				judgeWb = ((Board[i][j] == 2) && (Board[i][j + 1] == 1) && (Board[i][j + 2] == 1) && (Board[i][j + 3] == 1) && (Board[i][j + 4] == 1) && (Board[i][j + 5] == 0) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i][j + 1] == 1) && (Board[i][j + 2] == 1) && (Board[i][j + 3] == 1) && (Board[i][j + 4] == 1) && (Board[i][j + 5] == 2) && (j + 4 < 15));
				judgeDb = ((Board[i][j] == 2) && (Board[i + 1][j + 1] == 1) && (Board[i + 2][j + 2] == 1) && (Board[i + 3][j + 3] == 1) && (Board[i + 4][j + 4] == 1) && (Board[i + 5][j + 5] == 0) && (i + 4 < 15) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j + 1] == 1) && (Board[i + 2][j + 2] == 1) && (Board[i + 3][j + 3] == 1) && (Board[i + 4][j + 4] == 1) && (Board[i + 5][j + 5] == 2) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLb || judgeWb || judgeDb) {
					score += 1000;
				}
			}
		}
		//死三
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLb = ((Board[i][j] == 2) && (Board[i + 1][j] == 1) && (Board[i + 2][j] == 1) && (Board[i + 3][j] == 1) && (Board[i + 4][j] == 0) && (i + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j] == 1) && (Board[i + 2][j] == 1) && (Board[i + 3][j] == 1) && (Board[i + 4][j] == 2) && (i + 4 < 15));
				judgeWb = ((Board[i][j] == 2) && (Board[i][j + 1] == 1) && (Board[i][j + 2] == 1) && (Board[i][j + 3] == 1) && (Board[i][j + 4] == 0) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i][j + 1] == 1) && (Board[i][j + 2] == 1) && (Board[i][j + 3] == 1) && (Board[i][j + 4] == 2) && (j + 4 < 15));
				judgeDb = ((Board[i][j] == 2) && (Board[i + 1][j + 1] == 1) && (Board[i + 2][j + 2] == 1) && (Board[i + 3][j + 3] == 1) && (Board[i + 4][j + 4] == 0) && (i + 4 < 15) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j + 1] == 1) && (Board[i + 2][j + 2] == 1) && (Board[i + 3][j + 3] == 1) && (Board[i + 4][j + 4] == 2) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLb || judgeWb || judgeDb) {
					score += 100;
				}
			}
		}
	}
	else if (color == 2) {
		//成5
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLa = (Board[i][j] == 2) && (Board[i + 1][j] == 2) && (Board[i + 2][j] == 2) && (Board[i + 3][j] == 2) && (Board[i + 4][j] == 2);
				judgeWa = (Board[i][j] == 2) && (Board[i][j + 1] == 2) && (Board[i][j + 2] == 2) && (Board[i][j + 3] == 2) && (Board[i][j + 4] == 2);
				judgeDa = (Board[i][j] == 2) && (Board[i + 1][j + 1] == 2) && (Board[i + 2][j + 2] == 2) && (Board[i + 3][j + 3] == 2) && (Board[i + 4][j + 4] == 2);
				if (judgeLa || judgeWa || judgeDa) {
					score += 1000000;
				}
			}
		}
		//活四
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLa = ((Board[i][j] == 0) && (Board[i + 1][j] == 2) && (Board[i + 2][j] == 2) && (Board[i + 3][j] == 2) && (Board[i + 4][j] == 2) && (Board[i + 5][j] == 0) && (i + 4 < 15));
				judgeWa = ((Board[i][j] == 0) && (Board[i][j + 1] == 2) && (Board[i][j + 2] == 2) && (Board[i][j + 3] == 2) && (Board[i][j + 4] == 2) && (Board[i][j + 5] == 0) && (j + 4 < 15));
				judgeDa = ((Board[i][j] == 0) && (Board[i + 1][j + 1] == 2) && (Board[i + 2][j + 2] == 2) && (Board[i + 3][j + 3] == 2) && (Board[i + 4][j + 4] == 2) && (Board[i + 5][j + 5] == 0) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLa || judgeWa || judgeDa) {
					score += 100000;
				}
			}
		}
		//活三
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLa = ((Board[i][j] == 0) && (Board[i + 1][j] == 2) && (Board[i + 2][j] == 2) && (Board[i + 3][j] == 2) && (Board[i + 4][j] == 0) && (i + 4 < 15));
				judgeWa = ((Board[i][j] == 0) && (Board[i][j + 1] == 2) && (Board[i][j + 2] == 2) && (Board[i][j + 3] == 2) && (Board[i][j + 4] == 0) && (j + 4 < 15));
				judgeDa = ((Board[i][j] == 0) && (Board[i + 1][j + 1] == 2) && (Board[i + 2][j + 2] == 2) && (Board[i + 3][j + 3] == 2) && (Board[i + 4][j + 4] == 0) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLa || judgeWa || judgeDa) {
					score += 1000;
				}
			}
		}
		//死四
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLa = ((Board[i][j] == 1) && (Board[i + 1][j] == 2) && (Board[i + 2][j] == 2) && (Board[i + 3][j] == 2) && (Board[i + 4][j] == 2) && (Board[i + 5][j] == 0) && (i + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j] == 2) && (Board[i + 2][j] == 2) && (Board[i + 3][j] == 2) && (Board[i + 4][j] == 2) && (Board[i + 5][j] == 1) && (i + 4 < 15));
				judgeWa = ((Board[i][j] == 1) && (Board[i][j + 1] == 2) && (Board[i][j + 2] == 2) && (Board[i][j + 3] == 2) && (Board[i][j + 4] == 2) && (Board[i][j + 5] == 0) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i][j + 1] == 2) && (Board[i][j + 2] == 2) && (Board[i][j + 3] == 2) && (Board[i][j + 4] == 2) && (Board[i][j + 5] == 1) && (j + 4 < 15));
				judgeDa = ((Board[i][j] == 1) && (Board[i + 1][j + 1] == 2) && (Board[i + 2][j + 2] == 2) && (Board[i + 3][j + 3] == 2) && (Board[i + 4][j + 4] == 2) && (Board[i + 5][j + 5] == 0) && (i + 4 < 15) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j + 1] == 2) && (Board[i + 2][j + 2] == 2) && (Board[i + 3][j + 3] == 2) && (Board[i + 4][j + 4] == 2) && (Board[i + 5][j + 5] == 1) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLa || judgeWa || judgeDa) {
					score += 1000;
				}
			}
		}
		//死三
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				judgeLa = ((Board[i][j] == 1) && (Board[i + 1][j] == 2) && (Board[i + 2][j] == 2) && (Board[i + 3][j] == 2) && (Board[i + 4][j] == 0) && (i + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j] == 2) && (Board[i + 2][j] == 2) && (Board[i + 3][j] == 2) && (Board[i + 4][j] == 1) && (i + 4 < 15));
				judgeWa = ((Board[i][j] == 1) && (Board[i][j + 1] == 2) && (Board[i][j + 2] == 2) && (Board[i][j + 3] == 2) && (Board[i][j + 4] == 0) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i][j + 1] == 2) && (Board[i][j + 2] == 2) && (Board[i][j + 3] == 2) && (Board[i][j + 4] == 1) && (j + 4 < 15));
				judgeDa = ((Board[i][j] == 1) && (Board[i + 1][j + 1] == 2) && (Board[i + 2][j + 2] == 2) && (Board[i + 3][j + 3] == 2) && (Board[i + 4][j + 4] == 0) && (i + 4 < 15) && (j + 4 < 15)) ||
					((Board[i][j] == 0) && (Board[i + 1][j + 1] == 2) && (Board[i + 2][j + 2] == 2) && (Board[i + 3][j + 3] == 2) && (Board[i + 4][j + 4] == 1) && (i + 4 < 15) && (j + 4 < 15));
				if (judgeLa || judgeWa || judgeDa) {
					score += 100;
				}
			}
		}
	}

	return score;
}
