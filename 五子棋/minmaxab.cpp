#include"wuziqi.h"

//int flag = 0;//用于标记是否用于搜索,-1表示被下过了，1表示还没下，但会用于后续搜索,2表示搜索过了,3表示最优解
int findbest(int acolor, int depth, ab last) {
	ab now = last;
	int value = 0;
	int min = 100000000, max = -100000000;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++) {
			if (xyvalue[j][i].flag == 1)
			{
				if (depth == DEPTH) {//最后一层才开始估值
					value = evaluate(i, j,acolor);
					switch (acolor) {
					case -1:if (value < min)
					{
						min = value;

					}; break;
					case 1:
						if (value > max)
						{
							max = value;

						}; break;
					}


					if (firsttime == 0) {
						switch (acolor) {
						case -1:if (now.b > value) {//
							now.b = value;
							break;
						}
						case 1:if (now.a < value) {
							now.a = value;
							break;
						}
						}
					}



					if (now.a >= now.b) {
						bridge = now;
						goto out;
					}
					bridge = now;

				}

				else {
					qp[j][i] = acolor;//模拟
					xyvalue[j][i].flag = -1;
					/*if (int a = judge() != 0) {
						qp[j][i] = 0;
						xyvalue[j][i].flag = 1;//清空模拟
						if (depth == 2) {
							best.x = i; best.y = j;//只有最开始下的才会是可能下的地方
						}
						switch (acolor) {
						case -1:
							now.b = a * 10000000;
							break;
						
						case 1:
							now.a = a * 10000000;
							break;
						
						}
				
						bridge = now;
						return (a * 10000000);
					}*/
					value = findbest(-acolor, depth + 1, now);//（now是用于剪枝的，不知道起什么名字，）下一层搜索
					switch (acolor) {						  //一个大问题就是返回值是什么；我返回了一个不会影响min或max的值
					case -1:
						now.b = minormax(now.b, bridge.a, bridge.b, acolor);//发生剪枝后b不一定最小，还是要比

						break;

					case 1:
						now.a = minormax(now.a, bridge.a, bridge.b, acolor);
						break;

					}
					bridge = now;
					if (now.a >= now.b) {
						qp[j][i] = 0;
						xyvalue[j][i].flag = 1;
						goto out;
					}

					qp[j][i] = 0;
					xyvalue[j][i].flag = 1;//清空模拟

					switch (acolor) {
					case -1:
						if (value < min)
						{
							min = value;
							if (depth == 2) {
								best.x = i; best.y = j;//只有最开始下的才会是可能下的地方
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
					bridge = now;




				}
			}
		}
	}


	firstab(now, acolor, min, max);
	switch (acolor) {
	case -1:return min; break;
	case 1:return max; break;
	}

out:
	return value;


}



void firstab(ab now, int acolor, int min, int max) {
	if (firsttime == 1) {
		switch (acolor) {
		case -1:if (now.a < min)
		{
			now.a = min;

		}; break;
		case 1:
			if (now.b > max)
			{
				now.b = max;

			}; break;
		}



		bridge = now;

		firsttime = 0;
	}

}

int minormax(int a, int b, int c, int minormax) {
	int d;
	if (a > b) {
		d = a;
		a = b;
		b = d;
	}
	if (a > c) {
		d = a;
		a = c;
		c = d;
	}
	if (b > c) {
		d = b;
		b = c;
		c = d;
	}
	switch (minormax) {
	case -1:return a; //返回最小
	case 1:return c;//返回最大
	}

}
