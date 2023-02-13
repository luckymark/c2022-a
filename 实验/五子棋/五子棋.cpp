#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#define width 600  //窗口宽度
#define length 500  //窗口长度
#define row 15     //棋局的宽数
#define col 15     //棋局的列数
#define grid 25    //格子的大小
#define space 3*grid    //棋局离左上边框的距离
int cnt = 0;   //记录电脑落子数目
int map[row][col];   //一个棋局上的所有点

int judgeResult();    //判断是否结束
int judgeBlackScore(int BlackNum, int EmptyNum);  //判断黑棋的得分
int judgeWhiteScore(int WhiteNum, int EmptyNum);  //判断白棋的得分
int judgeAll_BlackScore(int i, int j);  //判断i，j点黑棋的总分
int judgeAll_WhiteScore(int i, int j);  //判断i，j点白棋的总分

void loadbk();  //加载背景
void draw();  //绘制图片

void AI_EasyPlay();  //简单AI下子
void AI_MiddlePlay();
void AI_DifficultPlay();

void EasyMan_AI();
void MiddleMan_AI();
void DifficultMan_AI();

void mouseMoveMsg(ExMessage* msg);  //鼠标移动
void Man_MousePressMsg(ExMessage* msg);  //人人模式下的鼠标点击
void AI_MousePressMsg(ExMessage* msg);  //人机模式下的鼠标点击

void chooseGame();
void choose_RenjuMode();
int choose_RenjuDifficulty();

void Man_Man();

typedef struct {
	int msg_x;
	int msg_y;
	int player;
}pos;
pos position;
typedef struct {
	int ScoreMax[row][col];
	int ScoreMin[row][col];
	int ScoreMax_x;
	int ScoreMax_y;
	int ScoreMin_x;
	int ScoreMin_y;
	int value;
	int alpha;
	int beta;
	int NowValue[row][col];
}Score;
enum playmessage
{
	none,
	black,
	white,
};
ExMessage msg;
Score MinMax(int depth, int alpha, int beta);
Score Max(int depth, int alpha, int beta);
Score Min(int depth, int alpha, int beta);
Score evaluate();

int MAX(int a, int b)
{
	int ret;
	if (a >= b)
		ret = a;
	else
		ret = b;
	return ret;
}
int MIN(int a, int b)
{
	int ret;
	if (a <= b)
		ret = a;
	else
		ret = b;
	return ret;
}

int main()
{
	srand(time(NULL));
	//创建窗口
	initgraph(width, length);
	position.player = black;
	BeginBatchDraw();
	chooseGame();
	EndBatchDraw();
	_getch();
	return 0;
}

void loadbk()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE bk; //背景变量
	loadimage(&bk, L"renju/shagou.png");//加载背景
	putimage(0, 0, &bk);//输出背景
	draw();
	EndBatchDraw();
}
void draw()
{

	for (int i = 0; i < row; i++)
	{

		//画横线
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(space, space + i * grid, space + (row - 1) * grid, space + i * grid);
	}
	for (int i = 0; i < col; i++)
	{

		//画竖线
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(space + i * grid, space, space + i * grid, space + grid * (col - 1));
	}

	//画粗点
	setfillcolor(BLACK);
	fillcircle(space + (7 - 4) * grid, space + (7 - 4) * grid, 5);
	fillcircle(space + (7 + 4) * grid, space + (7 - 4) * grid, 5);
	fillcircle(space + (7 - 4) * grid, space + (7 + 4) * grid, 5);
	fillcircle(space + (7 + 4) * grid, space + (7 + 4) * grid, 5);
	fillcircle(space + (7) * grid, space + (7) * grid, 5);

	//画粗边框
	setlinestyle(PS_SOLID, 3);
	rectangle(space, space, space + (row - 1) * grid, space + (col - 1) * grid);

	//画棋子(棋子的坐标)
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (map[i][j] == black)
			{
				setfillcolor(BLACK);
				fillcircle(space + i * grid, space + j * grid, 8);
			}
			else if (map[i][j] == white)
			{
				setfillcolor(WHITE);
				fillcircle(space + i * grid, space + j * grid, 8);
			}

	//棋子蓝色边框
	if ((position.msg_x < 15 && position.msg_x >= 0) && (position.msg_y < 15 && 0 <= position.msg_y))
	{
		if (map[position.msg_x][position.msg_y] == none)//只会在没有棋子的地方显示
		{
			setlinecolor(BLUE);
			rectangle((position.msg_x + 3) * grid - 12, (position.msg_y + 3) * grid - 12, (position.msg_x + 3) * grid + 12, (position.msg_y + 3) * grid + 12);
		}
	}
}

