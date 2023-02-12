#include"backward.h"
#include"chessdata.h"
#include"ifwin.h"
#include"robot.h"
#include"creatmap.h"
#include"trasprent_img.h"
#include"over.h"
#include<stdio.h>



IMAGE chess_black;
IMAGE chess_white;
IMAGE b_mask;
IMAGE w_mask;
IMAGE back;

extern char name1[30];
extern FILE* precord;

struct chessdata game;
int* igame = (int*)malloc(sizeof(int) * 300);

int clickposhang, clickposlie, lie_est, hang_est, turn = 0, A = -100000, B = 100000;


void begin()
{
	while (turn < 10000)
	{


		MOUSEMSG msg;
		while (1)
		{

			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 800 && msg.x < 1000 && msg.y>100 && msg.y <200)
			{
				init();
				initchessdata(&game);
				begin();
				
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 800 && msg.x < 1000 && msg.y>250 && msg.y <350)
			{
				backward();
				break;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 800 && msg.x < 1000 && msg.y>400 && msg.y < 500)
			{
				break;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 800 && msg.x < 1000 && msg.y>550 && msg.y < 650)
			{
				fopen_s(&precord, "存档.txt", "w");
				fprintf(precord, "%s\n%d\n", name1,turn);
				for (int a = 0; a < 25; a++)
				{
					for (int b = 0; b < 25; b++)
					{
						fprintf(precord, "%d\n", game.chessmap[a][b]);
					}
				}
				printf("\n以存档，继续游戏只需重新开始，选择读档，欢迎下次光临\n");
				exit(0);
				
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && clickboard(msg) && msg.x >50 && msg.x <750 && msg.y>50 && msg.y < 750)
			{
				int x = margin + clickposlie * node_size - node_size / 2;
				int y = margin + clickposhang * node_size - node_size / 2;
				puttrimage(x, y, &b_mask, &chess_black);
				game.chessmap[clickposhang + 5][clickposlie + 5] = 1;
				if (ifwin(clickposhang + 5, clickposlie + 5, 1))
				{
					over(2);
				}
				break;
			}
		}

		robot();


		turn++;
	}
}