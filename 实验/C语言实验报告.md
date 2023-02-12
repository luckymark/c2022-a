﻿# C语言实验报告

郑灿坤 2022080908018

## 《AI五子棋对弈》程序的功能

 - 玩家能够选择**先后手**
 - 能够**悔棋**并回滚多步
 - 根据每局的胜利或失败，玩家可以看到自己的**积分**

**游戏规则是最先完成五子连珠的一方获得胜利。**

## 配置开发环境
我使用的是Visual Studio 2022软件，安装了EasyX图形库来导入图片素材。


## 实战

我把五子棋的开发分为以下几个模块

 1. **开始界面**（包含**游戏规则讲解**），并根据玩家选择调整**先后手**
 2. 初始化，**导入**棋盘，黑白棋，胜利、失败界面**图片素材**和开始、胜利、失败的**音频素材**
 3. 玩家用鼠标落子，经过**模糊定位法**之后，让棋子落在点上
 4. 建立**分值评价体系**，AI评估场上空格分值后，**选择分值最大，即优势最大的点自动落子**
 5. **判断胜负**并展示胜利、失败界面
 7. 根据玩家胜利/失败场数**计算玩家积分**，并在胜利/失败界面展示玩家的积分
 8. **悔棋**功能
 
 各模块之间的关系大致可以由下面的**流程图**表示：
 ```mermaid
graph TB
A(开始界面选择先后手初始化) --> B[游戏开始]
B --> C[AI计算场上空格分值]
C --> D[AI落子]
B --> E[玩家落子]
E-->F
D-->F{检测游戏是否结束}
F--是-->G(展示失败或成功界面和玩家积分)
F--否-->B
```
我认为在开发过程中比较关键的代码有下面这些：

**模糊定位的代码：**

*通过计算得到玩家鼠标单击点离棋盘上最近的点，实现玩家能够在棋盘上准确落子，让黑白棋图片精确落在点位上*
```
bool clickBoard(MOUSEMSG msg)
{
	int col = (msg.x - margin_x) / BLOCK_SIZE;
	int row = (msg.y - margin_y) / BLOCK_SIZE;

	int leftTopPosX = margin_x + col * BLOCK_SIZE;
	int leftTopPosY = margin_y + row * BLOCK_SIZE;

	int selctPos = false;


	do {//左上
		int len = sqrt((msg.x - leftTopPosX) * (msg.x - leftTopPosX) +
			(msg.y - leftTopPosY) * (msg.y - leftTopPosY));
		if (len < POS_OFFSET) {
			clickPosRow = row;
			clickPosCol = col;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;
		}
		//右上
		int posX = leftTopPosX + BLOCK_SIZE;
		int posY = leftTopPosY;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET) {
			clickPosRow = row;
			clickPosCol = col + 1;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;
		}
		//右下
		posX = leftTopPosX + BLOCK_SIZE;
		posY = leftTopPosY + BLOCK_SIZE;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET) {
			clickPosRow = row + 1;
			clickPosCol = col + 1;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;
		}
		//左下
		posX = leftTopPosX;
		posY = leftTopPosY + BLOCK_SIZE;
		len = sqrt((msg.x - posX) * (msg.x - posX) +
			(msg.y - posY) * (msg.y - posY));
		if (len < POS_OFFSET) {
			clickPosRow = row + 1;
			clickPosCol = col;
			if (game.chessMap[clickPosRow][clickPosCol] == 0) {
				selctPos = true;
			}
			break;

		}
	} while (0);
	return selctPos;
}
```
**计算场上分值和AI行动的代码：**

根据场上所有方向（八个方向，五个子以内），计算玩家和AI已落子的个数，从而通过赋分制给已落子周围的空格计算分值，AI会落子在分值最大，即优势最大的点上。（比如AI已经四子连珠且有空格，那么此时这个空格是最高分）
如果场上有很多相同分值的空格，那么AI会随机落子其中一个。