void mouseMoveMsg(ExMessage* msg)
{
	//蓝色鼠标移动框的下标
	position.msg_x = floor((1.0 * msg->x / grid) + 0.5) - 3;//下标x
	position.msg_y = floor((1.0 * msg->y / grid) + 0.5) - 3;//下标y
//	position.isShow = 1;

}
void AI_MousePressMsg(ExMessage* msg)
{

	position.msg_x = floor(1.0 * msg->x / grid + 0.5) - 3;//下标x
	position.msg_y = floor(1.0 * msg->y / grid + 0.5) - 3;//下标y
	if (map[position.msg_x][position.msg_y] == none && position.msg_x < row && 0 <= position.msg_x && position.msg_y < col && 0 <= position.msg_y)
	{
		map[position.msg_x][position.msg_y] = position.player;//下子
		position.player = white;//切换棋手
	}
	else if (map[position.msg_x][position.msg_y] == none && position.msg_x < row && 0 <= position.msg_x && position.msg_y < col && 0 <= position.msg_y)
	{
		map[position.msg_x][position.msg_y] = position.player;//下子
		position.player = black;//切换棋手
	}
}//目前是人机情况下的鼠标点击
void Man_MousePressMsg(ExMessage* msg)
{
	position.msg_x = floor(1.0 * msg->x / grid + 0.5) - 3;//下标x
	position.msg_y = floor(1.0 * msg->y / grid + 0.5) - 3;//下标y
	if (map[position.msg_x][position.msg_y] == none && position.msg_x < row && 0 <= position.msg_x && position.msg_y < col && 0 <= position.msg_y)
	{
		map[position.msg_x][position.msg_y] = position.player;//下子
		position.player = (position.player == black ? white : black);//切换棋手
	}
}//目前是人人情况下的鼠标点击

