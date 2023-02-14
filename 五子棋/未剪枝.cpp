#include <graphics.h>
#include <conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<mmsystem.h>
#include<time.h>
#include<Windows.h>
//#programe  cocolcolent(lib,"winmm.lib")


typedef struct positionandvalue {
	int x= 0, y = 0;
	int value = 0;
	int flag = 0;//用于标记是否用于搜索,-1表示被下过了，1表示还没下，但会用于后续搜索,2表示搜索过了,3表示最优解
}p;
enum{len=19};


int bc = 41;//biangchang（边长）
const int DEPTH = 4;



IMAGE a;
int color = 1, flag = 1;//白为1，黑为-1
int qp[len][len] = { 0 };//棋盘是19*19的
int qpvalue[len][len] = {
0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0,
1,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4,3,2,1,
2,3,4,5,6,7,8,9,10,11,10,9,8,7,6,5,4,3,2,
3,4,5,6,7,8,9,10,11,12,11,10,9,8,7,6,5,4,3,
4,5,6,7,8,9,10,11,12,13,12,11,10,9,8,7,6,5,4,
5,6,7,8,9,10,11,12,13,14,13,12,11,10,9,8,7,6,5,
6,7,8,9,10,11,12,13,14,15,14,13,12,11,10,9,8,7,6,
7,8,9,10,11,12,13,14,15,16,15,14,13,12,11,10,9,8,7,
8,9,10,11,12,13,14,15,16,17,16,15,14,13,12,11,10,9,8,
9,10,11,12,13,14,15,16,17,18,17,16,15,14,13,12,11,10,9,
8,9,10,11,12,13,14,15,16,17,16,15,14,13,12,11,10,9,8,
7,8,9,10,11,12,13,14,15,16,15,14,13,12,11,10,9,8,7,
6,7,8,9,10,11,12,13,14,15,14,13,12,11,10,9,8,7,6,
5,6,7,8,9,10,11,12,13,14,13,12,11,10,9,8,7,6,5,
4,5,6,7,8,9,10,11,12,13,12,11,10,9,8,7,6,5,4,
3,4,5,6,7,8,9,10,11,12,11,10,9,8,7,6,5,4,3,
2,3,4,5,6,7,8,9,10,11,10,9,8,7,6,5,4,3,2,
1,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4,3,2,1,
0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0,





};

p xyvalue[len][len];
p best;//最好的位

int step = 0;
int getposition();
void draw_piece(int x, int y);
int judge();
void endgame();
void init();
void findblank();
int evaluate(int x, int y);
void fillblank();
void aidraw();
int getscore();
int count(int x, int y,  int direction);
int findbest(int acolor, int depth);
void qpevaluate();


int main()
{
	init();

	while (1) {
		if (color ==1) {
		getposition();//画出人类玩家的棋子
		int con = judge();
		if (con != 0) {
			endgame();
			return 0;

		}
	}


		if (color == -1)
	{



			aidraw();
			int con = judge();
			if (con != 0) {
				endgame();
				return 0;

			}
		}
	}
}

int  getposition() {
	int complete = 0;
	ExMessage col;
	col = getmessage(EX_MOUSE | EX_KEY);
	if (col.lbutton == 1) {
		int x = col.x / bc;
		int y = col.y / bc;
		draw_piece(x, y);
		complete = 1;


	}
	while (col.lbutton == 1) {
		col = getmessage(EX_MOUSE);


	}
	return complete;
}
int judge() {

	int value = 0;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 19; j++) {
			for (int direction = 1; direction < 5; direction++)
			{
				int number = count(i, j,direction);
				if (number>=5)
				{
					value = qp[j][i];
					break;
				}
				
			}
		}
	}
	return value;


}

void init() {
	initgraph(796, 796);
	loadimage(&a, _T("background.jpg"));
	putimage(0, 0, &a);
	//muciSendString(_T("open backcol.colp3"), NULL, 0, NULL);
	//muciSendString(_T("play backcol.colp3"), NULL, 0, NULL);

}
void aidraw() {
	findblank();
	fillblank();

}
void findblank() {
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++) {
			if (qp[j][i] != 0) {
				for (int a = -2; a < 3; a++)
				{
					for (int b = -2; b < 3; b++) {
						if (xyvalue[j + a][i + b].flag !=-1)
						{
							xyvalue[j + a][i + b].flag = 1;



						}

					}

				}
			}

		}


	}
}
void qpevaluate() {
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++) {
			if ((xyvalue[j][i].flag == 1)&&(qp[j][i]==0))
			{	
				xyvalue[j][i].value = evaluate(i, j);

			}
		}

	}
}

