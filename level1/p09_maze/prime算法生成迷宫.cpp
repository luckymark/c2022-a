#include <iostream>
using namespace std;
#include <graphics.h>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

#define WIDTH 1080//分辨率
#define HEIGHT 720
#define BLOCK_XY 10//小方格边长
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//小方格x轴数量
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//小方格y轴数量

#define kongqi COLORREF RGB(50,50,50)//空气颜色
#define qiangbi COLORREF RGB(255,255,255)//墙壁颜色
#define daixuan COLORREF RGB(0,255,0)//待选颜色
#define xuanzhong COLORREF RGB(255,0,0)//选中颜色

#define ROAD 0//路（空气）
#define WALL 1//墙壁
#define WAIT 2//待选路点

struct block {
public:
	int x;
	int y;
	block(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

int map[BLOCK_WIDTH][BLOCK_HEIGHT];//0代表空气，1代表墙壁，2代表待选路点，3代表选中路点（但是并没有用到）
vector<block*> openlist;//待选列表
vector<block*> list;

/*函数声明*/
void clearscreen(COLORREF RGB);//清空地图为RGB颜色(带有网格)
void gamedrawpixal(int x, int y, COLORREF RGB);//在x，y位置画颜色为RGB的方格
void init();//初始化
void join(int x, int y);//将x,y四周是墙壁的路点加入待选列表
void display();//刷新屏幕
void prim_main();//prim主循环
void through(int x, int y);//将x,y与它四周一个随机已经变成路的路点打通
/*********/

void init() {
	openlist.clear();
	/*地图初始化为墙*/
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			map[x][y] = WALL;
		}
	}
	/*随机选一个路点，将它变成路*/
	map[0][0] = ROAD;
	/*将路点四周不是路的路点加入待选列表*/
	join(0, 0);
	prim_main();
}
void prim_main() {
	while (openlist.size() > 0) {
		/*从待选路点随机选一个路点A*/
		int AIndexea = rand() % openlist.size();
		block* A = openlist[AIndexea];
		/*将A与它四周一个随机已经变成路的路点打通*/
		through(A->x, A->y);
		/*将A变成路*/
		map[A->x][A->y] = ROAD;
		/*将A四周不是路的路点加入待选列表*///(注意，不要重复添加路点！)
		join(A->x, A->y);
		/*从待选路点中移除A*/
		openlist.erase(openlist.begin() + AIndexea);

		gamedrawpixal(A->x, A->y, xuanzhong);
		FlushBatchDraw();
		display();
	}
	openlist.clear();
}
void through(int x, int y) {
	list.clear();
	//上
	if (y - 2 >= 0 && map[x][y - 2] == ROAD) {
		block* a = new block(x, y - 1);
		list.push_back(a);
	}
	//下
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == ROAD) {
		block* b = new block(x, y + 1);
		list.push_back(b);
	}
	//左
	if (x - 2 >= 0 && map[x - 2][y] == ROAD) {
		block* c = new block(x - 1, y);
		list.push_back(c);
	}
	//右
	if (x + 2 <= BLOCK_WIDTH - 1 && map[x + 2][y] == ROAD) {
		block* d = new block(x + 1, y);
		list.push_back(d);
	}
	int BIndexea = rand() % list.size();
	block* B = list[BIndexea];
	/*将x，y与B打通*/
	map[B->x][B->y] = ROAD;
}
void join(int x, int y) {
	//上
	if (y - 2 >= 0 && map[x][y - 2] == WALL) {
		block* a = new block(x, y - 2);
		openlist.push_back(a);
		map[x][y - 2] = WAIT;
	}
	//下
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == WALL) {
		block* b = new block(x, y + 2);
		openlist.push_back(b);
		map[x][y + 2] = WAIT;
	}
	//左
	if (x - 2 >= 0 && map[x - 2][y] == WALL) {
		block* c = new block(x - 2, y);
		openlist.push_back(c);
		map[x - 2][y] = WAIT;
	}
	//右
	if (x + 2 <= BLOCK_WIDTH - 1 && map[x + 2][y] == WALL) {
		block* d = new block(x + 2, y);
		openlist.push_back(d);
		map[x + 2][y] = WAIT;
	}
}
void display() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (map[x][y] == WALL) {
				gamedrawpixal(x, y, qiangbi);
			}
			else if (map[x][y] == ROAD) {
				gamedrawpixal(x, y, kongqi);
			}
			else if (map[x][y] == WAIT) {
				gamedrawpixal(x, y, daixuan);
			}
		}
	}
	FlushBatchDraw();
}
void clearscreen(COLORREF RGB) {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			gamedrawpixal(x, y, RGB);
		}
	}
}
void gamedrawpixal(int x, int y, COLORREF RGB) {
	setfillcolor(RGB); setlinecolor(COLORREF RGB(0, 0, 0));
	fillrectangle(x * BLOCK_XY, y * BLOCK_XY, BLOCK_XY + x * BLOCK_XY, BLOCK_XY + y * BLOCK_XY);
}
int main() {
	srand((unsigned)time(NULL));//随机数种子
	initgraph(WIDTH, HEIGHT);//创建绘图窗口
	BeginBatchDraw();//开始批量绘图
	cleardevice();//清空显示

	init();

	display();
	FlushBatchDraw();//将缓冲输出到屏幕

	while (1);
}
