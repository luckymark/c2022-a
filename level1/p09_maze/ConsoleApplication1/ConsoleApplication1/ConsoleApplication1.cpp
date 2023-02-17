#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <direct.h>
#include <string.h>

#define offsetx 20 
#define offsety 20 
#define map_width 15
#define map_height 15
#define piece_size 30

IMAGE backImg;
MOUSEMSG msg = { 0 };
int map[map_height][map_width];
int flag[2][4];//第一维标记-四个方向能连几个棋子，第二维标记是否活子，2表示活2子，1表示活1子，0表示死子
int currentPiece;
int changePiece;
int AIx, AIy;

void initView();
void initGame();
void playerVSAI();
void playerVSplayer();
bool pieceSet(int y, int x, int color);
void judge(int y, int x, int color);
void drawPiece(int x, int y, int color);
void AI();
void InitPage();
void ModelShow(); //模式显示
void main(void)
{
	char control[3];
	InitPage();
	while (1)
	{
		ModelShow();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (msg.x >= 255 && msg.x < 520 && msg.y >= 180 && msg.y <= 230)
			{
				playerVSAI();
				InitPage();
				break;
			}
			if (msg.x >= 255 && msg.x < 520 && msg.y >= 250 && msg.y <= 300)
			{
				playerVSplayer();
				InitPage();
				break;
			}
		}
	}
}

void ModelShow()
{
	msg = GetMouseMsg();

	if (msg.x >= 255 && msg.x < 520 && msg.y >= 180 && msg.y <= 230)
	{
		settextcolor(RGB(255, 0, 0));
		outtextxy(250, 180, L"人机对战!");
	}
	else if (msg.x >= 255 && msg.x < 520 && msg.y >= 250 && msg.y <= 300)
	{
		settextcolor(RGB(255, 0, 0));
		outtextxy(250, 250, L"人人对战!");
	}
	else
	{
		settextcolor(RGB(137, 57, 196));
		outtextxy(250, 180, L"人机对战!");
		outtextxy(250, 250, L"人人对战!");
	}
}

void InitPage()
{
	initgraph(520, 520);
	loadimage(&backImg, L"3.jpg", 520, 520);
	putimage(0, 0, &backImg);

	setbkmode(TRANSPARENT);
	settextstyle(55, 0, L"楷体");
}

void AI()
{
	int oldScore = 0, newScore = 0;
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			if (map[i][j] != 0) {
				continue;
			}
			judge(j, i, 1);//先判断白子（AI）
			for (int z = 0; z < 4; z++) {
				if (flag[0][z] == 5) {
					newScore += 1000;
				}
				else if (flag[0][z] == 4) {
					newScore += 100 * flag[1][z];
				}
				else if (flag[0][z] == 3) {
					newScore += 10 * flag[1][z];
				}
				else if (flag[0][z] == 2) {
					newScore += 1 * flag[1][z];
				}
			}
			if (newScore > oldScore) {
				oldScore = newScore;
				AIx = j; AIy = i;
			}
			newScore = 0;
			judge(j, i, 2);
			for (int z = 0; z < 4; z++) {
				if (flag[0][z] == 5) {
					newScore += 1000;
				}
				else if (flag[0][z] == 4) {
					newScore += 100 * flag[1][z];
				}
				else if (flag[0][z] == 3) {
					newScore += 10 * flag[1][z];
				}
				else if (flag[0][z] == 2) {
					newScore += 1 * flag[1][z];
				}
			}
			if (newScore > oldScore) {
				oldScore = newScore;
				AIx = j; AIy = i;
			}
		}
	}
}
void drawPiece(int x, int y, int color) {
	if (color == 1) {
		setfillcolor(WHITE);
	}
	else if (color == 2) {
		setfillcolor(BLACK);
	}
	solidcircle(x * piece_size + offsetx, y * piece_size + offsety, piece_size / 2);
}

void initGame() {
	currentPiece = 2;
	changePiece = -1;

	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			map[i][j] = 0;
		}
	}
}

void initView() {
	initgraph((map_width - 1) * piece_size + offsetx * 2, (map_height - 1) * piece_size + offsety * 2);
	loadimage(NULL, _T("2.jpg"), map_width * piece_size + offsetx * 2, map_height * piece_size + offsety * 2);

	setlinecolor(BLACK);
	for (int i = 0; i < map_width; i++) {
		line(i * piece_size + offsetx, offsety, i * piece_size + offsetx, offsety + (map_height - 1) * piece_size);
	}
	for (int i = 0; i < map_height; i++) {
		line(offsetx, offsety + i * piece_size, (map_width - 1) * piece_size + offsetx, offsety + i * piece_size);
	}
}

