#include<easyx.h>
#include<conio.h>
#include<time.h>
#include<graphics.h>
#include<Windows.h>
#include<stdlib.h>

#include"point.h"
#include"UI.h"
#include"AI.h"
#include"check.h"
#include "setting.h"

int ni = 0, nj = 0, nx = 0, ny = 0;//for regret
int num = 0;
place walk[230];
int len = 0;//for walk
place record_for_check[230];
int clen = 0;
point record_for_state[25][25];
int player;
int no_robot = 0;

void begin(struct point state[25][25], int play) {
	MOUSEMSG m;
	bTurn = INFINITY;
	int x, y, i, j, e, f = 0;
	point p[25][25];
	for (int i = 0; i < 24; i++) {
		for (j = 0; j < 24; j++) {
			p[i][j] = state[i][j];
		}
	}
	board();
	setlinecolor(BLACK);
	if (play == 0) player = 1;
	else player = -1;
	while (TRUE) {
	
		setbkcolor(BG_COLOR);
		int color;
		if (num % 2 == 0) {
			color = 1;
			setfillcolor(BLACK);
		}
		else {
			color = -1;
			setfillcolor(WHITE);
		}
		fillcircle(925, 125, 40);
		if (color == player || no_robot == 1) {//test
			setrop2(R2_COPYPEN);//R2_COPYPEN 當前顔色
			while (true) {
				m = GetMouseMsg();
				x = m.x % 50;
				y = m.y % 50;
				setbkcolor(BUTTON_COLOR);
				TCHAR s1[] = _T("重來");
				TCHAR s2[] = _T("悔棋");
				TCHAR s3[] = _T("結束遊戲");
				if (m.x <= 1030 && m.x >= 820 && m.y <= 255 && m.y >= 190) {//重來
					settextcolor(LIGHTCYAN);
					outtextxy(885, 200, s1);
					if (m.uMsg == WM_LBUTTONDOWN) {
						initialize(p);
						begin(p, player);
					}
				}
				else {
					settextcolor(WHITE);
					outtextxy(885, 200, s1);
				}
				if (m.x <= 1030 && m.x >= 820 && m.y <= 405 && m.y >= 340) {//悔棋
					settextcolor(LIGHTCYAN);
					outtextxy(885, 350, s2);
					if (m.uMsg == WM_LBUTTONDOWN) {
						if (len > 1 && num > 1) {
							regret(p);
							if (!no_robot) regret(p);//2 times;
							break;
						}
						else {
							setbkcolor(BG_COLOR);
							TCHAR s[] = _T("不可悔棋");
							outtextxy(850, 700, s);
						}
					}
				}
				else {
					settextcolor(WHITE);
					outtextxy(885, 350, s2);
				}
				if (m.x <= 1030 && m.x >= 820 && m.y <= 555 && m.y >= 490) {//結束遊戲
					settextcolor(LIGHTCYAN);
					outtextxy(845, 500, s3);
					if (m.uMsg == WM_LBUTTONDOWN) {
						closegraph();
						exit(0);
					}
				}
				else {
					settextcolor(WHITE);
					outtextxy(845, 500, s3);
				}

				if (x > 25)
					m.x = m.x - x + 50;
				else
					m.x = m.x - x;
				if (y > 25)
					m.y = m.y - y + 50;
				else
					m.y = m.y - y;
				i = m.x / 50 - 1 + MIN;
				j = m.y / 50 - 1 + MIN;

				if (m.uMsg == WM_LBUTTONDOWN) {
					if (i < MAX && j < MAX && i >= MIN && j >= MIN) {
						if (p[i][j].state == 0) {
							execute(p, i, j, color,false);
							walk[len].x = i;
							walk[len].y = j;
							len++;
							record_for_check[clen] = { i,j };
							clen++;
							num++;
							setbkcolor(BG_COLOR);
							clearrectangle(800, 700, 1200, 800);
							break;
						}
					}
				}
			}
		}
		else {//robot
			struct place place;
			//place = robot2(p, -player, f);
			//place = findBestMove(p);
			if (ROBOT_MODE == 1) {
				place = robot3(p, f);
				while (!(place.x < MAX && place.y < MAX && place.x >= MIN && place.y >= MIN && p[place.x][place.y].state == 0)) {
					place = robot3(p, f);
				
				}
			}
			else if (ROBOT_MODE == 2) {
				place = robot2(p,-player, f);
				while (!(place.x < MAX && place.y < MAX && place.x >= MIN && place.y >= MIN && p[place.x][place.y].state == 0)) {
					place = robot2(p, -player, f);
				}
			}
			else if (ROBOT_MODE == 3) {
				place = robot(p);
				while (!(place.x < MAX && place.y < MAX && place.x >= MIN && place.y >= MIN && p[place.x][place.y].state == 0)) {
					place = robot(p);
				}
			}
			
			execute(p, place.x, place.y, color,false);
 			walk[len].x = place.x;
			walk[len].y = place.y;
			len++;
			record_for_check[clen] = { place.x,place.y };
			clen++;
			num++;
		}

		e = end(p);
		if (e != 0) {
			Sleep(500);
			over(e);
			break;
		}
		f = 1;
	}
}

