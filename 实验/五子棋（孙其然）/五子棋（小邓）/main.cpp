//main.cpp
//问题 算法 四连子不封 加载界面 人人对战要改结束界面 
#include<graphics.h>
#include<Windows.h>
#include<mmsyscom.h>//播放音乐
#include"chessdata.h"
#include<math.h>
#include <time.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib")//库
IMAGE chessBlackimg;
IMAGE chessWhiteimg;
struct ChessData game;
const int map_x = 31, map_y = 37, mapchess_x = 43, mapchess_y = 42;//棋盘数据 空白区 行行列列间隔
//纠正点击（行列）
int clickRow, clickList;

/*******************************************************************************************************/
bool kaijv()
{
	initgraph(800, 800);//创建棋盘窗口
	loadimage(0, L"wzqjm.png");
	//音乐
	mciSendString(L"play gfkaijv.mp3", 0, 0, 0);
	int n;
next:scanf_s("%d", &n);
	if (n == 1)return false;
	if (n == 2)return true;
	else goto next;

}

/*项目初始化 内部函数*/
void init() {
	initgraph(800, 796);//创建棋盘窗口
	mciSendString(L"stop gfkaijv.mp3", 0, 0, 0);
	loadimage(0, L"gfqipan.jpg");//字符集更改
	//开局音乐
	mciSendString(L"play kaijv.mp3", 0, 0, 0);
	loadimage(&chessBlackimg, L"hei.png", Block_size, Block_size, true);//true:等比例缩放
	loadimage(&chessWhiteimg, L"bai.png", Block_size, Block_size, true);//true:等比例缩放

	/*初始化游戏模型*/
	initChessData(&game);
}

//模糊落子判断函数 是否占用 （内部函数）4
bool clickDIM(MOUSEMSG msg) {
	int list = (msg.x - map_x) / mapchess_x;
	int row = (msg.y - map_y) / mapchess_y;//列行

	int leftTop_x = map_x + list * mapchess_x;
	int leftTop_y = map_y + row * mapchess_y;//左上角坐标

	int selectpot = false;//判断是否选好点
	do {
		//左上
		int len1 = sqrt((msg.x - leftTop_x) * (msg.x - leftTop_x) + (msg.y - leftTop_y) * (msg.y - leftTop_y));
		if (len1 < Dim)
		{
			clickRow = row;
			clickList = list;
			if (game.chessMap[clickRow][clickList] == 0)//判断是否占用
			{
				selectpot = true;
			}
			break;
		}
		//右上
		int len2 = sqrt((msg.x - leftTop_x + mapchess_x) * (msg.x - leftTop_x + mapchess_x) + (msg.y - leftTop_y) * (msg.y - leftTop_y));
		if (len2 < Dim)
		{
			clickRow = row;
			clickList = list + 1;
			if (game.chessMap[clickRow][clickList] == 0)
			{
				selectpot = true;
			}
			break;
		}
		//左下
		int len3 = sqrt((msg.x - leftTop_x) * (msg.x - leftTop_x) + (msg.y - leftTop_y + mapchess_y) * (msg.y - leftTop_y + mapchess_y));
		if (len3 < Dim)
		{
			clickRow = row + 1;
			clickList = list;
			if (game.chessMap[clickRow][clickList] == 0)
			{
				selectpot = true;
			}
			break;
		}
		//右下
		int len4 = sqrt((msg.x - leftTop_x + mapchess_x) * (msg.x - leftTop_x + mapchess_x) + (msg.y - leftTop_y + mapchess_y) * (msg.y - leftTop_y + mapchess_y));
		if (len4 < Dim)
		{
			clickRow = row + 1;
			clickList = list + 1;
			if (game.chessMap[clickRow][clickList] == 0)
			{
				selectpot = true;
			}
			break;
		}
	} while (0);//用循环好用break跳出
	return selectpot;
}

//内部函数
void chessDown(int row, int list, int i)
{
	mciSendString(L"play luozi.mp3", 0, 0, 0);
	//图形矫正
	int x = map_x + clickList * mapchess_x - 0.5 * Block_size;
	int y = map_y + clickRow * mapchess_y - 0.5 * Block_size;
	if (i == -1)
	{
		putimage(x, y, &chessWhiteimg);
	}
	if (i == 1)
	{
		putimage(x, y, &chessBlackimg);
	}
}

//落子方修改占位 后手存数据 (内部函数） 
void updataGameMap(struct ChessData* data, int row, int list)
{
	if (!data)return;
	if (data->playerFlag)data->chessMap[row][list] = 1;
	else data->chessMap[row][list] = -1;
	//换手
	data->playerFlag = !data->playerFlag;
}