void playerVSAI()
{
	initGame();
	initView();

	MOUSEMSG m;
	int x, y;

	while (1) {
		m = GetMouseMsg();
		if (m.mkLButton)
		{
			x = (m.x - offsetx + piece_size / 2) / piece_size;
			y = (m.y - offsety + piece_size / 2) / piece_size;
			if (pieceSet(x, y, currentPiece))
			{
				drawPiece(x, y, currentPiece);
				judge(x, y, currentPiece);
				if (flag[0][0] >= 5 || flag[0][1] >= 5 || flag[0][2] >= 5 || flag[0][3] >= 5) //分出胜负则退出
				{
					if (currentPiece == 2)
					{
						MessageBox(GetHWnd(), L"黑子胜出！", L"游戏结束：", MB_OKCANCEL);
					}
					else
					{
						MessageBox(GetHWnd(), L"白子胜出！", L"游戏结束：", MB_OKCANCEL);
					}
					break;
				}
				//改变棋子颜色
				currentPiece += changePiece;
				changePiece *= -1;
				//AI行动
				AI();
				Sleep(1000);
				pieceSet(AIx, AIy, 1);
				drawPiece(AIx, AIy, currentPiece);
				judge(AIx, AIy, currentPiece);
				if (flag[0][0] >= 5 || flag[0][1] >= 5 || flag[0][2] >= 5 || flag[0][3] >= 5) {
					if (currentPiece == 2) {
						MessageBox(GetHWnd(), L"黑子胜出！", L"游戏结束：", MB_OKCANCEL);
					}
					else {
						MessageBox(GetHWnd(), L"白子胜出！", L"游戏结束：", MB_OKCANCEL);
					}
					break;
				}

				currentPiece += changePiece;
				changePiece *= -1;
			}
		}
	}
	closegraph();
}

void judge(int y, int x, int color) //判断当前位置4个方向连接的棋子数量，参数为棋子颜色 1白2黑
{
	bool flag1 = false, flag2 = false; //标记方向两头是不是有相反颜色的棋子
	int count = 0;//连接棋子数量
	int addx = 0, addy = -1;//增量
	int posx = x, posy = y;//增加后的x,y
	// - 向
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posy < 0)//如果越界
		{
			flag1 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag1 = true;
			break;
		}
		count++;
	}
	addy = 1;
	posx = x;
	posy = y;
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posy >= map_width)//如果越界
		{
			flag2 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag2 = true;
			break;
		}
		count++;
	}
	flag[1][0] = 2;
	if (flag1)
	{
		flag[1][0]--;
	}
	if (flag2)
	{
		flag[1][0]--;
	}

	flag[0][0] = count + 1;
	count = 0;
	// | 向
	flag1 = false;
	flag2 = false;
	posx = x;
	posy = y;
	addx = -1;
	addy = 0;
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posx < 0) //如果越界
		{
			flag1 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag1 = true;
			break;
		}
		count++;
	}
	addx = 1;
	posx = x;
	posy = y;
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posx >= map_height) //如果越界
		{
			flag2 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag2 = true;
			break;
		}
		count++;
	}
	flag[1][1] = 2;
	if (flag1)
	{
		flag[1][1]--;
	}
	if (flag2)
	{
		flag[1][1]--;
	}
	flag[0][1] = count + 1;
	count = 0;
	// / 向
	flag1 = false;
	flag2 = false;
	posx = x;
	posy = y;
	addx = -1;
	addy = 1;
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posx < 0 || posy >= map_width) //如果越界
		{
			flag1 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag1 = true;
			break;
		}
		count++;
	}
	addx = 1;
	addy = -1;
	posx = x;
	posy = y;
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posx >= map_height || posy < 0) //如果越界
		{
			flag2 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag2 = true;
			break;
		}
		count++;
	}
	flag[1][2] = 2;
	if (flag1)
	{
		flag[1][2]--;
	}
	if (flag2)
	{
		flag[1][2]--;
	}
	flag[0][2] = count + 1;
	count = 0;
	// \ 向
	flag1 = false;
	flag2 = false;
	posx = x;
	posy = y;
	addx = -1;
	addy = -1;
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posy < 0 || posx < 0) //如果越界
		{
			flag1 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag1 = true;
			break;
		}
		count++;
	}
	addx = 1;
	addy = 1;
	posx = x;
	posy = y;
	while (1)
	{
		posx += addx;
		posy += addy;
		if (posx >= map_height || posy >= map_width) //如果越界
		{
			flag2 = true;
			break;
		}
		if (map[posx][posy] == 0) //如果没有棋子
		{
			break;
		}
		if (map[posx][posy] != color) //如果为对方棋子
		{
			flag2 = true;
			break;
		}
		count++;
	}
	flag[1][3] = 2;
	if (flag1)
	{
		flag[1][3]--;
	}
	if (flag2)
	{
		flag[1][3]--;
	}
	flag[0][3] = count + 1;
	count = 0;
}

bool pieceSet(int y, int x, int color) //放置棋子，返回true表示放置成功，false 表示放置失败
{
	if (map[x][y] != 0)//当前位置有棋子
	{
		return false;
	}
	map[x][y] = color;
	return true;
}

void playerVSplayer() //人人对战
{
	initGame();
	initView();
	MOUSEMSG m;
	int x, y;
	while (1) {//game looping
		m = GetMouseMsg();
		//左键点击放置棋子
		if (m.mkLButton) {
			x = (m.x - offsetx + piece_size / 2) / piece_size;
			y = (m.y - offsety + piece_size / 2) / piece_size;
			if (pieceSet(x, y, currentPiece)) {
				drawPiece(x, y, currentPiece);
				judge(x, y, currentPiece);
				if (flag[0][0] >= 5 || flag[0][1] >= 5 || flag[0][2] >= 5 || flag[0][3] >= 5) {//分出胜负则退出
					if (currentPiece == 2)
						MessageBox(GetHWnd(), L"黑子胜出！", L"游戏结束：", MB_OKCANCEL);
					else
						MessageBox(GetHWnd(), L"白子胜出！", L"游戏结束：", MB_OKCANCEL);
					break;
				}
				//改变棋子颜色
				currentPiece += changePiece;
				changePiece *= -1;
			}
		}
	}
	closegraph();
}