void board() {//draw the board
	setbkcolor(BG_COLOR);
	cleardevice();//use bkcolor to fill graph
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	setbkcolor(BG_COLOR);
	settextstyle(40, 20, _T("Consolas"));
	for (int i = 50; i <= 750; i += 50) {
		line(i, 50, i, 750);
		line(50, i, 750, i);
	}
	for (int i = 200; i <= 600; i += 400) {
		fillcircle(i,600,5);
		fillcircle(i, 200, 5);
	}
	fillcircle(400, 400, 5);
	setfillcolor(BUTTON_COLOR);
	fillrectangle(820, 190, 1030, 255);
	fillrectangle(820, 340, 1030, 405);
	fillrectangle(820, 490, 1030, 555);
	TCHAR s1[] = _T("重來");
	TCHAR s2[] = _T("悔棋");
	TCHAR s3[] = _T("結束遊戲");
	outtextxy(885, 200, s1);
	outtextxy(885, 350, s2);
	outtextxy(845, 500, s3);
}

int end(struct point p[25][25]) {//it will return 0 if nobody win or draw
	int i, j, k = 0, x, y, q, b, e = 0;
	x = y = b = q = -2;
	if (num<9)return 0;
	for (i = MIN; i < MAX; i++) {
		for (j = MIN; j < MAX; j++) {
			if (p[i][j].state == 0) k++;

			else {
				for (x = -2; p[i][j].state == p[i][j + x].state && x < 4; x++) {}
				for (y = -2; p[i][j].state == p[i + y][j].state && y < 4; y++) {}
				for (b = -2; p[i][j].state == p[i + b][j + b].state && b < 4; b++) {}
				for (q = -2; p[i][j].state == p[i - q][j + q].state && q < 4; q++) {}
			}
			if (x == WIN - 2 || y == WIN - 2 || b == WIN - 2 || q == WIN - 2) {
				if (p[i][j].state == 1) e = 1;//black win
				else if (p[i][j].state == -1) e = -1;//white win
			}
		}
	}
	if (k == 0) e = 2;//draw
	return e;
}

void execute(struct point p[25][25], int x, int y, int z, bool is_regect) {//draw the chess(circle) and make the record with the state
	if (z != 0) {
		if (z == 1)
			setfillcolor(BLACK);
		if (z == -1)
			setfillcolor(WHITE);

		fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);
		p[x][y].state = z;
		record_for_state[x][y].state = z;
	}
}