//AI下子
void AI_EasyPlay()
{
	int ScoreMax = -100000;
	int depth = 0;
	Score play = MinMax(depth, -100000, 100000);
	if (position.player == white)
	{
		map[play.ScoreMax_x][play.ScoreMax_y] = white;
		position.player = black;
		cnt++;
	}
}
void AI_MiddlePlay()
{
	int ScoreMax = -100000;
	int depth;
	if (cnt < 5)
		depth = 0;
	else if (5 <= cnt)
		depth = 2;

	Score play = MinMax(depth, -100000, 100000);
	int NowScore[row][col] = { 0 };
	if (cnt >= 5)
	{
		int jd = 0;
		for (int i = 0; i < row; i++)
		{
			if (jd == 1)
				break;
			for (int j = 0; j < col; j++)
			{
				if (map[i][j] == none)
				{
					if (judgeAll_WhiteScore(i, j) < 10000)
					{
						NowScore[i][j] = fabs(play.NowValue[i][j] - judgeAll_BlackScore(i, j));
						if (NowScore[i][j] >= ScoreMax)
						{
							ScoreMax = NowScore[i][j];
							play.ScoreMax_x = i;
							play.ScoreMax_y = j;
						}
					}
					else
					{
						ScoreMax = judgeAll_WhiteScore(i, j);
						play.ScoreMax_x = i;
						play.ScoreMax_y = j;
						jd = 1;
						break;
					}
				}
			}
		}
	}
	if (position.player == white)
	{
		map[play.ScoreMax_x][play.ScoreMax_y] = white;
		position.player = black;
		cnt++;
	}
}
void AI_DifficultPlay()
{
	int ScoreMax = -100000;
	int depth;
	if (cnt < 5)
		depth = 0;
	else if (5 <= cnt && cnt < 10)
		depth = 2;
	else if (10 < cnt)
		depth = 4;
	Score play = MinMax(depth, -100000, 100000);
	int NowScore[row][col] = { 0 };
	if (cnt >= 5)
	{
		int jd = 0;
		for (int i = 0; i < row; i++)
		{
			if (jd == 1)
				break;
			for (int j = 0; j < col; j++)
			{
				if (map[i][j] == none)
				{
					if (judgeAll_WhiteScore(i, j) < 10000)
					{
						NowScore[i][j] = fabs(play.NowValue[i][j] - judgeAll_BlackScore(i, j));
						if (NowScore[i][j] >= ScoreMax)
						{
							ScoreMax = NowScore[i][j];
							play.ScoreMax_x = i;
							play.ScoreMax_y = j;
						}
					}
					else
					{
						ScoreMax = judgeAll_WhiteScore(i, j);
						play.ScoreMax_x = i;
						play.ScoreMax_y = j;
						jd = 1;
						break;
					}
				}
			}
		}
	}
	if (position.player == white)
	{
		map[play.ScoreMax_x][play.ScoreMax_y] = white;
		position.player = black;
		cnt++;
	}
}
//对战
void Man_Man()
{
	position.player = black;
	while (1)
	{
		loadbk();
		//处理消息
		if (peekmessage(&msg, EM_MOUSE))
			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				mouseMoveMsg(&msg);
				break;
			case WM_LBUTTONDOWN:
				Man_MousePressMsg(&msg);
				break;
			}
		loadbk();
		int ret = judgeResult();
		if (ret == 1)
		{
			printf("黑棋获胜");
			settextstyle(50, 0, L"正楷");
			outtextxy(width / 2, length / 2, L"黑棋胜");
			break;
		}
		else if (ret == 2)
		{
			printf("白棋获胜");
			settextstyle(50, 0, L"正楷");
			outtextxy(width / 2, length / 2, L"白棋胜");
			break;
		}
		else if (ret == 3)
		{
			printf("平局");
			settextstyle(50, 0, L"正楷");
			outtextxy(width / 2, length / 2, L"和棋");
			break;
		}
	}
}
void EasyMan_AI()
{
	while (1)
	{
		loadbk();
		//处理消息
		if (position.player == black)
		{
			if (peekmessage(&msg, EM_MOUSE))
				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					mouseMoveMsg(&msg);
					break;
				case WM_LBUTTONDOWN:
					AI_MousePressMsg(&msg);
					break;
				}
		}
		else if (position.player == white)
		{
			AI_EasyPlay();
		}
		loadbk();
		int ret = judgeResult();
		if (ret == 1)
		{
			printf("黑棋胜");
			settextstyle(50, 0, L"正楷");
			outtextxy(width / 2, length / 2, L"黑棋胜");
			break;
		}
		else if (ret == 2)
		{
			printf("白棋胜");
			settextstyle(50, 0, L"正楷");
			outtextxy(3 * width / 4, length / 2, L"白棋胜");
			break;
		}
		else if (ret == 3)
		{
			printf("平局");
			settextstyle(50, 0, L"正楷");
			outtextxy(width / 2, length / 2, L"和棋");
			break;
		}
	}
	return;
}
void MiddleMan_AI()
{
	{
		while (1)
		{
			loadbk();
			//处理消息
			if (position.player == black)
			{
				if (peekmessage(&msg, EM_MOUSE))
					switch (msg.message)
					{
					case WM_MOUSEMOVE:
						mouseMoveMsg(&msg);
						break;
					case WM_LBUTTONDOWN:
						AI_MousePressMsg(&msg);
						break;
					}
			}
			else if (position.player == white)
			{
				AI_MiddlePlay();
			}
			loadbk();
			int ret = judgeResult();
			if (ret == 1)
			{
				printf("黑棋胜");
				settextstyle(50, 0, L"正楷");
				outtextxy(width / 2, length / 2, L"黑棋胜");
				break;
			}
			else if (ret == 2)
			{
				printf("白棋胜");
				settextstyle(50, 0, L"正楷");
				outtextxy(width / 2, length / 2, L"白棋胜");
				break;
			}
			else if (ret == 3)
			{
				printf("平局");
				settextstyle(50, 0, L"正楷");
				outtextxy(width / 2, length / 2, L"和棋");
				break;
			}
		}
		return;
	}
}
void DifficultMan_AI()
{
	{
		while (1)
		{
			loadbk();
			//处理消息
			if (position.player == black)
			{
				if (peekmessage(&msg, EM_MOUSE))
					switch (msg.message)
					{
					case WM_MOUSEMOVE:
						mouseMoveMsg(&msg);
						break;
					case WM_LBUTTONDOWN:
						AI_MousePressMsg(&msg);
						break;
					}
			}
			else if (position.player == white)
			{
				AI_DifficultPlay();
			}
			loadbk();
			int ret = judgeResult();
			if (ret == 1)
			{
				printf("黑棋胜");
				settextstyle(50, 0, L"正楷");
				outtextxy(width / 2, length / 2, L"黑棋胜");
				break;
			}
			else if (ret == 2)
			{
				printf("白棋胜");
				settextstyle(50, 0, L"正楷");
				outtextxy(width / 2, length / 2, L"白棋胜");
				break;
			}
			else if (ret == 3)
			{
				printf("平局");
				settextstyle(50, 0, L"正楷");
				outtextxy(width / 2, length / 2, L"和棋");
				break;
			}
		}
		return;
	}
}

