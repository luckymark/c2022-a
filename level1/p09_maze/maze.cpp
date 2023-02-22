#include"maze.h"
void mapinit() {
	/*��ͼ��ʼ��Ϊǽ*/
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
	//ѡ��һ��Ϊ·
	map[0][0] = ROAD;
	specificpos firstpos{0,0};
	judgewait(&firstpos);
	prime_main();
	map[0][0] = HUMAN;//���������
	map[MAPROW - 2][MAPCOL - 2] = DOOR;
	map[MAPROW - 1][MAPCOL - 2] = DOOR;
	FlushBatchDraw();//�ͷŻ�ͼ��Ŀ����ȡ����˸
	display();
}

void judgewait(specificpos *pos) {
	//�ж�����
	if ((pos->y - 2) >= 0 && map[pos->x][pos->y - 2] ==WALL ) {
		specificpos* waitpos = new specificpos(pos->x, pos->y - 2);
		//�����Ǿ�����������д(malloc�����Ϊ����)��specificpos* waitpos = (specificpos*)malloc(sizeof(specificpos*));waitpos={};
		WALLlist.push_back(waitpos);
		map[pos->x][pos->y - 2] = WAIT;
	}
	//�ж�����
	if ((pos->y + 2) <=MAPCOL-1 && map[pos->x][pos->y + 2] == WALL) {
		specificpos* waitpos = new specificpos(pos->x, pos->y + 2);
		//�����Ǿ�����������д��specificpos* waitpos = (specificpos*)malloc(sizeof(specificpos*));waitpos={};
		WALLlist.push_back(waitpos);
		map[pos->x][pos->y + 2] = WAIT;
	}
	//�ж�����
	if (pos->x - 2 >= 0 && map[pos->x - 2][pos->y] == WALL)
	{
		specificpos* waitpos = new specificpos(pos->x - 2, pos->y);
		WALLlist.push_back(waitpos);
		map[pos->x - 2][pos->y] = WAIT;
	}
	//�ж�����
	if (pos->x + 2 <= MAPROW-1 && map[pos->x + 2][pos->y] == WALL)
	{
		specificpos* waitpos = new specificpos(pos->x + 2, pos->y);
		WALLlist.push_back(waitpos);
		map[pos->x + 2][pos->y] = WAIT;
	}
}

void through(specificpos* pos) {
	ROADlist.clear();
	//�ж�����
	if ((pos->y - 2) >= 0 && map[pos->x][pos->y - 2] == ROAD) {
		specificpos* roadpos = new specificpos(pos->x, pos->y - 1);
		ROADlist.push_back(roadpos);
	}
	//�ж�����
	if ((pos->y + 2) <= MAPCOL-1 && map[pos->x][pos->y + 2] == ROAD) {
		specificpos* roadpos = new specificpos(pos->x, pos->y + 1);
		ROADlist.push_back(roadpos);
	}
	//�ж�����
	if (pos->x - 2 >= 0 && map[pos->x - 2][pos->y] == ROAD)
	{
		specificpos* roadpos = new specificpos(pos->x - 1, pos->y);
		ROADlist.push_back(roadpos);
	}
	//�ж�����
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
		//���һ��λ�ý�waitת��Ϊroad
		int primenum = rand() % WALLlist.size();
		specificpos* roadpos = WALLlist[primenum];

		through(roadpos);//��ͨ��·��֮���ǽ��

		map[roadpos->x][roadpos->y] = ROAD;//�Ѵ�ѡ���Ϊ·��
		
		judgewait(roadpos);//�����µĴ�ѡ��

		WALLlist.erase(WALLlist.begin() + primenum);//�����·���ǽ��ɾ��
		
		//��ʼ��ͼ
		gamedrawpixal(roadpos, xuanzhong);
		FlushBatchDraw();//Ŀ����ȡ����˸
		display();
	}
	WALLlist.clear();
}

//��������λ�ã���block_width*block_height������
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
		return false;//��Ϸ����
	}
	else
		return true;//��Ϸû����
	
}
void move(specificpos*pos)
{

	int x = pos->x;
	int y = pos->y;
	int spr = pos->spr;
	while (checkover()) {
		//��ȡ�����������Ϣ
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

		//��������
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
			next.y = pos->y;//����
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
	BeginBatchDraw();//��ʼ������ͼ
	cleardevice();//�����ʾ
	mapinit();//��ͼ��ʼ��
	specificpos firstpos{ 0,0 };
	move(&firstpos);
	


	while (1);

	

}