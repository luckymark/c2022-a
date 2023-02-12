#include<easyx.h>
#include"chessdata.h"
#include"ifwin.h"
#include"trasprent_img.h"
#include"deducation.h"
#include"over.h"
extern struct chessdata game;


extern int clickposhang, clickposlie, lie_est, hang_est;
extern int turn;

extern IMAGE chess_black;
extern IMAGE chess_white;
extern IMAGE b_mask;
extern IMAGE w_mask;
extern int A, B;

void robot()
{
	int temp2 = -1000000,t=0,m,n;
	for (int i = min1; i < max2; i++)
	{
		for (int j = min1; j < max2; j++)
		{

			if (game.chessmap[i][j] == 0)
			{
				t = 0;
				for (m = -1; m < 2; m++) {
					for (n = -1; n < 2; n++) {
						if (game.chessmap[i + m][j + n] != 0) {
							t++;
						}
					}
				}
				if (t != 0)
				{
					game.chessmap[i][j] = -1;
					if (ifwin(i, j, -1) == 1)
					{
						int x = margin + (j-5) * node_size - node_size / 2;
						int y = margin + (i-5) * node_size - node_size / 2;
						puttrimage(x, y, &w_mask, &chess_white);
						over(3);
						return;
						
					}
					int temp = deduction(1, 2, A, B);
					game.chessmap[i][j] = 0;
					if (temp > temp2)
					{
						hang_est = i;
						lie_est = j;
						temp2 = temp;
					}
				}
			}
		}
	}

	int x = margin + (lie_est-5) * node_size - node_size / 2;
	int y = margin + (hang_est-5) * node_size - node_size / 2;
	puttrimage(x, y, &w_mask, &chess_white);
	game.chessmap[hang_est][lie_est] = -1;
	if (ifwin(hang_est, lie_est, -1))
	{
		Sleep(3000);
		over(3);
		
	}

}

//int player_est()
//{
//	int temp2_p = 1000000;
//	for (int i = 0; i < 15; i++)
//	{
//		for (int j = 0; j < 15; j++)
//		{
//			if (game.chessmap[i][j] == -1 || game.chessmap[i][j] == 1)
//				continue;
//			else if (game.chessmap[i][j] == 0)
//			{
//				game.chessmap[i][j] = 1;
//				int temp_p = assessmap();
//				game.chessmap[i][j] = 0;
//				if (temp_p < temp2_p)
//				{
//					temp2_p = temp_p;
//				}
//
//
//			}
//		}
//	}
//	return temp2_p;
//}