void chooseGame()
{
	int msg_x = 0, msg_y = 0;
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		IMAGE bk;
		loadimage(&bk, L"renju/选择游戏.jpg");//加载背景
		putimage(0, 0, &bk);//输出背景 

		if (msg_x > 42 && msg_x < 224 && msg_y < 186 && msg_y>108)//选择五子棋
		{
			setlinestyle(PS_SOLID, 3);
			rectangle(42, 108, 224, 186);
		}

		if (peekmessage(&msg))
		{
			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				msg_x = msg.x;
				msg_y = msg.y;
				break;
			case WM_LBUTTONDOWN:
				if (msg.x > 42 && msg.x < 224 && msg.y < 186 && msg.y>108)
					choose_RenjuMode();//跳入选择五子棋游戏模式界面
				return;
			}
		}
		FlushBatchDraw();
	}
}
void choose_RenjuMode()
{
	int msg_x = 0, msg_y = 0;
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		IMAGE bk;
		loadimage(&bk, L"renju/五子棋模式选择.jpg");//加载背景
		putimage(0, 0, &bk);//输出背景 

		if (msg_x > 167 && msg_x < 424 && msg_y < 192 && msg_y>125)//人人对战
		{
			setlinestyle(PS_SOLID, 3);
			rectangle(167, 125, 424, 192);
		}
		else if (msg_x > 167 && msg_x < 424 && msg_y < 284 && msg_y>223)//人机对战
		{
			setlinestyle(PS_SOLID, 3);
			rectangle(167, 223, 424, 284);
		}

		if (peekmessage(&msg))
		{
			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				msg_x = msg.x;
				msg_y = msg.y;
				break;
			case WM_LBUTTONDOWN:  //选择某个状态
				if (msg_x > 167 && msg_x < 424 && msg_y < 192 && msg_y>125) //选择人人对战
				{
					Man_Man();
					return;
				}
				else if (msg_x > 167 && msg_x < 424 && msg_y < 284 && msg_y>223)//选择人机对战
				{
					if (choose_RenjuDifficulty() == 1)//1代表简单
					{
						EasyMan_AI();
						return;
					}
					else if (choose_RenjuDifficulty() == 2)//2代表中等
					{
						MiddleMan_AI();
						return;
					}
					else if (choose_RenjuDifficulty() == 3)//3代表困难
					{
						DifficultMan_AI();
						return;
					}
				}
			}
		}
		FlushBatchDraw();
	}
}
int choose_RenjuDifficulty()
{
	int msg_x = 0, msg_y = 0;
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		IMAGE bk;
		loadimage(&bk, L"renju/五子棋难度选择.jpg");//加载背景
		putimage(0, 0, &bk);//输出背景 

		if (msg_x > 211 && msg_x < 385 && msg_y> 126 && msg_y < 206)//选择简单
		{
			setlinestyle(PS_SOLID, 3);
			rectangle(211, 126, 385, 206);
		}

		if (msg_x > 211 && msg_x < 385 && msg_y> 217 && msg_y < 296)//选择中等
		{
			setlinestyle(PS_SOLID, 3);
			rectangle(211, 217, 385, 296);
		}

		if (msg_x > 211 && msg_x < 385 && msg_y> 323 && msg_y < 400)//选择噩梦
		{
			setlinestyle(PS_SOLID, 3);
			rectangle(211, 323, 385, 400);
		}

		if (peekmessage(&msg))
		{
			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				msg_x = msg.x;
				msg_y = msg.y;
				break;
			case WM_LBUTTONDOWN:
				if (msg_x > 211 && msg_x < 385 && msg_y> 126 && msg_y < 206)//简单选择
				{
					return 1;
				}
				else if (msg_x > 211 && msg_x < 385 && msg_y> 217 && msg_y < 296)//中等选择
				{

					return 2;
				}
				else if (msg_x > 211 && msg_x < 385 && msg_y> 323 && msg_y < 400)//噩梦选择
				{

					return 3;
				}
			}
		}
		FlushBatchDraw();
	}
}