```
//计算场上落点分值
void calculateScore(ChessData* data) {
	if (!data)return;

	int personNum = 0;
	int botNum = 0;
	int emptyNum = 0;

	memset(data->scoreMap, 0, sizeof(data->scoreMap));
	for (int row = 0; row < BOARD_GRADE_SIZE; row++)
		for (int col = 0; col < BOARD_GRADE_SIZE; col++) {
			if (row >= 0 && col >= 0 && data->chessMap[row][col] == 0) {
				int directs[4][2] = { {1,0},{1,1},{0,1} ,{-1,1} };
				for (int k = 0; k < 4; k++) {
					int x = directs[k][0];
					int y = directs[k][1];

					personNum = 0;
					botNum = 0;
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						if (row + i * y >= 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x >= 0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == 1) {
							personNum++;
						}
						else if (row + i * y >= 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x >= 0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}
					for (int i = 1; i <= 4; i++) {
						if (row - i * y >= 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x >= 0 && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == 1) {
							personNum++;
						}
						else if (row - i * y >= 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x >= 0 && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}
					if (personNum == 1)
						data->scoreMap[row][col] += 10;
					else if (personNum == 2) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 30;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 40;
					}
					else if (personNum == 3) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 60;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 200;
					}
					else if (personNum == 4)
						data->scoreMap[row][col] += 20000;

					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						if (row + i * y > 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x>0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == -1) {
							botNum++;
						}
						else if (row + i * y > 0 && row + i * y < BOARD_GRADE_SIZE &&
							col + i * x>0 && col + i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row + i * y][col + i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}

					for (int i = 1; i <= 4; i++) {
						if (row - i * y > 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x>0 && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == -1) {
							botNum++;
						}
						else if (row - i * y > 0 && row - i * y < BOARD_GRADE_SIZE &&
							col - i * x && col - i * x < BOARD_GRADE_SIZE &&
							data->chessMap[row - i * y][col - i * x] == 0) {
							emptyNum++;
							break;
						}
						else
							break;
					}
					if (botNum == 0)
						data->scoreMap[row][col] += 5;
					else if (botNum == 1)
						data->scoreMap[row][col] += 10;
					else if (botNum == 2) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 25;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 50;
					}
					else if (botNum == 3) {
						if (emptyNum == 1)
							data->scoreMap[row][col] += 55;
						else if (emptyNum == 2)
							data->scoreMap[row][col] += 300;
					}
					else if (botNum == 4)
						data->scoreMap[row][col] += 30000;
				}
			}
		}
}

//根据场上点位分值算出AI的落点
point_t actionByAI(ChessData* data) {
	calculateScore(data);

	int maxScore = 0;

	point_t maxPoints[BOARD_GRADE_SIZE * BOARD_GRADE_SIZE] = { 0 };
	int k = 0;

	for (int row = 0; row < BOARD_GRADE_SIZE; row++)
		for (int col = 0; col < BOARD_GRADE_SIZE; col++)
		{

			if (data->chessMap[row][col] == 0)
			{
				if (data->scoreMap[row][col] > maxScore)
				{
					memset(maxPoints, 0, sizeof(maxPoints));
					k = 0;
					maxScore = data->scoreMap[row][col];

					maxPoints[k].row = row;
					maxPoints[k].col = col;
					k++;
				}
				else if (data->scoreMap[row][col] == maxScore) {

					maxPoints[k].row = row;
					maxPoints[k].col = col;
					k++;
				}
			}
		}
	srand((unsigned)time(0));
	int index = rand() % k;
	return maxPoints[index];
}
```

**判断场上是否五子连珠的代码：**

*计算八个方向上的相同颜色棋子的连子数，一旦达到5，立即判断胜负。*
```
bool checkWin(ChessData* game, int row, int col)
{
	for (int i = 0; i < 5; i++)
	{

		if (col - i >= 0 &&
			col - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 1] &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 2] &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 3] &&
			game->chessMap[row][col - i] == game->chessMap[row][col - i + 4])
			return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 1][col] &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 2][col] &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 3][col] &&
			game->chessMap[row - i][col] == game->chessMap[row - i + 4][col])
			return true;
	}

	for (int i = 0; i < 5; i++)
	{
		if (row + i < BOARD_GRADE_SIZE &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 1][col - i + 1] &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 2][col - i + 2] &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 3][col - i + 3] &&
			game->chessMap[row + i][col - i] == game->chessMap[row + i - 4][col - i + 4])
			return true;
	}

	for (int i = 0; i < 5; i++)
	{

		if (row - i >= 0 &&
			row - i + 4 < BOARD_GRADE_SIZE &&
			col - i >= 0 &&
			col - i + 4 < BOARD_GRADE_SIZE &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 1][col - i + 1] &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 2][col - i + 2] &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 3][col - i + 3] &&
			game->chessMap[row - i][col - i] == game->chessMap[row - i + 4][col - i + 4])
			return true;
	}
	return false;
}
```
**悔棋的代码：**

