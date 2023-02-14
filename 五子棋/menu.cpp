#include"wuziqi.h"

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
int judge() {

	int winner = 0;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 19; j++) {
			for (int direction = 1; direction < 5; direction++)
			{
				int number = count(i, j, direction);
				if (number >= 6)
				{
					winner = qp[j][i];
					return winner;
				}

			}
		}
	}
	return winner;


}

