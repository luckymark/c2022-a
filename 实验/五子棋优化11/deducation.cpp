//#include"main.h"

#include"score_access.h"
#include"ifwin.h"
#include"chessdata.h"

extern struct chessdata game;
extern int turn;
extern int A, B;


int deduction(int sex,int depth,int a,int b)
{
	int m, n, i, j, t = 0, br = 0;
	long double va = 0;
	if (depth == 0||end()!=0)   
	{
		return assessmap();       
	}
	else if (sex  == 1)     //玩家回合
	{
		for (m = min1; m < max2; m++)
		{
			if (br == 1) {   
				break;
			}
			for (n =min1; n < max2; n++)
			{
				if (game.chessmap[m][n]== 0)   
				{
					if (turn < 80) {
						t = 0;
						for (i = -1; i < 2; i++) {
							for (j = -1; j < 2; j++) {
								if (game.chessmap[i + m][j + n]!= 0) {
									t++;     //偏僻点剪枝
								}
							}
						}
					}
					else {
						t = 1;
					}
					if (t == 0)   //偏僻
					{
						va = B;
					}
					else {
						game.chessmap[m][n] = 1;    //棋下在这个地方
						va = deduction(-sex, depth - 1, a, b);
						game.chessmap[m][n] = 0;      
					}
					if (va < b)    
					{
						b = va;
					}
					if (b < a)
					{
						break;    //b剪枝
						br = 1;
					}
				}
			}
		}
		return b; //返回分数
	}
	else if (sex ==-1)     //电脑回合
	{
		for (m = min1; m <max2; m++)
		{
			if (br == 1) {   //a剪枝 
				break;
			}
			for (n = min1; n <max2; n++)
			{
				if (game.chessmap[m][n] == 0)     //为空
				{
					if (turn < 80) {
						t = 0;
						for (i = -1; i < 2; i++) {
							for (j = -1; j < 2; j++) {
								if (game.chessmap[i + m][j + n] != 0) {
									t++;     //偏僻点剪枝
								}
							}
						}
					}
					else {
						t = 1;
					}
					if (t == 0)   //偏僻
					{
						va = A;
					}
					else {
						game.chessmap[m][n] = -1;     
						va = deduction( -sex, depth - 1, a, b);
						game.chessmap[m][n] = 0;   
					}
					if (va > a)   
					{
						a = va;
					}
					if (b < a)
					{
						break;    
						br = 1;
					}
				}
			}
		}
		return a;
	}
	return 0;

}

//for (m = MIN; m < MAX; m++)
//{
//	if (br == 1) {   //b剪枝
//		break;
//	}
//	for (n = MIN; n < MAX; n++)
//	{
//		if (p[m][n].state == 0)   //为空
//		{
//			if (num < 80) {
//				t = 0;
//				for (i = -1; i < 2; i++) {
//					for (j = -1; j < 2; j++) {
//						if (p[i + m][j + n].state != 0) {
//							t++;     //偏僻点剪枝
//						}
//					}
//				}
//			}
//			else {
//				t = 1;
//			}
//			if (t == 0)   //偏僻
//			{
//				va = B;
//			}
//			else {
//				p[m][n].state = -1;    //棋下在这个地方
//				va = deduction(p, sex + 1, depth - 1, a, b);
//				p[m][n].state = 0;      //撤回
//			}
//			if (va < b)    //找最小值
//			{
//				b = va;
//			}
//			if (b < a)
//			{
//				break;    //b剪枝
//				br = 1;
//			}
//		}
//	}
//}
//return b; //返回分数