#include"chessdata.h"
#include<easyx.h>
#include<graphics.h>
#include<math.h>

extern IMAGE chess_black;
extern IMAGE chess_white;
extern IMAGE b_mask;
extern IMAGE w_mask;

IMAGE Board;
IMAGE Restart;
IMAGE Regret;
IMAGE Pull;
IMAGE Late;

extern struct chessdata game;

extern int clickposhang, clickposlie, lie_est, hang_est;
extern int turn;


void init() {
	//创建棋盘
	initgraph(1050,800);
	setbkcolor(RGB(254, 216, 177));
	cleardevice();
	setlinestyle(PS_SOLID, 5);
	setlinecolor(RGB(255,153,177));
	rectangle(10, 10, 1040, 790);

	settextstyle(25,12, "宋体");
	settextcolor(RGB(020,230,255));
	outtextxy(20,20, "指导老师：俸大神（超牛(≧&≦)ゞ）");
	outtextxy(20,760, "作者：鲁基俊  学号：2022080907025");
	

	loadimage(&Board, "wuzi/ChessBoard.jpg", 700,700);
	putimage(50, 50, &Board);

	loadimage(&Restart, "wuzi/restart.png",200,100);
	putimage(800,100, &Restart);
	loadimage(&Regret, "wuzi/regret.png",200, 100);
	putimage(800,250, &Regret);
	loadimage(&Late, "wuzi/late.png", 200, 100);
	putimage(800, 400, &Late);
	loadimage(&Pull, "wuzi/pull.png", 200, 100);
	putimage(800, 550, &Pull);





	loadimage(&chess_black, "wuzi/B-2.jpg", node_size-5, node_size-5, true);
	loadimage(&chess_white, "wuzi/w-2.jpg", node_size-5, node_size-5, true);
	loadimage(&b_mask, "wuzi/B-1.jpg", node_size-5, node_size-5, true);
	loadimage(&w_mask, "wuzi/w-1.jpg", node_size-5, node_size-5, true);

	initchessdata(&game);

}

bool clickboard(MOUSEMSG msg) {
	int lie = (msg.x - margin) / node_size;
	int hang = (msg.y - margin) / node_size;

	int lefttop_x = margin + lie * node_size;
	int lefttop_y = margin + hang * node_size;
	int selctpos = false,dis;
	do {
		for(int hh=0;hh<2;hh++)
			for (int ll = 0; ll < 2; ll++)
			{
				int posx = lefttop_x + hh*node_size;
				int posy = lefttop_y+ll*node_size;
				dis = sqrt((msg.x - posx) * (msg.x - posx) + (msg.y - posy) * (msg.y - posy));
				if (dis < ifdown) {
					clickposhang = hang+ll;
					clickposlie = lie+hh;
					selctpos = true;
					break;
				}
			}
	} while (0);
	if (game.chessmap[clickposhang+5][clickposlie+5] == -1 || game.chessmap[clickposhang+5][clickposlie+5] == 1)
		selctpos = 0;
	return selctpos;
}		
		

