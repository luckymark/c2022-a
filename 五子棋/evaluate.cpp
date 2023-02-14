#include"wuziqi.h"

int getscore() {
	int sum = 0;
	int count2 = 100, count3 = 1000, count4 = 100000, count5 = 10000000;

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 19; j++) {
			for (int direction = 1; direction < 5; direction++)
			{
				int number = count(i, j, direction);
				switch (number) {
				case 2:sum += qp[j][i] * count2; break;//活二，赌三，死四
				case 3:sum += qp[j][i] * count3; break;//活三
				case 4:sum += qp[j][i] * count4; break;//只有赌四才是这个评方
				case 5:sum += qp[j][i] * count4; break;
				case 6: sum += qp[j][i] * count5;  break;//以下三个全为连5的
				case 7: sum += qp[j][i] * count5;  break;
				case 8: sum += qp[j][i] * count5;	 break;
				default:break;
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
		while (ay < len && ax < len && qp[ay][ax] == qp[y][x]&&count<6) {
			ay += yc;
			ax += xc;
			count++;
		}
		if (count == 5)//连五
		{
			count += 3;
			
		}
		if (count == 4)
		{
			count += 1;
		}
		if (qp[ay][ax] != 0) {
			count--;
		}
		if (y - yc < len && x - xc < len && y < len && x < len) {
			if (qp[y - yc][x - xc] == -qp[y][x]) {
				count--;
			}
		}
	}
	return count;
}
int evaluate(int x, int y,int acolor) {

	qp[y][x] = acolor;
	int sumvalue = qpvalue[y][x] * acolor;
	sumvalue += getscore();
	qp[y][x] = 0;
	return sumvalue;

}