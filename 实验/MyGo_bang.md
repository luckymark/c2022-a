#Go_bang
##1.玩法规则
可选择先后手，可悔一步棋，但棋局实在不理想可以直接点击重新开始，无时间限制，禁手等。
##2实现
###1工具
visual studio2022+Easyx
###2模块
####1打印棋盘
```C
void board()
{
	initgraph(950, 800);
	setbkcolor(RGB(209, 209, 209));
	cleardevice();
	for (int i = 50; i <= 750; i += 50)
	{
		line(i, 50, i, 750);
		line(50, i, 750, i);
	}

	setlinecolor(BLACK);
	settextstyle(40, 0, "宋体");
	outtextxy(800, 200, "悔 棋");
	outtextxy(800, 300, "重 来");
	outtextxy(800, 400, "后 手");
	outtextxy(800, 500, "退 出");
	settextcolor(BLACK);
	settextstyle(15, 0, "宋体");
}
```
通过计算棋盘的大小和格数运用EasyX的函数进行棋盘的绘制。
####2棋子结构
```C
struct point {
	int state;          //  玩家-1,   空位置0,   电脑1
	long double value;        //该点价值分
	long double n_value;        //总优势分
};
```
####3初始化棋盘（点击重新开始时调用）
```C
void initialize(struct point p[25][25])
{
	int i, j;
	num = 0;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 25; j++)
		{
			p[i][j].state = 0;   //为空
			p[i][j].value = 0;
			p[i][j].n_value = 0;
		}
	}
}
```
####4落子后结果判断
```C
int result(struct point p[25][25])
{
	int i, j, k = 0, x = 0, y = 0, b = 0, q = 0, winner = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)
			{
				k++;
				if (k == 0)
				{
					winner= draw;//平局
				}
			}
			if (p[i][j].state)
			{
				for (x = -2; p[i][j].state == p[i][j + x].state && x < 4; x++)     //横
				{
				}
				for (y = -2; p[i][j].state == p[i + y][j].state && y < 4; y++)      //纵
				{
				}
				for (b = -2; p[i][j].state == p[i + b][j + b].state && b < 4; b++)    //斜下
				{
				}
				for (q = -2; p[i][j].state == p[i - q][j + q].state && q < 4; q++)    //斜上
				{
				}
				if (x == 3 || y == 3 || b == 3 || q == 3)
				{
					if (p[i][j].state == 1)
					{
						winner = com; //电脑赢
					}
					if (p[i][j].state == -1)
					{
						winner = hum; //玩家赢
					}
				}
			}
		}
	}
	return winner; 
}
```
遍历棋盘，看是否有五子连线。
####5游戏结束时
```C
void gameOver(int winner)
{
	point pp[25][25];      	
	initialize(pp);      //初始化
	initgraph(400, 400);
	cleardevice();     //使用当前背景色清空绘图设备
	settextstyle(50, 24, "宋体");
	settextcolor(RED);    //字体颜色
	if (winner == draw)
	{
		outtextxy(100, 50, "平局");
	}
	else if (winner == hum)
	{
		outtextxy(100, 50, "玩家获胜");
	}
	else if (winner == com)
	{
		outtextxy(100, 50, "电脑获胜");
	}
	settextcolor(WHITE);
	outtextxy(50, 200, "返回游戏界面");
	outtextxy(80, 300, " 结束游戏");

	while (true)
	{
		MOUSEMSG n;
		n = GetMouseMsg();
		switch (n.uMsg) {
		case WM_LBUTTONDOWN:
			if (n.x <= 350 && n.x >= 50 && n.y <= 250 && n.y >= 200)
				play(pp);   
			if (n.x <= 300 && n.x >= 80 && n.y <= 350 && n.y >= 300)
			{
				closegraph(); 
				exit(0);  
			}
		}
	}
}
```
####6游戏进行
```C
void play(struct point p[25][25])
{
	MOUSEMSG m;
	int  x, y, i, j;
	board();
	setlinecolor(WHITE);

	while (1)
	{
		m = GetMouseMsg();
		x = m.x % 50;
		y = m.y % 50;
		setrop2(R2_COPYPEN);
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x <= 900 && m.y < 250 && m.x >= 800 && m.y > 200)  //悔棋
			{
				regret(p);
				continue;
			}
			if (m.x <= 900 && m.y < 350 && m.x >= 800 && m.y > 300)	//重开
			{
				initialize(p);   //初始化
				play(p);
			}
			if (m.x <= 900 && m.y < 450 && m.x >= 800 && m.y > 400)  //后手
			{
				if (num < 1)
				{
					computer(p);   //电脑执棋
					num++;
				}
			}
			if (m.x <= 900 && m.y < 550 && m.x >= 800 && m.y > 500)  //退出
			{
				closegraph(); 
				exit(0);    
			}

			if (x >= 25)     //玩家执棋
				m.x = m.x - x + 50;
			else
				m.x = m.x - x;
			if (y >= 25)
				m.y = m.y - y + 50;
			else
				m.y = m.y - y;
			i = m.x / 50 - 1 + MIN; 
			j = m.y / 50 - 1 + MIN;
			if (i < 20 && j < 20)
			{
				if (p[i][j].state == -1)
					break;
				if (m.x <= 750 && m.y <= 750 && m.x >= 50 && m.y >= 50)
				{
					setfillcolor(BLACK);
					fillcircle(m.x, m.y, 20);
					ii = i;    //为悔棋坐标做记录
					jj = j;
					p[i][j].state = -1;//修改该位置的状态
				}
				if (result(p) != 0)//结束判断
				{
					Sleep(1000);
					gameOver(result(p));
				}
				computer(p);   
				if (result(p) != 0)
				{
					Sleep(1000);
					gameOver(result(p));
				}
				num++;    //对弈次数
			}
		}
	}
}
```
获取鼠标信息，判断所属区域，在棋盘上的话，则并将Lbuttondown的坐标转换为棋盘坐标，改变该点的棋子信息，并判断游戏结果，如果结束，调用gameOver函数，若没有，则换电脑执棋。如果所点击的区域是其它功能，则调用相应的函数。
####7悔棋
```C
void regret(struct point p[25][25])
{
	board();
	setrop2(R2_COPYPEN);  //设置绘制颜色
	setcolor(WHITE);
	p[ii][jj].state = 0;  //将上一步棋清空
	p[xx][yy].state = 0;
	for (int i = MIN; i < MAX; i++) {        //重新绘制棋盘
		for (int j = MIN; j < MAX; j++) {
			if (p[i][j].state == -1) {
				setfillcolor(BLACK);
				fillcircle((i + 1 - MIN) * 50, (j + 1 - MIN) * 50, 20);
			}
			if (p[i][j].state == 1) {
				setfillcolor(WHITE);
				fillcircle((i + 1 - MIN) * 50, (j + 1 - MIN) * 50, 20);
			}
		}
	}
}
```
利用之前下棋时记录的xx，yy来修改棋盘信息。
####8价值评估
```C
        //宏定义初始8个方向每个价值为10
				long double v1 = VALUE, v2 = VALUE, v3 = VALUE, v4 = VALUE, v5 = VALUE, v6 = VALUE, v7 = VALUE, v8 = VALUE;
				for (x = 0, n = j; p[i][j].state != -p[i][n + 1].state && n + 1 < 20 && x < 4; x++, n++)       //右
				{
				}
				if (x < 4)
				{
					v1 = 0;    //被挡住为0
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n + 1].state && k < 5; k++, n++)       //右
					{
						v1 *= VALUE;     //连续分数翻倍
					}
---------------------------------------------------------------------------------------------------------------

                p[i][j].value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));    //加上距离中心优势分
				if (p[i][j].state == -1)    //玩家棋子为负分
				{
					p[i][j].value = -p[i][j].value * DEFINE;       //DEFINE为偏向防守程度
				}
```
各方向的估值方式相同，如此估算出八个方向的分别价值，进而计算此时局势的总价值
```C
double assess(struct point p[25][25])
{
	int i, j;
	p_assess(p);     //某点价值
	long double s_value = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			s_value += p[i][j].value;//棋盘总优势分为所有点分数的和
		}
	}
	return s_value;
}
```
####9递归推演
```C
double deduction(struct point p[25][25], /*int sex,*/ int depth, long double a, long double b)
{
	int m, n, i, j, t = 0, br = 0;
	long double value = 0;
	if (depth == 0 || result(p) != 0)   //达到深度或棋局结束
	{
		return assess(p);       //递归出口，返回分数
	}
	else if (/*sex */depth % 2 == 1)    
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) { 
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0)   //为空
				{
		
					if (num<80&&!hasNieghbor(p, m, n))
					{
						value = Beta;
					}
					else {
						p[m][n].state = -1;   
						value = deduction(p,  depth - 1, a, b);
						p[m][n].state = 0;      
					}
					if (value < b)    
					{
						b = value;
					}
					if (b <= a)
					{
						br = 1;
						break;    
						
					}
				}
			}
		}
		return b; //返回分数
	}
	else if (depth % 2 == 0)     //电脑层
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1) {   
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].state == 0)     //为空
				{

					if (num < 80 && !hasNieghbor(p, m, n))
					{
						value = Alpha;
					}
					else {
						p[m][n].state = 1;     //棋下在这个地方
						value = deduction(p,/* sex + 1,*/ depth - 1, a, b);
						p[m][n].state = 0;     //撤回
					}
					if (value > a)    //找最大值
					{
						a = value;
					}
					if (b <= a)
					{
						br = 1;
						break;    
						
					}
				}
			}
		}
		return a;//返回分数
	}
	return 0;
}
```
利用alpha，beta剪枝和局部搜索来推演落子的可能情况,这里搜索的层数是四层，平均每次需要四五秒，到后面感觉需要时间会变多。
####9局部搜索
```C
bool hasNieghbor(struct point p[25][25], int m, int n)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (p[i + m][j + n].state != 0)
			{
				return true;
			}
		}
	}
	return false;
}
```
只考虑那些能和棋子产生关系的空位置，而不用考虑所有空位置，这样能极大减小b的值。局部搜索的考虑棋盘上每一个有子点周围8个方向上延申3个深度，只有这些地方会与现有棋子产生联系
####10电脑执棋函数
```C
int computer(struct point p[25][25])
{
	int i, j, x = 12, y = 12, m, n, t = 0;
	long double v = -MAXMAX;    
	for (i = MIN; i < MAX; i++)       
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)     
			{
			
				if (hasNieghbor(p,i,j) )  //不偏僻
				{
					p[i][j].state = 1;    //模拟落子
					if (result(p) == com)           //改枚举增加可读性
					{
						drop(p, i, j);    
						return 0;
					}
					else if ((p[i][j].n_value = deduction(p, 2, Alpha, Beta)) > KILL)       //迭代加深
					{
						drop(p, i, j);
						return 0;
					}  
					p[i][j].n_value = deduction(p, 4, Alpha, Beta);
					  p[i][j].state = 0;   
					if (p[i][j].n_value > v)
					{
						v = p[i][j].n_value;    
						x = i;
						y = j;     
					}					
				}
			}
		}
	}
	drop(p, x, y);    //下棋
	return 0;
}
```
电脑执棋时并没有考虑到路径长短。所以很容易出现在4层得到可以结束的点，其实在2层的时候也有一个这样的点，因为分数一样，AI会随机选择一个走法。就导致了明明可以两步赢的棋，AI非要走3步，对玩家来说，感觉就是在调戏人。所以电脑在搜索落点的时候做了个迭代加深和简单的算杀，从2层开始，逐步增加搜索深度，直到找到胜利走法或者达到深度限制为止，基于之前的评估函数估计了一个值KILL，先进行两层搜索，当某点的值大于KILL时，下在此处就可以结束战斗，就不用再继续搜索。不然的话，再进行四层搜索。搜索结束之后选择分值最高的点下子，调用drop。
####落子
传入棋盘和之前搜索到的最佳点坐标，落子
```C
void drop(struct point p[25][25], int x, int y)
{
	setfillcolor(WHITE); //填充颜色
	fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);//画圆，下这一步
	xx = x;
	yy = y;    //为悔棋坐标做记录
	p[x][y].state = 1;     //修改状态
}
```
###3效果
程序大小：144K
![](../屏幕截图%202023-02-14%20195107.png)
*效果图*
![](../屏幕截图%202023-02-14%20195245.png)
![](../屏幕截图%202023-02-14%20195352.png)
*游戏结束*
运行及算力：可手动改变搜索层数，如果改为两层的话可以秒响应，水平能够和我自己五五开吧（一般跟它的节奏下就得输，容易忽略某些地方，自己把握节奏就能赢）改为四层的话理论上应该更强，但实际感觉水平差别不大，但响应速度明显变慢，前几部到可以秒响应，后面平均就得四五秒。
###参考文献
https://blog.csdn.net/lihongxun945/article/details/50764168
https://blog.csdn.net/lihongxun945/article/details/50625267
https://blog.csdn.net/baixiaozhe/article/details/51872495
https://blog.csdn.net/lihongxun945/article/details/50730231
https://blog.csdn.net/lihongxun945/article/details/50668622
https://blog.csdn.net/lihongxun945/article/details/50992330
https://blog.csdn.net/livingsu/article/details/104536005
https://blog.csdn.net/weixin_69725192/article/details/124805624