#include "wu.h"
int tuple6type[4][4][4][4][4][4];
void init_tuple6type() {
	memset(tuple6type, 0, sizeof(tuple6type));//全部设为0
	//白连5,ai赢
	tuple6type[2][2][2][2][2][2] = WIN;
	tuple6type[2][2][2][2][2][0] = WIN;
	tuple6type[0][2][2][2][2][2] = WIN;
	tuple6type[2][2][2][2][2][1] = WIN;
	tuple6type[1][2][2][2][2][2] = WIN;
	tuple6type[3][2][2][2][2][2] = WIN;//边界考虑
	tuple6type[2][2][2][2][2][3] = WIN;
	//黑连5,ai输
	tuple6type[1][1][1][1][1][1] = LOSE;
	tuple6type[1][1][1][1][1][0] = LOSE;
	tuple6type[0][1][1][1][1][1] = LOSE;
	tuple6type[1][1][1][1][1][2] = LOSE;
	tuple6type[2][1][1][1][1][1] = LOSE;
	tuple6type[3][1][1][1][1][1] = LOSE;
	tuple6type[1][1][1][1][1][3] = LOSE;
	//白活4
	tuple6type[0][2][2][2][2][0] = FLEX4;
	//黑活4
	tuple6type[0][1][1][1][1][0] = flex4;
	//白活3
	tuple6type[0][2][2][2][0][0] = FLEX3;
	tuple6type[0][0][2][2][2][0] = FLEX3;
	tuple6type[0][2][0][2][2][0] = FLEX30;
	tuple6type[0][2][2][0][2][0] = FLEX30;
	//黑活3
	tuple6type[0][1][1][1][0][0] = flex3;
	tuple6type[0][0][1][1][1][0] = flex3;
	tuple6type[0][1][0][1][1][0] = flex30;
	tuple6type[0][1][1][0][1][0] = flex30;
	//白活2
	tuple6type[0][2][2][0][0][0] = FLEX2;
	tuple6type[0][2][0][2][0][0] = FLEX2;
	tuple6type[0][2][0][0][2][0] = FLEX2;
	tuple6type[0][0][2][2][0][0] = FLEX2;
	tuple6type[0][0][2][0][2][0] = FLEX2;
	tuple6type[0][0][0][2][2][0] = FLEX2;
	//黑活2
	tuple6type[0][1][1][0][0][0] = flex2;
	tuple6type[0][1][0][1][0][0] = flex2;
	tuple6type[0][1][0][0][1][0] = flex2;
	tuple6type[0][0][1][1][0][0] = flex2;
	tuple6type[0][0][1][0][1][0] = flex2;
	tuple6type[0][0][0][1][1][0] = flex2;
	//白活1
	tuple6type[0][2][0][0][0][0] = FLEX1;
	tuple6type[0][0][2][0][0][0] = FLEX1;
	tuple6type[0][0][0][2][0][0] = FLEX1;
	tuple6type[0][0][0][0][2][0] = FLEX1;
	//黑活1
	tuple6type[0][1][0][0][0][0] = flex1;
	tuple6type[0][0][1][0][0][0] = flex1;
	tuple6type[0][0][0][1][0][0] = flex1;
	tuple6type[0][0][0][0][1][0] = flex1;
	tuple6type[3][2][2][2][0][2] = BLOCK40;
	tuple6type[3][2][0][2][2][2] = BLOCK40;
	tuple6type[2][0][2][2][2][3] = BLOCK40;
	tuple6type[2][2][0][2][2][3] = BLOCK40;
	tuple6type[2][2][2][0][2][3] = BLOCK40;
	tuple6type[2][0][2][2][2][3] = BLOCK40;
	tuple6type[0][2][2][0][2][2] = BLOCK40;
	tuple6type[2][2][0][2][2][2] = BLOCK40;
	tuple6type[2][2][2][0][2][0] = BLOCK40;
	tuple6type[0][2][0][2][2][2] = BLOCK40;
	tuple6type[3][1][1][1][0][1] = block40;
	tuple6type[3][1][0][1][1][1] = block40;
	tuple6type[1][0][1][1][1][3] = block40;
	tuple6type[1][1][0][1][1][3] = block40;
	tuple6type[1][1][1][0][1][3] = block40;
	tuple6type[1][0][1][1][1][3] = block40;
	tuple6type[3][2][2][0][2][0] = BLOCK401;
	tuple6type[0][2][0][2][2][3] = BLOCK401;
	int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:左5中黑个数,y:左5中白个数,ix:右5中黑个数,iy:右5中白个数
	for (p1 = 0; p1 < 4; ++p1) {
		for (p2 = 0; p2 < 3; ++p2) {
			for (p3 = 0; p3 < 3; ++p3) {
				for (p4 = 0; p4 < 3; ++p4) {
					for (p5 = 0; p5 < 3; ++p5) {
						for (p6 = 0; p6 < 4; ++p6) {
							x = y = ix = iy = 0;

							if (p1 == 1)x++;
							else if (p1 == 2)y++;

							if (p2 == 1) { x++; ix++; }
							else if (p2 == 2) { y++; iy++; }

							if (p3 == 1) { x++; ix++; }
							else if (p3 == 2) { y++; iy++; }

							if (p4 == 1) { x++; ix++; }
							else if (p4 == 2) { y++; iy++; }

							if (p5 == 1) { x++; ix++; }
							else if (p5 == 2) { y++; iy++; }

							if (p6 == 1)ix++;
							else if (p6 == 2)iy++;

							if (p1 == 3 || p6 == 3) {//有边界
								if (p1 == 3 && p6 != 3) {//左边界
									//白冲4
									if (ix == 0 && iy == 4) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
									}
									//黑冲4
									if (ix == 4 && iy == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block4;
									}
									//白眠3
									if (ix == 0 && iy == 3) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
									}
									//黑眠3
									if (ix == 3 && iy == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block3;
									}
									//白眠2
									if (ix == 0 && iy == 2) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
									}
									//黑眠2
									if (ix == 2 && iy == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block2;
									}
								}
								else if (p6 == 3 && p1 != 3) {//右边界
									//白冲4
									if (x == 0 && y == 4) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
									}
									//黑冲4
									if (x == 4 && y == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block4;
									}
									//黑眠3
									if (x == 3 && y == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
									}
									//白眠3
									if (x == 0 && y == 3) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block3;
									}
									//黑眠2
									if (x == 2 && y == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
									}
									//白眠2
									if (x == 0 && y == 2) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block2;
									}
								}
							}
							else {//无边界
								//白冲4
								if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
								}
								//黑冲4
								if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = block4;
								}
								//白眠3
								if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
								}
								//黑眠3
								if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = block3;
								}
								//白眠2
								if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
								}
								//黑眠2
								if ((x == 2 && y == 0) || (ix == 2 && iy == 0)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = block2;
								}
							}
						}
					}
				}
			}
		}
	}
}



