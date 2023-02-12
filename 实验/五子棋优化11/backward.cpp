#include"chessdata.h"
#include"creatmap.h"
#include"ifwin.h"
#include"trasprent_img.h"


extern struct chessdata game;
extern IMAGE chess_black;

extern IMAGE b_mask;
extern IMAGE w_mask;
extern IMAGE back;

extern int clickposhang, clickposlie, lie_est, hang_est;

void backward()
{
	IMAGE fugai;
	loadimage(&fugai, "wuzi/fugai1.jpg", node_size, node_size);
	int x = margin + (lie_est-5) * node_size - node_size / 2;
	int y = margin + (hang_est-5) * node_size - node_size / 2;
	putimage(x, y, &fugai);
	int x2 = margin + (clickposlie) * node_size - node_size / 2;
	int y2 = margin + (clickposhang) * node_size - node_size / 2;
	putimage(x2, y2, &fugai);
	game.chessmap[clickposhang+5][clickposlie+5] = 0;
	game.chessmap[hang_est][lie_est] = 0;
	MOUSEMSG msg2;
	while (1)
	{
		msg2 = GetMouseMsg();
		if (msg2.uMsg == WM_LBUTTONDOWN && clickboard(msg2) && msg2.x > 50 && msg2.x < 750 && msg2.y>50 && msg2.y < 750)
		{
			int x = margin + clickposlie * node_size - node_size / 2;
			int y = margin + clickposhang * node_size - node_size / 2;
			puttrimage(x, y, &b_mask, &chess_black);
			game.chessmap[clickposhang+5][clickposlie+5] = 1;
			if (ifwin(clickposhang, clickposlie, 1))
				loadimage(0, "wuzi/win.jpg");
			break;
		}
	}
}