//玩家落子
void manGO(int n)
{
	chessDown(clickRow, clickList, n);
	updataGameMap(&game, clickRow, clickList);
}

//ai算法评定 “一子 死二 活二 死三 活三 死四 杀四” 多个最高分，随机取一个 （内部函数）
void caculateScore(ChessData * data)
{
	if (!data)return;
	int personalNum = 0;//玩家连城子数目
	int botNum = 0;//ai连城子数目
	int emptyNum = 0;//各个方向空白位个数
	//初始化评分数组 为0
	memset(data->scoreMap, 0, sizeof(data->scoreMap));
	for (int row = 0; row < Board_width; ++row)
	{
		for (int list = 0; list < Board_width; ++list)
		{
			//空白点计算
			if (row >= 0 && list >= 0 && data->chessMap[row][list] == 0)
			{
				//遍历四个方向 计算正反方向
				int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int k = 0; k < 4; ++k)
				{
					int x = directs[k][0];
					int y = directs[k][1];
					//重置
					int personalNum = 0;//玩家连城子数目
					int botNum = 0;//ai连城子数目
					int emptyNum = 0;//各个方向空白位个数
					//对黑棋正向评分
					for (int i = 1; i <= 4; ++i)
					{
						if (row + i * y >= 0 && row + i * y < Board_width && list + i * x >= 0 && list + i * x <= Board_width && data->chessMap[row + i * y][list + i * x] == 0)
						{
							emptyNum++;
							break;//遇到空白位置，停止该方向的搜索
						}
						else//出边界，或者遇到白棋，就停止该方向的搜索
							break;
					}
					//对黑棋反向评分
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y >= 0 && row - i * y < Board_width && list - i * x >= 0 && list - i * x <= Board_width && data->chessMap[row - i * y][list - i * x] == 1)
						{
							personalNum++;
						}
						//空白位
						else if (row - i * y >= 0 && row - i * y < Board_width && list - i * x >= 0 && list - i * x <= Board_width && data->chessMap[row - i * y][list - i * x] == 0)
						{
							emptyNum++;
							break;
						}
						else //出边界，或者已有AI棋子
						{
							break;
						}
					}
					if (personalNum == 1) //杀二
						data->scoreMap[row][list] += 10;
					else if (personalNum == 2)
					{
						if (emptyNum == 1) //死三
							data->scoreMap[row][list] += 30;
						else if (emptyNum == 2) //活三
							data->scoreMap[row][list] += 40;
					}
					else if (personalNum == 3)
					{
						if (emptyNum == 1) //死四
							data->scoreMap[row][list] += 60;
						else if (emptyNum == 2) //活四
							data->scoreMap[row][list] += 200;
					}
					else if (personalNum == 4)
						data->scoreMap[row][list] += 20000;

					//进行一次清空
					emptyNum = 0;

					//对白棋进行正向评分
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y > 0 && row + i * y < Board_width && list + i * x > 0 && list + i * x < Board_width && data->chessMap[row + i * y][list + i * x] == -1)
						{
							botNum++;
						}
						else if (row + i * y > 0 && row + i * y < Board_width && list + i * x > 0 && list + i * x < Board_width && data->chessMap[row + i * y][list + i * x] == 0)
						{
							emptyNum++;
							break;
						}
						else
							break;
					}

					//对白棋反向评分
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y > 0 && row - i * y < Board_width && list - i * x > 0 && list - i * x < Board_width && data->chessMap[row - i * y][list - i * x] == -1)
						{
							botNum++;
						}

						//空白位
						else if (row - i * y > 0 && row - i * y < Board_width && list - i * x > 0 && list - i * x < Board_width && data->chessMap[row - i * y][list - i * x] == 0)
						{
							emptyNum++;
							break;
						}
						else //出边界
						{
							break;
						}
					}

					if (botNum == 0) //普通下子
						data->scoreMap[row][list] += 5;
					else if (botNum == 1) //杀二
						data->scoreMap[row][list] += 10;
					else if (botNum == 2) {
						if (emptyNum == 1) //死三
							data->scoreMap[row][list] += 25;
						else if (emptyNum == 2) //活三
							data->scoreMap[row][list] += 50;
					}
					else if (botNum == 3) {
						if (emptyNum == 1) //死四
							data->scoreMap[row][list] += 55;
						else if (emptyNum == 2) //活四
							data->scoreMap[row][list] += 300;
					}

					else if (botNum >= 4)
						data->scoreMap[row][list] += 30000;
				}

			}
		}
	}
}