EVALUATION evaluate(int board[15][15]) {
	//各棋型权重
	init_tuple6type();
	int weight[22] = { 0,80000,-10000000,40000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3,400,-8000,400,-100000,20};
	      //                         白5         黑5        白4      黑4   白04    黑04  白3   黑3 白03  黑03白2   黑2  白003  黑003
	//int weight[22] = { 0,1000000,-10000000,50000,-80000,4000,-50000,400,-40000,200,-400,20,-40,1,-4,1,-4,400,-30000,50000,-80000,20 };
	////                                白5     黑5        白4    黑4    白04    黑04    白3   黑3  白03黑03白2   黑2    白003  黑003 白4.  黑4.   白03.
	int i, j, type;
	int stat[4][22];//统计4个方向上每种棋型的个数
	memset(stat, 0, sizeof(stat));

	int A[17][17];//包括边界的虚拟大棋盘,board[i][j]=A[i-1][j-1],3表示边界
	for (int i = 0; i < 17; ++i)A[i][0] = 3;
	for (int i = 0; i < 17; ++i)A[i][16] = 3;
	for (int j = 0; j < 17; ++j)A[0][j] = 3;
	for (int j = 0; j < 17; ++j)A[16][j] = 3;
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			A[i + 1][j + 1] = board[i][j];

	//判断横向棋型
	for (i = 1; i <= 15; ++i) {
		for (j = 0; j < 12; ++j) {
			type = tuple6type[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
			stat[0][type]++;
		}
	}
	//判断竖向棋型
	for (j = 1; j <= 15; ++j) {
		for (i = 0; i < 12; ++i) {
			type = tuple6type[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
			stat[1][type]++;
		}
	}
	//判断左上至右下棋型
	for (i = 0; i < 12; ++i) {
		for (j = 0; j < 12; ++j) {
			type = tuple6type[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
			stat[2][type]++;
		}
	}
	//判断右上至左下棋型
	for (i = 0; i < 12; ++i) {
		for (j = 5; j < 17; ++j) {
			type = tuple6type[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i + 5][j - 5]];
			stat[3][type]++;
		}
	}

	EVALUATION eval;
	memset(eval.STAT, 0, sizeof(eval.STAT));
	int score = 0;
	for (i = 1; i < 17; ++i) {
		score += (stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]) * weight[i];//初步计分

		int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];//统计所有方向上部分棋型的个数
		if (i == WIN)eval.STAT[WIN] = count;
		else if (i == LOSE)eval.STAT[LOSE] = count;
		else if (i == FLEX4)eval.STAT[FLEX4] = count;
		else if (i == flex4)eval.STAT[flex4] = count;
		else if (i == block4)eval.STAT[block4] = count;
	}
	eval.result = R_DRAW;

	//白赢
	if (eval.STAT[WIN] > 0)eval.result = R_WHITE;
	//黑赢
	else if (eval.STAT[LOSE] > 0)eval.result = R_BLACK;

	eval.score = score;
	return eval;
}
double MAXMINvalue(int cstore[15][15], int deep, double alpha, double beta)
{
	int result;
	result = evaluate(cstore).result;
	if (deep == 0 || result != R_DRAW) {//如果模拟落子可以分出输赢，那么直接返回结果，不需要再搜索
		if (deep == 0)
		{
			point P;
			P = seekpoint(cstore, deep);//生成最佳的可能落子位置
			return (P.tscore[0]);//返回最佳位置对应的最高分
		}
		else
			return evaluate(cstore).score;
	}
	else if (deep % 2 == 0 && deep != 0)
	{
		point P;
		int m = 0, n = 0;
		P = seekpoint(cstore, deep);
		if (P.tscore[0] == GO)
			return 0;
		for (int i = 0; i < numb; ++i) {
			cstore[P.x[i]][P.y[i]] = C_WHITE;//模拟己方落子
			double a = MAXMINvalue(cstore, deep - 1, alpha, beta);
			cstore[P.x[i]][P.y[i]] = C_NONE;//还原落子
			if (a > alpha) {
				alpha = a;
				m = P.x[i];
				n = P.y[i];
			}
			if (beta <= alpha)
				break;//剪枝
		}
		if (deep == DEEP) {
			downpoint(m, n);
		}
		return alpha;
	}
	else {//min层
		point P = seekpoint(cstore, deep);
		for (int i = 0; i < numb; ++i) {
			cstore[P.x[i]][P.y[i]] = C_BLACK ;//模拟敌方落子
			double a = MAXMINvalue(cstore, deep - 1, alpha, beta);
			cstore[P.x[i]][P.y[i]] = C_NONE;//还原落子
			if (a < beta)
				beta = a;
			if (beta <= alpha)
				break;//剪枝
		}
		return beta;
	}
}
point seekpoint(int store[15][15], int deep)//搜索10个最优点
{
	double rate[15][15];
	double worth[15][15];
	int stick[15][15];
	point P;
	int y1 = 0;
	for (int x1 = 0; x1 < 8; x1++) {
		for (; y1 < 15 - x1; y1++) {
			rate[x1][y1] = 1 + x1 * 0.1;
			rate[y1][x1] = 1 + x1 * 0.1;
			rate[14 - x1][y1] = 1 + x1 * 0.1;
			rate[y1][14 - x1] = 1 + x1 * 0.1;
		}
		y1 = 0;
		y1 = 1 + x1;

	}//对棋盘进行整体赋值
	int mark = 0, m = 0, n = 0;
	for (int x1 = 0; x1 < 15; x1++) {
		for (int y1 = 0; y1 < 15; y1++) {
			if (store[x1][y1] != 0)
				stick[x1][y1] = 1;
		}
	}//标记点
	memset(worth, 0, sizeof(worth));
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (stick[i][j] != 0) {
				for (int k = -3; k <= 3; ++k) {
					if ((i + k >= 0 && i + k < 15) && (stick[i + k][j] != 1)) {
						stick[i + k][j] = C_PLACE;//空点
						if ((j + k >= 0 && j + k < 15) && (stick[i + k][j + k] != 1))stick[i + k][j + k] = C_PLACE;
						if ((j - k >= 0 && j - k < 15) && (stick[i + k][j - k] != 1))stick[i + k][j - k] = C_PLACE;
					}
					if ((j + k >= 0 && j + k < 15) && (stick[i][j + k] != 1))stick[i][j + k] = C_PLACE;
				}
			}
		}
	}
	if (deep % 2 == 0)
	{
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				worth[i][j] = -INT_MAX;
				if (stick[i][j] == C_PLACE) {
					EVALUATION result;
					result = evaluate(store);
					int count = 0;
					if (result.STAT[FLEX4] != 0)//判断是否结束
					{
						count = 1;
					}
					store[i][j] = C_WHITE;
					worth[i][j] = evaluate(store).score * rate[i][j];
					result = evaluate(store);
					store[i][j] = C_NONE;
					if ((deep == DEEP) && (result.STAT[WIN] != 0))
					{
						
							mark = 1;
							m = i;
							n = j;
						
					}
					if (((deep == DEEP) && (result.STAT[FLEX4] != 0)) && (count == 0))
					{
						if ((result.STAT[flex4] == 0)&& (result.STAT[block4]==0))
						{
							mark = 1;
							m = i;
							n = j;
						}
					}
				}
			}
		}
	}
	if (mark == 1)
	{
		downpoint(m, n);
		P.tscore[0] = GO;//一个特殊值
		return P;
	}
	if (deep % 2 == 1)
	{
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				worth[i][j] = -INT_MAX;
				if (stick[i][j] == 2) {
					store[i][j] = C_BLACK;
					worth[i][j] = evaluate(store).score * rate[i][j];
					store[i][j] = C_NONE;
				}
			}
		}
	}

	double w;
	for (int k = 0; k < numb; ++k) {
		w = -INT_MAX;
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (worth[i][j] > w) {
					w = worth[i][j];
					P.x[k] = i;
					P.y[k] = j;
				}
			}
		}
		P.tscore[k] = w;//逐一得出最优值

		worth[P.x[k]][P.y[k]] = -INT_MAX;//清除掉上一点,计算下一点的位置和分数
	}
	return P;
}

