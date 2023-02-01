#include"maze.h"
void mapinit() {
	/*地图初始化为墙*/
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			map[x][y] = WALL;
		}
	}
	/*for (int i = 0; i < BLOCK_HEIGHT; i++) {
		vector<int>row;
		for (int j = 0; j < BLOCK_WIDTH; j++)
		{
			row.push_back(WALL);
		}
		map.push_back(row);
	}*/
	//选择一点为路
	map[0][0] = ROAD;
	specificpos firstpos{0,0};
	judgewait(&firstpos);
	prime_main();
	map[0][0] = HUMAN;//人物出生点
	map[MAPROW - 2][MAPCOL - 2] = DOOR;
	map[MAPROW - 1][MAPCOL - 2] = DOOR;
	FlushBatchDraw();//释放绘图，目的是取消闪烁
	display();
}

void judgewait(specificpos *pos) {
	//判断上面
	if ((pos->y - 2) >= 0 && map[pos->x][pos->y - 2] ==WALL ) {
		specificpos* waitpos = new specificpos(pos->x, pos->y - 2);
		//上面那句好像可以这样写(malloc申请更为复杂)：specificpos* waitpos = (specificpos*)malloc(sizeof(specificpos*));waitpos={};
		WALLlist.push_back(waitpos);
		map[pos->x][pos->y - 2] = WAIT;
	}
	//判断下面
	if ((pos->y + 2) <=MAPCOL-1 && map[pos->x][pos->y + 2] == WALL) {
		specificpos* waitpos = new specificpos(pos->x, pos->y + 2);
		//上面那句好像可以这样写：specificpos* waitpos = (specificpos*)malloc(sizeof(specificpos*));waitpos={};
		WALLlist.push_back(waitpos);
		map[pos->x][pos->y + 2] = WAIT;
	}
	//判断左面
	if (pos->x - 2 >= 0 && map[pos->x - 2][pos->y] == WALL)
	{
		specificpos* waitpos = new specificpos(pos->x - 2, pos->y);
		WALLlist.push_back(waitpos);
		map[pos->x - 2][pos->y] = WAIT;
	}
	//判断右面
	if (pos->x + 2 <= MAPROW-1 && map[pos->x + 2][pos->y] == WALL)
	{
		specificpos* waitpos = new specificpos(pos->x + 2, pos->y);
		WALLlist.push_back(waitpos);
		map[pos->x + 2][pos->y] = WAIT;
	}
}

void through(specificpos* pos) {
	ROADlist.clear();
	//判断上面
	if ((pos->y - 2) >= 0 && map[pos->x][pos->y - 2] == ROAD) {
		specificpos* roadpos = new specificpos(pos->x, pos->y - 1);
		ROADlist.push_back(roadpos);
	}
	//判断下面
	if ((pos->y + 2) <= MAPCOL-1 && map[pos->x][pos->y + 2] == ROAD) {
		specificpos* roadpos = new specificpos(pos->x, pos->y + 1);
		ROADlist.push_back(roadpos);
	}
	//判断左面
	if (pos->x - 2 >= 0 && map[pos->x - 2][pos->y] == ROAD)
	{
		specificpos* roadpos = new specificpos(pos->x - 1, pos->y);
		ROADlist.push_back(roadpos);
	}
	//判断右面
	if (pos->x + 2 <= MAPROW-1 && map[pos->x + 2][pos->y] == ROAD)
	{
		specificpos* roadpos = new specificpos(pos->x + 1, pos->y);
		ROADlist.push_back(roadpos);
	}
	if (ROADlist.size() > 0) {
		int primenum2 = rand() % ROADlist.size();
		specificpos* roadpos2 = ROADlist[primenum2];
		map[roadpos2->x][roadpos2->y] = ROAD;
	}
	
}

void prime_main() {
	while(WALLlist.size()>0){
		//随机一个位置将wait转化为road
		int primenum = rand() % WALLlist.size();
		specificpos* roadpos = WALLlist[primenum];

		through(roadpos);//打通两路点之间的墙点

		map[roadpos->x][roadpos->y] = ROAD;//把待选点变为路点
		
		judgewait(roadpos);//加入新的待选点

		WALLlist.erase(WALLlist.begin() + primenum);//将变成路点的墙点删除
		
		//开始绘图
		gamedrawpixal(roadpos, xuanzhong);
		FlushBatchDraw();//目的是取消闪烁
		display();
	}
	WALLlist.clear();
}

//遍历所有位置，画block_width*block_height个方块
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
			else if (map[x][y] == HUMAN) {
				gamedrawpixal(x, y, human);
			}
			else if (map[x][y] == DOOR) {
				gamedrawpixal(x, y, door);
			}
		}
	}
	FlushBatchDraw();
}

void gamedrawpixal(specificpos *pos, COLORREF RGB) {
	setfillcolor(RGB); 
	setlinecolor(COLORREF RGB(0, 0, 0));
	fillrectangle(pos->x * BLOCK_XY, pos->y * BLOCK_XY, BLOCK_XY + pos->x * BLOCK_XY, BLOCK_XY + pos->y * BLOCK_XY);
}
void gamedrawpixal(int x, int y, COLORREF RGB) {
	setfillcolor(RGB); 
	setlinecolor(COLORREF RGB(0, 0, 0));
	fillrectangle(x * BLOCK_XY, y * BLOCK_XY, BLOCK_XY + x * BLOCK_XY, BLOCK_XY + y * BLOCK_XY);
}
bool checkover() {
	if(map[MAPROW-2][MAPCOL-2]==HUMAN)
	{
		return false;//游戏结束
	}
	else
		return true;//游戏没结束
	
}
void move(specificpos*pos)
{

	int x = pos->x;
	int y = pos->y;
	int spr = pos->spr;
	while (checkover()) {
		//读取按键输入的信息
		switch (_getch()) {
		case'w':
		case'W':
		case 72:
			pos->spr = UP;
			break;
		case's':
		case'S':
		case 80:
			pos->spr = DOWN;
			break;
		case'a':
		case'A':
		case 75:
			pos->spr = LEFT;
			break;
		case'd':
		case'D':
		case 77:
			pos->spr = RIGHT;
			break;
		}

		//进行行走
		specificpos next = *pos;
		switch (pos->spr)
		{
		case RIGHT:
			next.x++;
			break;
		case LEFT:
			next.x--;
			break;
		case UP:
			next.y--;
			break;
		case DOWN:
			next.y++;
			break;
		}
		switch (map[next.x][next.y]) {
		case WALL:
			next.x = pos->x;
			next.y = pos->y;//不变
			break;
		case ROAD:
			map[pos->x][pos->y] = ROAD;
			map[next.x][next.y] = HUMAN;
			break;
		case DOOR:
			map[pos->x][pos->y] = ROAD;
			map[next.x][next.y] = HUMAN;
			break;
		}
		*pos = next;
		display();
	}
}
int main() {
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();//开始批量绘图
	cleardevice();//清空显示
	mapinit();//地图初始化
	specificpos firstpos{ 0,0 };
	move(&firstpos);
	


	while (1);

	

}