//计算评分
point_t actionByAI(ChessData * data)
{
	caculateScore(data);
	//从评分中找最大分数的位置
	int maxScore = 0;
	point_t maxPoints[Board_width * Board_width] = { 0 };
	int k = 0;
	for (int row = 0; row < Board_width; row++)
		for (int list = 0; list < Board_width; list++)
		{
			//前提是这个坐标是空的
			if (data->chessMap[row][list] == 0)
			{
				if (data->scoreMap[row][list] > maxScore)
				{
					memset(maxPoints, 0, sizeof(maxPoints));
					k = 0;
					maxScore = data->scoreMap[row][list];
					maxPoints[k].row = row;
					maxPoints[k].list = list;
					k++;
				}
				else if (data->scoreMap[row][list] == maxScore) {
					maxPoints[k].row = row;
					maxPoints[k].list = list;
					k++;
				}
			}
		}

	srand((unsigned)time(0));
	int index = rand() % k;
	return maxPoints[index];
}

//AI落子
void AI_GO()
{
	point_t point = actionByAI(&game);
	clickRow = point.row;
	clickList = point.list;
	Sleep(1000);//AI假装思考
	chessDown(clickRow, clickList, -1);
	updataGameMap(&game, clickRow, clickList);
}

//胜负判断  （内部函数）
bool checkWin(ChessData* game, int row, int list)
{
	//横竖斜反斜四种大情况，每种情况都根据当前落子情况往后遍历5个棋子，有一种符合就算赢
	//水平方向
	for (int i = 0; i < 5; i++) {
		//往左5个，往右匹配4个，20种情况
		if (list - i >= 0 &&
			list - i + 4 < Board_width &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 1] &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 2] &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 3] &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 4])

			return true;
	}

	//竖直方向上下延申4个
	for (int i = 0; i < 5; i++) {
		if (list - i >= 0 &&
			list - i + 4 < Board_width &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 1][list] &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 2][list] &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 3][list] &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 4][list])

			return true;
	}

	//反斜线方向
	for (int i = 0; i < 5; i++) {
		if (row + i < Board_width &&
			row + i - 4 >= 0 &&
			list - i + 4 < Board_width &&
			//第[row+i]行，第[col-i]的棋子，与右上方连续的4个棋子都相同
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 1][list - i + 1] &&
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 2][list - i + 2] &&
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 3][list - i + 3] &&
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 4][list - i + 4])

			return true;
	}

	//"\"方向
	for (int i = 0; i < 5; i++) {
		//第[row+i]行，第[col-i]行的棋子，与左下方连续的四个棋子都相同
		if (row - i >= 0 &&
			row - i + 4 < Board_width &&
			list - i >= 0 &&
			list - i + 4 < Board_width &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 1][list - i + 1] &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 2][list - i + 2] &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 3][list - i + 3] &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 4][list - i + 4])

			return true;
	}
	return false;
}

//动画 语音 关闭窗口
bool checkOver() //检查游戏是否结束
{
	if (checkWin(&game, clickRow, clickList)) {
		Sleep(1000);
		//黑棋赢，此时标记已经反转，轮到白棋落子
		if (game.playerFlag == false) {
			mciSendString(L"play shengli.mp3", 0, 0, 0);
			loadimage(0, L"shengli.png");
		}
		else
		{
			mciSendString(L"play shibai.mp3", 0, 0, 0);
			loadimage(0,L"shibai.png");
		}

		Sleep(5000);
		closegraph();
		return true;
	}
	return false;
}
bool checkOver2()//检查游戏是否结束
{
	if (checkWin(&game, clickRow, clickList)) {
		Sleep(1000);
		//黑棋赢，此时标记已经反转，轮到白棋落子
		if (game.playerFlag == false) {
			mciSendString(L"play win.mp3", 0, 0, 0);
			loadimage(0,L"heiwin.png");
		}
		else
		{
			mciSendString(L"play win.mp3", 0, 0, 0);
			loadimage(0, L"baiwin.png");
		}

		Sleep(5000);
		closegraph();
		return true;
	}
	return false;
}

//人人对战
void renren()
{
	int n = 1;
	while (1)
	{   //鼠标
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && clickDIM(msg))//左键
		{
			manGO(n);
			checkOver2();
			n *= -1;
		}
	}
}

//人ji对战
void renji()
{
	while (1)
	{   //鼠标
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && clickDIM(msg))//左键
		{
			manGO(1);
			checkOver();

			AI_GO();
			checkOver();
		}
	}
}

int main(void)
{

	if (kaijv())
	{
		init();
		renji();
	}
	else
	{
		init();
		renren();
	}

	system("pause");
	return 0;
}

