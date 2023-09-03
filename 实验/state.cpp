

typedef struct place {
	int x;
	int y;
}place;

struct point {
	int state;
	long double a_value;
	long double d_value;
	place place;
};

int linkFive(point p1, point p2, point p3, point p4, point p5, int color) {//*****
	if (p1.state == p2.state &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color) return 1;
	return 0;
}

int liveFour(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//_****_
	if (p1.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color) return 1;
	return 0;
}

int rushFour1(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//ememy a****
	if ((p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p1.state == 0 &&
		p6.state == -color) ||
		(p2.state == p3.state &&
			p3.state == p4.state &&
			p4.state == p5.state &&
			p5.state == color &&
			p6.state == 0 &&
			p1.state == -color)) return 1;
	return 0;
}
int rushFour2(point p1, point p2, point p3, point p4, point p5, int color) {//no enemy *_***
	if ((p1.state == p2.state &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p4.state == 0) ||
		(p1.state == p4.state &&
			p4.state == p3.state &&
			p3.state == p5.state &&
			p5.state == color &&
			p2.state == 0)) return 1;
	if ((p1.state == p2.state &&
		p2.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p3.state == 0)) return 1;
	return 0;
}

int linkThree1(point p1, point p2, point p3, point p4, point p5, int color) {//_***_
	if (p1.state == p5.state &&
		p5.state == 0 &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == color) return 1;
	return 0;
}

int linkThree2(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//_**_*_ ||_*_**_
	if ((p1.state == p4.state &&
		p4.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color) ||
		(p1.state == p3.state &&
			p3.state == p6.state &&
			p6.state == 0 &&
			p2.state == p4.state &&
			p4.state == p5.state &&
			p5.state == color)) return 1;
	return 0;
}

int sleepThree1(point p1, point p2, point p3, point p4, point p5, int color)//no enemy *__**||**__*||*_*_* 
{
	if (p1.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p2.state == p3.state &&
		p3.state == 0) return 1;
	if (p1.state == p2.state &&
		p2.state == p5.state &&
		p5.state == color &&
		p3.state == p4.state &&
		p4.state == 0) return 1;
	if (p1.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p2.state == p4.state &&
		p4.state == 0) return 1;
	return 0;
}
int sleepThree2(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//enemy
	if (p1.state == p2.state &&
		p2.state == 0 &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p6.state == -color)return 1;//__***a
	if (p5.state == p6.state &&
		p6.state == 0 &&
		p3.state == p4.state &&
		p4.state == p2.state &&
		p2.state == color &&
		p1.state == -color)return 1;//a***__
	return 0;
}

int sleepThree3(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//enemy
	if (p1.state == p3.state &&
		p3.state == 0 &&
		p2.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p6.state == -color)return 1;//_*_**a
	if (p4.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p1.state == -color)return 1;//a**_*_
	if (p1.state == p4.state &&
		p4.state == 0 &&
		p2.state == p3.state &&
		p3.state == p5.state &&
		p5.state == color &&
		p6.state == -color)return 1;//_**_*a
	if (p3.state == p6.state &&
		p6.state == 0 &&
		p2.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color &&
		p1.state == -color)return 1;//a*_**_
	return 0;
}

int sleepThree4(point p1, point p2, point p3, point p4, point p5, point p6, point p7, int color) {//enemy a_***_a
	if (p1.state == p7.state &&
		p2.state == -color &&
		p2.state == p6.state &&
		p6.state == 0 &&
		p3.state == p4.state &&
		p4.state == p5.state &&
		p5.state == color)return 1;
	return 0;
}

int liveTwo1(point p1, point p2, point p3, point p4, int color) {//*__*
	if (p1.state == p4.state &&
		p4.state == color &&
		p2.state == p3.state &&
		p3.state == 0) return 1;
	return 0;
}

int liveTwo2(point p1, point p2, point p3, point p4, point p5, int color) {//_*_*_
	if (p1.state == p3.state &&
		p3.state == p5.state &&
		p5.state == 0 &&
		p2.state == p4.state &&
		p4.state == color) return 1;
	return 0;
}

int liveTwo3(point p1, point p2, point p3, point p4, point p5, point p6, int color) {//__**__
	if (p1.state == p2.state &&
		p2.state == p5.state &&
		p5.state == p6.state &&
		p6.state == 0 &&
		p3.state == p4.state &&
		p4.state == color) return 1;
	return 0;
}

int sleepTwo1(point p1, point p2, point p3, point p4, point p5, int color) {//*___*
	if (p1.state == p5.state &&
		p5.state == color &&
		p2.state == p3.state &&
		p3.state == p4.state &&
		p4.state == 0) return 1;
	return 0;
}

int sleepTwo2(point p1, point p2, point p3, point p4, point p5, point p6, int color) {
	if (p1.state == p2.state &&
		p2.state == p3.state &&
		p3.state == 0 &&
		p5.state == p4.state &&
		p4.state == color &&
		p6.state == -color) return 1;//___**a
	if (p4.state == p5.state &&
		p5.state == p6.state &&
		p6.state == 0 &&
		p2.state == p3.state &&
		p2.state == color &&
		p1.state == -color) return 1;//a**___
	if (p1.state == p2.state &&
		p2.state == p4.state &&
		p4.state == 0 &&
		p5.state == p3.state &&
		p5.state == color &&
		p6.state == -color) return 1;//__*_*a
	if (p5.state == p6.state &&
		p6.state == p3.state &&
		p3.state == 0 &&
		p2.state == p4.state &&
		p4.state == color &&
		p1.state == -color) return 1;//a*_*__
	if (p1.state == p3.state &&
		p3.state == p4.state &&
		p4.state == 0 &&
		p5.state == p2.state &&
		p2.state == color &&
		p6.state == -color) return 1;//_*__*a
	if (p3.state == p4.state &&
		p4.state == p6.state &&
		p6.state == 0 &&
		p2.state == p5.state &&
		p5.state == color &&
		p1.state == -color) return 1;//a*__*_
	return 0;
}

int Max(int a, int b) {
	if (a > b) return a;
	return b;
}
int Min(int a, int b) {
	if (a < b) return a;
	return b;
}