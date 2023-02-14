#define X 40
#define Y 20
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
enum {kong = 0, qiang = 1, zhongdian = 2, ren = 3, xiangzi = 4};

typedef struct position {
	int x;
	int y;
} p;
void move(p* nowp, char direction, int a[][X], int kind);
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


	//造人和终点和箱子
	p p1, p2, p3;
	p *renp = &p1, *zhongdianp = &p2, *xiangzip = &p3;
	int kind;
	kind = ren;
	creat(kind, a, renp);
	kind = zhongdian;
	creat(kind, a, zhongdianp);
	kind = xiangzi;
	creat(kind, a, xiangzip);



	p*nowp = renp;
	draw(a);
	int key;
	while (1) {
		system("cls");
		draw(a);
		key = getch();
		kind = ren;
		move(nowp, key, a, kind);
		if ((nowp->x == zhongdianp->x) && (nowp->y == zhongdianp->y)) {
			printf("you win");
			break;
		}
	}


}

void move(p* nowp, char direction, int a[][X], int kind) {
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
	if (a[nextp.y][nextp.x] == 4) {
		kind = xiangzi;
		move(&nextp, direction, a, kind);
		nowp = &nextp;

	}

	if ((a[nextp.y][nextp.x]) == 0) {
		a[nextp.y][nextp.x] = kind;
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
				case 4:
					printf("$");
					break;
			}

		}
		printf("\n");
	}
}