运用堆栈的原理，先创建一个链表结构，存放场上棋盘各点的数据(棋盘的基层数据是一个二重数组，1代表白棋，-1代表黑棋，0代表空格)。
通过入栈出栈的方式更新棋盘各点底层数据，然后重新绘制棋盘和剩下的棋子。
```
typedef struct backstorage {
	int row;
	int col;
	struct backstorage* next;
}Node;

Node *head=(Node*)malloc(sizeof(Node));
void creatbackstorage(int clickPosRow,int clickPosCol) {
	Node* p;
	p = (Node*)malloc(sizeof(Node));
	if (p != NULL) {
		p->col = clickPosCol;
		p->row = clickPosRow;
		p->next = NULL;
	}
	if (head->next == NULL) {
		head->next = p;
	}
	else {
		Node* tail = head;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = p;
	}
}

void back(ChessData* data) {
	if (head->next == NULL) {
		return;
	}
	else {
		Node* tail = head;
		while (tail->next->next != NULL) {
			tail = tail->next;
		}
		data->chessMap[tail->next->row][tail->next->col] = 0;
		mciSendString("play res/repent1.mp3", 0, 0, 0);
		tail->next = NULL;
		free(tail->next);
		
	}
	recover(data);
	
	return;
}

void recover(ChessData* data) {
	system("cls");
	initgraph(897, 895);
	loadimage(0, "res/棋盘2.jpg");
	for (int i = 0; i < BOARD_GRADE_SIZE; i++) {
		for (int j = 0; j < BOARD_GRADE_SIZE; j++) {
			if (data->chessMap[i][j] == -1)
			{
				int x = margin_x + j * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
				int y = margin_y + i * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
					drawPNG(&chessBlackImg, x, y);
			}
			if (data->chessMap[i][j] == 1)
			{
				int x = margin_x + j * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
				int y = margin_y + i * BLOCK_SIZE - 0.5 * BLOCK_SIZE;
				drawPNG(&chessWhiteImg, x, y);
			}
		}
	}
}
```


## 我的成果

**开始界面**
![开始界面]([开始界面.jpg (599×1274) (raw.githubusercontent.com)](https://raw.githubusercontent.com/Foreon/c2022-a/main/%E5%AE%9E%E9%AA%8C/%E4%BA%94%E5%AD%90%E6%A3%8B%E6%B8%B8%E6%88%8F%E7%95%8C%E9%9D%A2/%E5%BC%80%E5%A7%8B%E7%95%8C%E9%9D%A2.jpg))

**游戏运行界面**

![运行界面]([运行界面.jpg (1355×1408) (raw.githubusercontent.com)](https://raw.githubusercontent.com/Foreon/c2022-a/main/%E5%AE%9E%E9%AA%8C/%E4%BA%94%E5%AD%90%E6%A3%8B%E6%B8%B8%E6%88%8F%E7%95%8C%E9%9D%A2/%E8%BF%90%E8%A1%8C%E7%95%8C%E9%9D%A2.jpg))

**胜利界面**

![胜利]([胜利界面.jpg (897×895) (raw.githubusercontent.com)](https://raw.githubusercontent.com/Foreon/c2022-a/main/%E5%AE%9E%E9%AA%8C/%E4%BA%94%E5%AD%90%E6%A3%8B%E6%B8%B8%E6%88%8F%E7%95%8C%E9%9D%A2/%E8%83%9C%E5%88%A9%E7%95%8C%E9%9D%A2.jpg))

**失败界面**

![失败界面]([失败界面.jpg (1341×1377) (raw.githubusercontent.com)](https://raw.githubusercontent.com/Foreon/c2022-a/main/%E5%AE%9E%E9%AA%8C/%E4%BA%94%E5%AD%90%E6%A3%8B%E6%B8%B8%E6%88%8F%E7%95%8C%E9%9D%A2/%E5%A4%B1%E8%B4%A5%E7%95%8C%E9%9D%A2.jpg))

我根据自己的兴趣，为本程序设计了**开始界面**，**失败和胜利界面**的图片。希望能让玩家感到**有趣**一点。

并且玩家落子，悔棋，胜利或失败时都是有**音效**的。

## 程序运行速度和大小

经实测，本程序全程不卡顿，帧率方面由于游戏类型限制，并不能体现。（就像扫雷这种游戏类型的帧率）

除去图片素材和音频素材，本程序exe文件大小为167KB。
## AI的棋力水平评价
本程序的AI落子采用的是**赋分机制**，选取优势最大的点落子，在测试过程中取得了不错的水平。
我采用的测试方法是人工测试。

我们宿舍4人都和本程序的AI下过棋（玩家先手），第一次测试中都没有赢过AI.

我自己测试得出的结论是：

 - 玩家先手AI赢的概率大概是五分之四。
 - 玩家后手AI赢的概率大概是十分之九。

可见本程序AI的棋力水平还是相当不错的，在面对普通人（以我宿舍四人为代表，平常没研究过五子棋的必胜下法，仅仅把五子棋当作娱乐的人群）的时候，拥有**非常高的胜率**。

## 参考文献
[(14条消息) C语言实践----五子棋（附源代码及思路讲解）_c语言五子棋代码_Hiya◡a的博客-CSDN博客](https://blog.csdn.net/weixin_61866141/article/details/125996622?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167619867216800186527181%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167619867216800186527181&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-125996622-null-null.142^v73^insert_down3,201^v4^add_ask,239^v1^insert_chatgpt&utm_term=c%E8%AF%AD%E8%A8%80%E4%BA%94%E5%AD%90%E6%A3%8B&spm=1018.2226.3001.4187exe%E6%96%87%E4%BB%B6)

[【C语言】游戏开发：实现人机对战五子棋_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1UT4y1B7Th/?spm_id_from=333.337.search-card.all.click&vd_source=200e4e4a6866c2ee223c0a5586de29b1)