int first() {//set player color
	initgraph(1100, 800);
	setbkcolor(BG_COLOR);
	cleardevice();
	int num;
	MOUSEMSG n;
	setbkcolor(BUTTON_COLOR);
	setfillcolor(BUTTON_COLOR);
	settextcolor(WHITE);
	settextstyle(40, 0, _T("Consolas"));
	fillrectangle(50, 375, 375, 465);
	fillrectangle(475, 375, 675, 465);
	fillrectangle(775, 375, 1000, 465);
	TCHAR s1[] = _T("選擇白子/黑子");
	TCHAR s2[] = _T("雙人模式");
	TCHAR s3[] = _T("隨機");
	outtextxy(90, 400, s1);
	outtextxy(500, 400, s2);
	outtextxy(850, 400, s3);

	while (true) {
		n = GetMouseMsg();
		if (n.x <= 375 && n.x >= 50 && n.y >= 375 && n.y <= 465) {
			settextcolor(LIGHTCYAN);
			outtextxy(90, 400, s1);
			if (n.uMsg == WM_LBUTTONDOWN) {
				setbkcolor(BG_COLOR);
				cleardevice();
				setbkcolor(BUTTON_COLOR);
				fillrectangle(175, 375, 475, 465);
				fillrectangle(575, 375, 875, 465);
				TCHAR s1[] = _T("白子");
				TCHAR s2[] = _T("黑子");
				outtextxy(285, 400, s1);
				outtextxy(685, 400, s2);
				while (true) {
					n = GetMouseMsg();
					if (n.x <= 475 && n.x >= 175 && n.y >= 375 && n.y <= 465) {
						settextcolor(LIGHTCYAN);
						outtextxy(285, 400, s1);
						if (n.uMsg == WM_LBUTTONDOWN) return 1;
					}
					else {
						settextcolor(WHITE);
						outtextxy(285, 400, s1);
					}
					if (n.x <= 875 && n.x >= 575 && n.y >= 375 && n.y <= 465) {
						settextcolor(LIGHTCYAN);
						outtextxy(685, 400, s2);
						if (n.uMsg == WM_LBUTTONDOWN) return 0;
					}
					else {
						settextcolor(WHITE);
						outtextxy(685, 400, s2);
					}
				}
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(90, 400, s1);
		}

		if (n.x <= 675 && n.x >= 475 && n.y >= 375 && n.y <= 465) {
			settextcolor(LIGHTCYAN);
			outtextxy(500, 400, s2);
			if (n.uMsg == WM_LBUTTONDOWN) {
				no_robot = 1;
				return 1;
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(500, 400, s2);
		}

		if (n.x <= 1000 && n.x >= 775 && n.y >= 375 && n.y <= 465) {
			settextcolor(LIGHTCYAN);
			outtextxy(850, 400, s3);
			if (n.uMsg == WM_LBUTTONDOWN) {
				num = random();
				while (true) {
					n = GetMouseMsg();
					TCHAR s1[] = _T("確定");
					TCHAR s2[] = _T("重抽");
					if (n.x >= 175 && n.y >= 590 && n.x <= 300 && n.y <= 650) {//mouse put on left button
						settextcolor(LIGHTCYAN);
						outtextxy(200, 600, s1);
						if (n.uMsg == WM_LBUTTONDOWN) return num;
					}
					else {
						settextcolor(WHITE);
						outtextxy(200, 600, s1);
					}
					if (n.x >= 775 && n.y >= 590 && n.x <= 900 && n.y <= 650) {//mouse put on right button
						settextcolor(LIGHTCYAN);
						outtextxy(800, 600, s2);
						if (n.uMsg == WM_LBUTTONDOWN) {
							setbkcolor(BG_COLOR);
							settextcolor(WHITE);
							num = random();
						}
					}
					else {
						settextcolor(WHITE);
						outtextxy(800, 600, s2);
					}
				}
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(850, 400, s3);
		}
	}
}

void initialize(struct point p[25][25]) {
	int i, j;
	num = 0;
	for (int i = 0; i < 230; i++) walk[i] = { NULL,NULL };
	for (i = 0; i < 25; i++) {
		for (j = 0; j < 25; j++) {
			p[i][j].state =  2;
			p[i][j].has_neighnors = 0;
			p[i][j].a_value = 0;
			p[i][j].d_value = 0;
			p[i][j].val = 0;
			p[i][j].place.x =  i;
			p[i][j].place.y =  j;
		}
	}
	for (i = MIN; i < MAX; i++) {
		for (j = MIN; j < MAX; j++) {
			p[i][j].state = record_for_state[i][j].state = 0;
		}
	}
}

void over(int x) {
	setbkcolor(BG_COLOR);
	setlinecolor(BLACK);
	settextstyle(40, 0, _T("Consolas"));
	settextcolor(BLACK);
	if (x == 1) {
		TCHAR s[] = _T("Black Win!");
		outtextxy(835, 20, s);
	}
	else if (x == -1) {
		TCHAR s[] = _T("White Win!");
		outtextxy(835, 20, s);
	}
	else {
		TCHAR s[] = _T("Draw");
		outtextxy(850, 20, s);
	}
	clearrectangle(800, 175, 1100, 800);
	settextcolor(WHITE);
	setbkcolor(BUTTON_COLOR);
	setfillcolor(BUTTON_COLOR);
	fillrectangle(800, 335, 1065, 400);
	fillrectangle(800, 485, 1065, 550);
	
	TCHAR s1[] = _T("返回遊戲界面");
	TCHAR s2[] = _T("結束遊戲");
	outtextxy(820, 350, s1);
	outtextxy(855, 500, s2);
	while (true)
	{
		MOUSEMSG n;
		n = GetMouseMsg();
		if (n.x <= 1065 && n.x >= 800 && n.y <= 400 && n.y >= 335) {
			settextcolor(LIGHTCYAN);
			outtextxy(820, 350, s1);
			if (n.uMsg == WM_LBUTTONDOWN) {
				start();
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(820, 350, s1);
		}
		if (n.x <= 1065 && n.x >= 800 && n.y <= 550 && n.y >= 485) {
			settextcolor(LIGHTCYAN);
			outtextxy(855, 500, s2);
			if (n.uMsg == WM_LBUTTONDOWN) {
				closegraph();
				exit(0);
			}
		}
		else {
			settextcolor(WHITE);
			outtextxy(855, 500, s2);
		}	
	}
}

int random() {
	int num;
	time_t t;
	srand((unsigned)time(&t));
	num = rand() % 2;
	setbkcolor(BG_COLOR);
	settextcolor(WHITE);
	cleardevice();
	if (num == 0) {
		TCHAR s[] = _T("you are black");
		outtextxy(400, 400, s);
	}
	else if (num == 1) {
		TCHAR s[] = _T("you are white");
		outtextxy(400, 400, s);
	}
	else {
		TCHAR s[] = _T("error");
		outtextxy(400, 400, s);
	}
	setbkcolor(BUTTON_COLOR);
	setfillcolor(BUTTON_COLOR);
	setlinecolor(BUTTON_COLOR);
	TCHAR s1[] = _T("確定");
	TCHAR s2[] = _T("重抽");
	fillrectangle(175, 590, 300, 650);
	fillrectangle(775, 590, 900, 650);
	outtextxy(200, 600, s1);
	outtextxy(800, 600, s2);
	return num;
}

void regret(struct point p[25][25]) {
	p[walk[len - 1].x][walk[len - 1].y].state = 0;
	len--;
	num--;
	board();
	for (int i = MIN; i < MAX; i++) {
		for (int j = MIN; j < MAX; j++) {
			if (p[i][j].state != 0){
				execute(p, i, j, p[i][j].state,true);
			}
		}
	}
}


void start() {
	int number;
	number = first();
	point p[25][25];
	initialize(p);
	begin(p, number);
	_getch();
	closegraph();
}