void fillblank() {
	findbest(color,2);
	draw_piece(best.x, best.y);
}



int evaluate(int x, int y) {

	qp[y][x] = color;
	int sumvalue = qpvalue[y][x] * color;
	sumvalue += getscore();
	qp[y][x] = 0;
	return sumvalue;

}






//int flag = 0;//用于标记是否用于搜索,-1表示被下过了，1表示还没下，但会用于后续搜索,2表示搜索过了,3表示最优解
int findbest(int acolor, int depth) {//没有模拟下子
	int value=0;
	int min = 100000000, max = -100000000;
	findblank();
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++) {
			if (xyvalue[j][i].flag == 1)
			{
				if (depth == DEPTH) {
					value = evaluate(i, j);
					switch (acolor) {
					case -1:if (value <min)
					{
						min=value;
						
					}; break;
					case 1:
						if (value>max)
						{
							max = value;
							
						}; break;
					}

				}
				else {
					qp[j][i] = acolor;
					xyvalue[j][i].flag = -1;
					value=findbest( -acolor, depth + 1);
					qp[j][i] = 0;
					xyvalue[j][i].flag = 0;
					switch (acolor) {
					case -1:
						if (value < min)
					{
						min=value;
						if (depth == 2) {
							best.x = i; best.y = j;
						}
					}; break;
					case 1:
						if (value > max)
						{
							max = value;
							if (depth == 2) {
								best.x = i; best.y = j;
							}
							
						}; break;
					}	
				}
			}
		}
	}

	switch (acolor) {
	case -1:return min; break;
	case 1:return max; break;
	}
	
	

}









/*void fillblank() {
	int x = 0;
	int y = 0;




	qpevaluate(qp);
	int min = 1000000, max = 0;
	if (color == -1) {//这个if是为了以后换成白子也可以
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < len; j++) {
				if (xyvalue[i][j].flag == 1) {
					if (xyvalue[i][j].value < min)
					{
						min = xyvalue[i][j].value;
						best.y = i;
						best.x = j;

					}


				}

			}
		}
	}
	draw_piece(best.x, best.y);




}*/
int getscore() {
	int sum = 0;
	int count2 = 100, count3 = 1000, count4 = 100000, count5 = 1000000;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 19; j++) {
			for (int direction = 1; direction < 5; direction++)
			{
				int number = count(i, j, direction);
				switch (number) {
				case 2:sum += qp[j][i] * count2; break;
				case 3:sum += qp[j][i] * count3; break;
				case 4:sum += qp[j][i] * count4; break;
				case 5:sum += qp[j][i] * count5; break;
				case 6:sum += qp[j][i] * count5; break;
				case 7:sum += qp[j][i] * count5; break;
				}
			}
		}
	}

	return sum;

}
int count(int x, int y, int direction) {
	int xc = 0, yc = 0, count = 0;
	switch (direction) {
	case 1:xc = 1; yc = 0; break;//向右
	case 2:xc = 0; yc = 1; break;//向下
	case 3:xc = 1; yc = 1; break;//右下
	case 4:xc = 1; yc = -1; break;//右上
	}

	if (qp[y][x] != 0)
	{
		int ay = y, ax = x;
		while (qp[ay][ax] == qp[y][x] && ay < len && ax < len) {
			ay += yc;
			ax += xc;
			count++;
		}
		if (count == 5)
		{
			count += 2;
		}
		if (qp[ay][ax] != 0) {
			count--;
		}
		if (qp[y - yc][x - xc] == -qp[y][x]) {
			count--;
		}
	}
	return count;
}
void endgame() {
	Sleep(1000);
	closegraph();
	if (color == -1) {
		printf("白胜\n");

	}
	else {
		printf("黑胜\n");
	}
	printf("用了%d步", step);

}
void draw_piece(int x, int y) {

	switch (color) {
	case -1:setfillcolor(BLACK); break;

	case 1:setfillcolor(WHITE); break;
	}
	int r = 20;
	if (qp[y][x] == 0) {
		qp[y][x] = color;
		xyvalue[y][x].flag = -1;


		y = y * bc + 28;//28是距离边界的长度
		x = x * bc + 28;
		fillcircle(x, y, r);
		color = -color;

		step++;
	}
}