int judgeBlackScore(int BlackNum, int EmptyNum)
{
	int score = 0;
	if (BlackNum == 0)
		score += 0;

	else if (BlackNum == 1 && EmptyNum == 1)
		score += 15;
	else if (BlackNum == 1 && EmptyNum == 0)
		score += 8;

	else if (BlackNum == 2 && EmptyNum == 1)
		score += 40;
	else if (BlackNum == 2 && EmptyNum == 0)
		score += 30;

	else if (BlackNum == 3 && EmptyNum == 1)
		score += 200;
	else if (BlackNum == 3 && EmptyNum == 0)
		score += 60;
	else
		score += 20000;
	return score;
}
int judgeWhiteScore(int WhiteNum, int EmptyNum)
{

	int score = 0;
	if (WhiteNum == 0)
		score += 0;

	else if (WhiteNum == 1 && EmptyNum == 1)
		score += 20;
	else if (WhiteNum == 1 && EmptyNum == 0)
		score += 10;

	else if (WhiteNum == 2 && EmptyNum == 1)
		score += 50;
	else if (WhiteNum == 2 && EmptyNum == 0)
		score += 25;

	else if (WhiteNum == 3 && EmptyNum == 1)
		score += 300;
	else if (WhiteNum == 3 && EmptyNum == 0)
		score += 55;
	else
		score += 30000;
	return score;
}
int judgeAll_BlackScore(int i, int j)
{
	int BlackNum = 0, EmptyNum = 0, score = 0;
	//判断横向
	for (int x = 1; x <= 4; x++)
	{

		if (map[i + x][j] == black && i + x < row)
			BlackNum += 1;
		else if (map[i + x][j] == none && i + x < row)
		{
			EmptyNum++;
			break;
		}
		else if (map[i + x][j] == white || i + x >= row)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;

	for (int x = 1; x <= 4; x++)
	{
		if (map[i - x][j] == black && 0 <= i - x)
			BlackNum += 1;
		else if (map[i - x][j] == none && 0 <= i - x)
		{
			EmptyNum++;
			break;
		}
		else if (map[i - x][j] == white || i - x < 0)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;
	//判断竖向
	for (int y = 1; y <= 4; y++)
	{
		if (map[i][j + y] == black && i + y < col)
			BlackNum += 1;
		else if (map[i][j + y] == none && i + y < col)
		{
			EmptyNum++;
			break;
		}
		else if (map[i][j + y] == white || i + y >= col)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;

	for (int y = 1; y <= 4; y++)
	{
		if (map[i][j - y] == black && 0 <= i - y)
			BlackNum += 1;
		else if (map[i][j - y] == none && 0 <= i - y)
		{
			EmptyNum++;
			break;
		}
		else if (map[i][j - y] == white || i - y < 0)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;

	//判断右上
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i + x][j - y] == black && 0 <= j - y && i + x < row)
			BlackNum += 1;
		else if (map[i + x][j - y] == none && 0 <= j - y && i + x < row)
		{
			EmptyNum++;
			break;
		}
		else if (map[i + x][j - y] == white || j - y < 0 || i + x >= row)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;

	//判断左下
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i - x][j + y] == black && j + y < col && 0 <= i - x)
			BlackNum += 1;
		else if (map[i - x][j + y] == none && j + y < col && 0 <= i - x)
		{
			EmptyNum++;
			break;
		}
		else if (map[i - x][j + y] == white || j + y >= col || i - x < 0)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;

	//判断右下
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i + x][j + y] == black && j + y < col && i + x < row)
			BlackNum += 1;
		else if (map[i + x][j + y] == none && j + y < col && i + x < row)
		{
			EmptyNum++;
			break;
		}
		else if (map[i + x][j + y] == white || j + y >= col || i + x >= row)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;

	//判断左上
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i - x][j - y] == black && 0 <= j - y && 0 <= i - x)
			BlackNum += 1;
		else if (map[i - x][j - y] == none && 0 <= j - y && 0 <= i - x)
		{
			EmptyNum++;
			break;
		}
		else if (map[i - x][j - y] == white || j - y < 0 || i - x < 0)
			break;
	}
	score += judgeBlackScore(BlackNum, EmptyNum);
	BlackNum = 0, EmptyNum = 0;

	return score;
}
int judgeAll_WhiteScore(int i, int j)
{
	int WhiteNum = 0, EmptyNum = 0, score = 0;

	//判断横向
	for (int x = 1; x <= 4; x++)
	{

		if (map[i + x][j] == white && i + x < row)
			WhiteNum += 1;
		else if (map[i + x][j] == none && i + x < row)
		{
			EmptyNum++;
			break;
		}
		else if (map[i + x][j] == black || i + x >= row)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	for (int x = 1; x <= 4; x++)
	{
		if (map[i - x][j] == white && 0 <= i - x)
			WhiteNum += 1;
		else if (map[i - x][j] == none && 0 <= i - x)
		{
			EmptyNum++;
			break;
		}
		else if (map[i - x][j] == black || i - x < 0)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	//判断竖向
	for (int y = 1; y <= 4; y++)
	{
		if (map[i][j + y] == white && i + y < col)
			WhiteNum += 1;
		else if (map[i][j + y] == none && i + y < col)
		{
			EmptyNum++;
			break;
		}
		else if (map[i][j + y] == black || i + y >= col)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	for (int y = 1; y <= 4; y++)
	{
		if (map[i][j - y] == white && 0 <= i - y)
			WhiteNum += 1;
		else if (map[i][j - y] == none && 0 <= i - y)
		{
			EmptyNum++;
			break;
		}
		else if (map[i][j - y] == black || i - y < 0)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	//判断右上
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i + x][j - y] == white && 0 <= j - y && i + x < row)
			WhiteNum += 1;
		else if (map[i + x][j - y] == none && 0 <= j - y && i + x < row)
		{
			EmptyNum++;
			break;
		}
		else if (map[i + x][j - y] == black || j - y < 0 || i + x >= row)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	//判断左下
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i - x][j + y] == white && j + y < col && 0 <= i - x)
			WhiteNum += 1;
		else if (map[i - x][j + y] == none && j + y < col && 0 <= i - x)
		{
			EmptyNum++;
			break;
		}
		else if (map[i - x][j + y] == black || j + y >= col || i - x < 0)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	//判断右下
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i + x][j + y] == white && j + y < col && i + x < row)
			WhiteNum += 1;
		else if (map[i + x][j + y] == none && j + y < col && i + x < row)
		{
			EmptyNum++;
			break;
		}
		else if (map[i + x][j + y] == black || j + y >= col || i + x >= row)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	//判断左上
	for (int x = 1, y = 1; x <= 4 && y <= 4; x++, y++)
	{
		if (map[i - x][j - y] == white && 0 <= j - y && 0 <= i - x)
			WhiteNum += 1;
		else if (map[i - x][j - y] == none && 0 <= j - y && 0 <= i - x)
		{
			EmptyNum++;
			break;
		}
		else if (map[i - x][j - y] == black || j - y < 0 || i - x < 0)
			break;
	}
	score += judgeWhiteScore(WhiteNum, EmptyNum);
	WhiteNum = 0, EmptyNum = 0;

	return score;
}
int judgeResult()
{
	int ret;
	for (int i = 0; i <= row; i++)
		for (int j = 0; j <= col; j++)
		{
			ret = 0;
			if (map[i][j] == none)
			{
				ret = 1;
				continue;
			}
			else if (map[i][j] == map[i + 1][j] && map[i][j] == map[i + 2][j] && map[i][j] == map[i + 3][j] && map[i][j] == map[i + 4][j] ||//判断横向
				map[i][j] == map[i][j + 1] && map[i][j] == map[i][j + 2] && map[i][j] == map[i][j + 3] && map[i][j] == map[i][j + 4] || //判断纵向
				map[i][j] == map[i + 1][j - 1] && map[i][j] == map[i + 2][j - 2] && map[i][j] == map[i + 3][j - 3] && map[i][j] == map[i + 4][j - 4] ||//判断右上斜线
				map[i][j] == map[i + 1][j + 1] && map[i][j] == map[i + 2][j + 2] && map[i][j] == map[i + 3][j + 3] && map[i][j] == map[i + 4][j + 4])  //判断右下斜线
			{

				if (map[i][j] == black)
				{
					return 1;
				}
				else if (map[i][j] == white)
				{
					return 2;
				}
			}
		}
	//判断是否和棋
	if (ret == 0)
	{
		return 3;

	}
	else
		return 0;
}

