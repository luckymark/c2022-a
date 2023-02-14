#define X 40
#define Y 20
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
enum {kong = 0, qiang = 1, zhongdian = 2, ren = 3};

typedef struct position {
	int x;
	int y;
} p;
void move(p* nowp, char direction, int a[][X]);
void creat(int kind, int a[Y][X], p* pos);
void draw(int a[Y][X]);
void creatroad(p* renp, p* zhongdianp, int a[Y][X]);


int main() {
	srand(time(NULL));
	int a[Y][X];
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			a[j][i] = 0;
		}
	}


	//造墙
	for (int i = 0; i < X; i++) {
		a[0][i] = 1;
		a[Y - 1][i] = 1;
	}
	for (int i = 0; i < Y; i++) {
		a[i][0] = 1;
		a[i][X - 1] = 1;
	}


	//造人和终点
	p p1, p2;
	p *renp = &p1, *zhongdianp = &p2;
	int kind;
	kind = ren;
	creat(kind, a, renp);
	kind = zhongdian;
	creat(kind, a, zhongdianp);



	//多造几个墙
	kind = 1;
	p p3;
	p *p4 = &p3;
	for (int i = 0; i < 250; i++) {
		creat(kind, a, p4);
	}
	creatroad(renp, zhongdianp, a);

	p *nowp = renp;
	char key;
	while (1) {
		system("cls");
		draw(a);
		key = getch();
		move(nowp, key, a);
		if ((nowp->x == zhongdianp->x) && (nowp->y == zhongdianp->y)) {
			printf("you win");
			break;
		}
	}


}

void move(p* nowp, char direction, int a[][X]) {
	p nextp;
	nextp.x = 0;
	nextp.y = 0;
	switch (direction) {
		case 'w':
			nextp.x = nowp->x;
			nextp.y = (nowp->y) - 1;
			break;
		case 'a':
			nextp.x = (nowp->x) - 1;
			nextp.y = nowp->y;
			break;
		case 's':
			nextp.x = nowp->x;
			nextp.y = (nowp->y) + 1;
			break;
		case 'd':
			nextp.x = (nowp->x) + 1;
			nextp.y = nowp->y;
			break;


	}
	if ((a[nextp.y][nextp.x]) != 1) {
		a[nextp.y][nextp.x] = 3;
		a[nowp->y][nowp->x] = 0;
		*nowp = nextp;
	}

}
void creat(int kind, int a[Y][X], p* pos) {
	int x1, y1;
	do {

		x1 = rand() % 40;
		y1 = rand() % 20;
	} while (a[y1][x1] != 0);
	a[y1][x1] = kind;
	pos->x = x1;
	pos->y = y1;





}
void draw(int a[Y][X]) {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			switch (a[i][j]) {
				case 0:
					printf(" ");
					break;
				case 1:
					printf("#");
					break;
				case 2:
					printf("!");
					break;
				case 3:
					printf("*");
					break;
			}

		}
		printf("\n");
	}
}

void creatroad(p* renp, p* zhongdianp, int a[Y][X]) {
	int dx, dy;
	int con;
	int conx = -1;
	int cony = -1;
	p p5;
	p *roadp = &p5;
	roadp->x = renp->x;
	roadp->y = renp->y;
	dx = (roadp->x) - (zhongdianp->x);
	if (dx < 0) {
		dx = -dx;
		conx = 1;
	}

	dy = (roadp->y) - (zhongdianp->y);
	if (dy < 0) {
		dy = -dy;
		cony = 1;
	}

	while ((dx + dy) > 0) {
		con = rand() % 2;
		if (dx == 0) {
			for (int i = 1; i < dy; i++) {
				roadp->y = (roadp->y) + cony;
				a[(roadp->y)][roadp->x] = 0;

			}
			break;
		}
		if (dy == 0) {
			for (int i = 1; i < dx; i++) {
				roadp->x = (roadp->x) + conx;
				a[roadp->y][(roadp->x)] = 0;

			}
			break;
		}
		switch (con) {
			case 0:
				roadp->x = (roadp->x) + conx;
				a[roadp->y][(roadp->x) ] = 0;
				dx--;

				break;

			case 1:
				roadp->y = (roadp->y) + cony;
				a[(roadp->y)][roadp->x] = 0;
				dy--;

				break;

		}


	}


}