Score evaluate()
{
	int BlackScore[row][col] = { 0 };
	int WhiteScore[row][col] = { 0 };
	Score ScoreMax;
	ScoreMax.value = -100000000;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (map[i][j] == none)  //如果该位置没有棋子
			{
				BlackScore[i][j] = judgeAll_BlackScore(i, j);
				WhiteScore[i][j] = judgeAll_WhiteScore(i, j);
				int count;
				if (cnt < 5)
					count = fabs(WhiteScore[i][j] - BlackScore[i][j]);
				else
					count = WhiteScore[i][j];
				if (count >= ScoreMax.value)
				{
					ScoreMax.value = count;
					ScoreMax.ScoreMax_x = i;
					ScoreMax.ScoreMax_y = j;
				}
			}
		}
	return ScoreMax;
}
Score MinMax(int depth, int alpha, int beta)
{
	if (position.player == white)
		return Max(depth, alpha, beta);
	else
		return Min(depth, alpha, beta);
}
Score Max(int depth, int alpha, int beta)
{
	Score val;
	val.value = -100000;
	val.alpha = alpha;
	val.beta = beta;
	if (depth <= 0 || judgeResult())
	{
		return evaluate();
	}
	else
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				if (map[i][j] == none)  //如果该位置没有棋子
				{
					map[i][j] = white;
					Score num = Min(depth - 1, val.alpha, val.beta);
					val.NowValue[i][j] = num.value;
					if (val.value <= num.value)
					{
						val.value = num.value;
						val.ScoreMax_x = i;
						val.ScoreMax_y = j;
					}
					map[i][j] = none;
					if (num.value >= val.beta)
						return val;
					val.alpha = max(val.alpha, val.value);
				}
			}
		return val;
	}
}
Score Min(int depth, int alpha, int beta)
{
	Score val;
	val.value = 1000000;
	val.alpha = alpha;
	val.beta = beta;
	if (depth <= 0 || judgeResult())
	{
		return evaluate();
	}
	else
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				if (map[i][j] == none)  //如果该位置没有棋子
				{
					map[i][j] = black;
					Score num = Max(depth - 1, val.alpha, val.beta);
					if (val.value >= num.value)
					{
						val.value = num.value;
						val.ScoreMin_x = i;
						val.ScoreMin_y = j;
					}
					map[i][j] = none;

					if (num.value <= val.alpha)
						return val;
					val.beta = MIN(val.beta, val.value);
				}
			}
		return val;
	}
}
