/*#五子棋
功能：普通五子棋规则，重新开始之后双方黑白棋互换，无禁手无时间限制，可以无条件无次数限制悔棋，没有落子提示，比如准备玩家下棋的时候鼠标位于交叉点附近没有落子的迹象
工具：使用了vs2019，标准库，easyx库以及时间库
模块划分：图形界面由easyx头文件的库函数实现。自定义了一个区域的标志，通过检测区域标志和鼠标映射到对应的反馈。定义两个二维数组，作为初级棋盘数据保存和次级棋盘数据保存，两者保证绝对的同步。初级棋盘保证能还原棋谱，次级棋盘用于判决函数。判决函数和画图界面函数分开写。如：定义下棋区域，鼠标位于下棋区域则按下鼠标画棋子。
效果评估：悔棋时候擦除部分画面重新画图，只改部分界面，达到不闪烁、高帧率的效果。整体程序模拟人的思路下棋，依照相连棋子个数为权重依次评判，若满足当前条件，判决函数输出当前位置，并且不再执行接下来的判决。暂时未添加双三等多维判决功能。实在是不会写递归函数，所以采用了把每个判决函数都写下来的方式，“教会”计算机判决。
棋力评价：大概位于刚了解规则的萌新水平，看不出来双三，但是知道了连着3个的要堵，剩下的随机下，使得看起来尽量像是人做出的随机选择
*/

#include <stdio.h>
#include <graphics.h>
#include <easyx.h>
#include <time.h>

void DrawQizi(int x, int y, bool* xianshou);
void RegretQizi(int x, int y);
int XifuGedian(int z);
void zhuanzhi(int* p); 
void qiufu(int*p);
int Win(int* q);
int Heng4(int* p);
int ZhengXie4(int* p);
int FuXie4(int* p);
int fenxi(int*p,int j,bool xianshou);
int C54(int* p);
int C53(int* p);
int Heng3(int* p);
int ZhengXie3(int* p);
int FuXie3(int* p);
int Si3(int* p);
int Heng3Si(int* p);
int ZhengXie3Si(int* p);
int FuXie3Si(int* p);
int C42(int* p);
int Heng2(int* p);
int ZhengXie2(int* p);
int FuXie2(int* p);
int suiji(int* p,bool xianshou);
int ZhengXie64(int* p);
int FuXie64(int* p);
int Heng64(int* p);
int C64(int* p);
const int GAP = 40;
int beginTime = 0;
int endTime = 0;
int main() {
	beginTime = clock();
	bool heibai = 0;
	initial:
	bool xianshou =0;
	//画棋盘
	int qipan[15][15] = { {0,}, };
	int zhuangtai[15][15] = { {0,}, };
	initgraph(960, 720, NULL);
	setbkcolor(RGB(252,176,64));
	cleardevice();
	setlinecolor(RGB(0,0,0));
	for (int i = 1; i < 16;i++) {
		line(GAP * 1, GAP *i,GAP*15,GAP*i );
	}
	for (int i = 1; i < 16; i++) {
		line(GAP * i, GAP * 1, GAP * i, GAP *15);
		}
	settextstyle(40,0, ANSI_CHARSET);
	settextcolor(RGB(0, 0, 0));
	TCHAR REGRET[] = L"regret";
	outtextxy(800, 500, REGRET);
	TCHAR RESTART[] = L"restart";
	outtextxy(800,600,RESTART);
	TCHAR AI[] = L"AI";
	TCHAR ME[] = L"ME";
	rectangle(775,500,775+150,550);
	rectangle(775, 600, 775 + 150, 650);
	int x = 0;
	int y = 0;
	int j = 0;
	int location = 0;
	ExMessage m;
	heibai = !heibai;
	if (heibai) {
		qipan[7][7] = ++j;
		zhuangtai[7][7] = (j%2);
		DrawQizi(8*GAP, 8*GAP, &xianshou);
	}
	outtextxy(800, 200, AI);
	outtextxy(800, 250, ME);
	DrawQizi(19 * GAP, 270, &xianshou);
	DrawQizi(19*GAP, 220, &xianshou);
	while (true)
	{
		getmessage(&m,1);
		if(m.message==WM_LBUTTONDOWN){
			x = XifuGedian(m.x) * GAP;
			y = XifuGedian(m.y) * GAP;
			if ((x * y) &&(!qipan[XifuGedian(m.y)-1][XifuGedian(m.x)-1])) {
				qipan[XifuGedian(m.y) - 1][XifuGedian(m.x) - 1] = ++j;//注意这里的数组转置，应该是第一个是y，第二个是x，第一个数组实际上写错了
				if (j%2==0) {
					zhuangtai[XifuGedian(m.y) - 1][XifuGedian(m.x) - 1] = -1;
				}
				else {
					zhuangtai[XifuGedian(m.y) - 1][XifuGedian(m.x) - 1] = 1;
				}
				DrawQizi(x, y,&xianshou);
				if ((Win((int*)&qipan)!=-1)) {
					goto final;
				}
				location=fenxi((int*)&zhuangtai,j,xianshou);
				x = (location / 15+1)*GAP;
				y = (location % 15+1)*GAP;
				qipan[location / 15][location % 15] =++j;
				if ((j % 2) == 0) {
					zhuangtai[location / 15][location % 15] = -1;
				}
				else {
					zhuangtai[location / 15][location % 15] = 1;
				}
				DrawQizi(y, x, &xianshou);
				if ((Win((int*)&qipan) != -1)) {
					goto final;
				}
			}
			else if ((m.x>775)&&(m.x<(775+150))) {
				if ((m.y>500)&&(m.y<550)) {
					j = j - 2;
					for (int i = 0; i < 225; ++i) {
						if ((qipan[i % 15][i / 15] == j + 1)||(qipan[i % 15][i / 15] == j + 2)) {
							qipan[i % 15][i / 15] = 0;
							zhuangtai[i % 15][i / 15] = 0;
							RegretQizi((i / 15 + 1) * GAP, (i % 15 + 1) * GAP);
						}
					}
					
				}
				if ((m.y > 600) && (m.y < 650)) {
					xianshou = !xianshou;
					goto initial;
				}
			}	
		}
	}	
	final:
	TCHAR WIN[] = L"WIN";
	outtextxy(800, 400, WIN);
	while (true)
	{
		getmessage(&m, 1);
		if (m.message == WM_LBUTTONDOWN) {
			if ((m.x > 775) && (m.x < (775 + 150))) {
				if ((m.y > 600) && (m.y < 650)) {
					xianshou = !xianshou;
					goto initial;
				}
			}
		}
	}
	return 0;
}
void DrawQizi(int x,int y,bool *xianshou) {
	setfillcolor(RGB(((int)(*xianshou))*255, ((int)(*xianshou))*255, ((int)(*xianshou))*255));
	fillcircle(x,y,10);
	(*xianshou) = !(*xianshou);
}
void RegretQizi(int x,int y) {
	setfillcolor(RGB(252, 176, 64));
	solidrectangle(x-15,y-15,x+15,y+15);
	line(x-15,y,x+15,y);
	line(x, y - 15, x , y+ 15);
}
int XifuGedian(int z) {
	int mod = 0;
	if ((z> (GAP-15))&&(z<(15* GAP+15))&&((z+15)%GAP<=30)) {
		mod = (z + 15) / GAP;
	}
	return mod;
}
int Win(int* q) {
	int back = -1;
	int p[15][15] = { {0,} ,};
	for (int l = 0; l < 15; ++l) {
		for (int k = 0; k < 15; ++k) {
			p[l][k] = *(q+15*l+k);
		}
	}
	for (int m = 0; m < 2;++m) {
		for (int l = 0; l < 15;++l) {
			for (int k = 0; k < 11; ++k) {
				if ((p[l][k] != 0)&& (p[l][k+1] != 0)&& (p[l][k+2] != 0)&& (p[l][k+3] != 0)&& (p[l][k+4] != 0)) {
					if ((p[l][k] %2== 0) && (p[l][k + 1] %2== 0) && (p[l][k + 2] %2== 0) && (p[l][k + 3] %2== 0) && (p[l][k + 4] %2== 0)) {
						back = 0;
					}
					if ((p[l][k] % 2 == 1) && (p[l][k + 1] % 2 == 1) && (p[l][k + 2] % 2 == 1) && (p[l][k + 3] % 2 == 1) && (p[l][k + 4] % 2 == 1)) {
						back = 1;
					}
				}
			}
		}
		zhuanzhi((int *)&p);
	}
	for (int l = 0; l < 11; ++l) {
		for (int k = 0; k <11; ++k) {
			if ((p[l][k] != 0) && (p[l + 1][k + 1] != 0) && (p[l + 2][k + 2] != 0) && (p[l + 3][k + 3] != 0) && (p[l + 4][k + 4] != 0)) {
				if ((p[l][k] % 2 == 0) && (p[l + 1][k + 1] % 2 == 0) && (p[l + 2][k + 2] % 2 == 0) && (p[l + 3][k + 3] % 2 == 0) && (p[l + 4][k + 4] % 2 == 0)) {
					back = 0;
				}
				if ((p[l][k] % 2 == 1) && (p[l + 1][k + 1] % 2 == 1) && (p[l + 2][k + 2] % 2 == 1) && (p[l + 3][k + 3] % 2 == 1) && (p[l + 4][k + 4] % 2 == 1)) {
					back = 1;
				}
			}
			if ((p[l+4][k] != 0) && (p[l + 3][k + 1] != 0) && (p[l + 2][k + 2] != 0) && (p[l + 1][k + 3] != 0) && (p[l ][k + 4] != 0)) {
				if ((p[l+4][k] % 2 == 0) && (p[l + 3][k + 1] % 2 == 0) && (p[l + 2][k + 2] % 2 == 0) && (p[l + 1][k + 3] % 2 == 0) && (p[l ][k + 4] % 2 == 0)) {
					back = 0;
				}
				if ((p[l+4][k] % 2 == 1) && (p[l + 3][k + 1] % 2 == 1) && (p[l + 2][k + 2] % 2 == 1) && (p[l + 1][k + 3] % 2 == 1) && (p[l][k + 4] % 2 == 1)) {
					back = 1;
				}
			}
		}
	}
	return back;
}
	//第一判决函数：为了保证不会输：死四活三，双三
	//我方有4个的时候一定要连到5个，优先级最高；对方。。。同我方，优先级仅仅低于我方同情况
	//
	//禁手：附近3个位置内有同行的两个活的就要下那里，优先级次高//4选2如-1010101-
	//
	//同禁手，但是只有1个活的
	// 
	//活3
	// 
	//对于每一个连着的5个位置，不能有3个同时为同一个颜色，先判断是否为空再判断颜色
void zhuanzhi(int* p) {
	int a = 0;
	for (int l = 0; l < 15; ++l) {
		for (int k = l; k < 15; ++k) {
			a = *(p + l * 15 + k);
			*(p + l * 15 + k) = *(p + k * 15 + l);
			*(p + k * 15 + l) = a;
		}
	}
}
void qiufu(int *p) {
	for (int l = 0; l < 15; ++l) {
		for (int k = 0; k < 15; ++k) {
			*(p + l * 15 + k) = -(*(p + l * 15 + k));
		}
	}
}
int Heng4(int *p) {
	int  c = -1;
	for (int m = 0; m < 15;++m) {
		for (int k = 0; k < 11;++k) {
			if (((*(p + 15 * m + k))+(*(p + 15 * m + k+1)) + (*(p + 15 * m + k+2)) + (*(p + 15 * m + k + 3))+(*(p + 15 * m + k + 4)))==4) {
				for (int i = 0; i < 5; ++i) {
					if (*(p + 15 * m + k + i) == 0) {
						c = 15 * m + k + i;
					}
				}
			}		
		}
	}
	return c;
}
int ZhengXie4(int* p) {
	int c = -1;
	for (int m = 0; m < 11; ++m) {
		for (int k = 0; k < 11; ++k) {
			if (((*(p + 15 * m + k)) + (*(p + 15 * (m + 1) + k + 1)) + (*(p + 15 * (m + 2) + k + 2)) + (*(p + 15 * (m + 3) + k + 3)) + (*(p + 15 * (m + 4) + k + 4))) == 4) {
				for (int i = 0; i < 5; ++i) {
					if (*(p + 15 * (m + i) + k + i) == 0) {
						c = 15 * (m + i) + k + i;
					}
				}
			}
		}
	}
	return c;
}
int FuXie4(int* p) {
	int c = -1;
	for (int m = 0; m < 11; ++m) {
		for (int k = 0; k < 11; ++k) {
			if (((*(p + 15 * m + k+4)) + (*(p + 15 * (m + 1) + k + 3)) + (*(p + 15 * (m + 2) + k + 2)) + (*(p + 15 * (m + 3) + k + 1)) + (*(p + 15 * (m + 4) + k))) == 4) {
				for (int i = 0; i < 5; ++i) {
					if (*(p + 15 * (m + i) + k + 4-i) == 0) {
						c = 15 * (m + i) + k + 4-i;
					}
				}
			}
		}
	}
	return c;
}
int fenxi(int* p, int j, bool xianshou) {
	int c = -1;
	int d = -1;
	d = C54(p);
	if (d != -1) {
		c = d;
	}
	else {
		//双三双四
		//死四活三
		// xoxoxox
		// 每次最好都要一个随机数
		//都没做
		d = C64(p);
		if (d != -1) {
			c = d;
			printf("C64(p)\n");
		}
		else {
			d = C53(p);
			if (d != -1) {
				c = d;
				printf("C53(p)\n");
			}
			else {
				d = Si3(p);
				if (d != -1) {
					c = d;
					printf("Si3(p)\n");
				}
				else {
					d = C42(p);
					if (d != -1) {
						c = d;
						printf("C42(p)\n");
					}
					else {
						d = suiji(p, xianshou);
						c = d;
						printf("随机\n");
					}

				}
			}
		}
	}
	printf("fenxi=%d %d\n",c/15,c%15);
	return c;
}
int C54(int* p) {
	int c = -1;
	for (int i = 0; i < 2; ++i) {qiufu(p);
		if (ZhengXie4(p)!=-1) {c = ZhengXie4(p);}
		if (FuXie4(p)!=-1) { c= FuXie4(p); }
		zhuanzhi(p);
		if (Heng4(p)!=-1) { c= (Heng4(p)/15)+(Heng4(p) % 15)*15; }
		zhuanzhi(p);
		if (Heng4(p)!=-1) { c = Heng4(p); }
		
	}
	return c;
}
int C53(int *p) {
	int c = -1;
	for (int i = 0; i < 2;++i) {qiufu(p);
		if (ZhengXie3(p)!=-1) { c = ZhengXie3(p); }
		if (FuXie3(p)!=-1) { c = FuXie3(p); }
		zhuanzhi(p);
		if (Heng3(p)!=-1) { c = (Heng3(p)/15)+(Heng3(p) % 15)*15; }
		zhuanzhi(p);
		if (Heng3(p)!=-1) { c = Heng3(p); }
	}
	return c;
}
int Heng3(int* p) {
	int  c = -1;
	for (int m = 0; m < 15; ++m) {
		for (int k = 0; k < 11; ++k) {
			if ((*(p + 15 * m + k)==0) && (*(p + 15 * m + k + 1)==1)&& (*(p + 15 * m + k + 2)==1) &&(*(p + 15 * m + k + 3)==1) && (*(p + 15 * m + k + 4)==0))  {
				endTime = clock();
				if ((endTime - beginTime) % 2 == 0) {
					c = 15 * m + k;
				}
				else { c = 15 * m + k + 4; }
			}
		}
	}
	return c;
}
int ZhengXie3(int* p) {
	int  c = -1;
	for (int m = 0; m < 11; ++m) {
		for (int k = 0; k < 11; ++k) {
			if ((*(p + 15 * m + k)==0) && (*(p + 15 * (m +1)+ k + 1)==1) && (*(p + 15 *( m +2)+ k + 2)==1) && (*(p + 15 *( m+3) + k + 3)==1) && (*(p + 15 * (m+4) + k + 4)==0)) {
				endTime = clock();
				if ((endTime - beginTime) % 2 == 0) {
						c = 15 * m+ k ;
					}else {
						c = 15 * (m +4)+ k + 4;
					}
			}
		}
	}
	return c;
}
int FuXie3(int* p) {
	int  c = -1;
	for (int m = 4; m < 15; ++m) {
		for (int k = 0; k < 11; ++k) {
			if ((*(p + 15 * m + k)==0) && (*(p + 15 * (m-1) + k + 1)==1) && (*(p + 15 * (m-2) + k + 2)==1) &&(*(p + 15 * (m-3) + k + 3)==1) &&(*(p + 15 * (m-4) + k + 4)==0))  {
				endTime = clock();
				if ((endTime - beginTime) % 2 == 0) {
					c = 15 * m+k;
				}
				else {
					c = 15 * (m - 4) + k + 4;
				}
			}
		}
	}
	return c;
}
int C64(int* p) {
	int c = -1;
	for (int i = 0; i < 2; ++i) {
		qiufu(p);
		if (ZhengXie64(p) != -1) { c = ZhengXie64(p); }
		if (FuXie64(p) != -1) { c = FuXie64(p); }
		zhuanzhi(p);
		if (Heng64(p) != -1) { c = (Heng64(p) / 15) + (Heng64(p) % 15) * 15; }
		zhuanzhi(p);
		if (Heng64(p) != -1) { c = Heng64(p); }
	}
	return c;
}
int Si3(int*p) {
	int c = -1;
	int d = -1;
	int q[15][15] = { {0,}, };
	for (int i = 0; i < 15 * 15; ++i) { *(&q[0][0] + i) = *(p + i); }
	for (int i = 0; i < 2; ++i) {qiufu(p);
	if (ZhengXie3Si(p) != -1) { c = ZhengXie3Si(p); *(&q[0][0] + c) = *(&q[0][0] + c) + 1; printf("Zhengxie\n"); }
		if (FuXie3Si(p)!=-1) { c = FuXie3Si(p); *(&q[0][0] + c) = *(&q[0][0] + c) + 1;	printf("Fuxie\n");
		}
		zhuanzhi(p);
		if (Heng3Si(p)!=-1) { c = (Heng3Si(p)/15)+(Heng3Si(p) % 15)*15; *(&q[0][0] + c) = *(&q[0][0] + c) + 1;	printf("heng1\n");
		}
		zhuanzhi(p);
		if (Heng3Si(p)!=-1) { c = Heng3Si(p); *(&q[0][0] + c) = *(&q[0][0] + c) + 1; printf("heng2\n");
		}
	}
printf("c=%d %d\n",c/15,c%15);
	return c;
}
int Heng3Si(int* p) {
	int  c =-1;
	for (int m = 0; m < 15; ++m) {
		for (int k = 0; k < 11; ++k) {
			if ((*(p + 15 * m + k + 1) == 1)&& (*(p + 15 * m + k + 2) == 1)&& (*(p + 15 * m + k + 3) == 1)) {
				if (((*(p + 15 * m + k ))* (*(p + 15 * m + k + 4))==0)&& ((*(p + 15 * m + k )) + (*(p + 15 * m + k + 4)) == -1)) {
					if ((*(p + 15 * m + k)) == 0) { c = 15 * m + k; }
					else { c = 15 * m + k + 4; }
				}
			}
		}
	}
	return c;
}
int ZhengXie3Si(int* p) {
	int  c = -1;
	for (int m = 0; m < 11; ++m) {
		for (int k = 0; k < 11; ++k) {
			if ((*(p + 15 * (m+1) + k + 1) == 1) && (*(p + 15 * (m+2) + k + 2) == 1) && (*(p + 15 * (m+3) + k + 3) == 1)) {
				if (((*(p + 15 * m + k)) * (*(p + 15 * (m+4) + k + 4)) == 0) && ((*(p + 15 * m + k)) + (*(p + 15 * (m +4)+ k + 4)) == -1)) {
						if (*(p + 15 * m + k) == 0) {
							c = 15 * m  + k ;
						}
						else {
							c = 15 * (m + 4) + k + 4;
						}
				}
			}
		}
	}
	return c;
}
int FuXie3Si(int* p) {
	int  c = -1;
	for (int m = 0; m < 11; ++m) {
		for (int k = 0; k < 11; ++k) {
			if ((*(p + 15 * (m - 1) + k + 1) == 1) && (*(p + 15 * (m - 2) + k + 2) == 1) && (*(p + 15 * (m - 3) + k + 3) == 1)) {
				if (((*(p + 15 * m + k)) * (*(p + 15 * (m - 4) + k + 4)) == 0) && ((*(p + 15 * m + k)) + (*(p + 15 * (m - 4) + k + 4)) == -1)) {
					if (*(p + 15 * m + k) == 0) {
						c = 15 * m + k;
					}
					else {
						c = 15 * (m - 4) + k + 4;
					}
				}
			}
		}
	}
	return c;
}
int C42(int *p) {
	int c = -1;
	for (int i = 0; i < 2; ++i) {qiufu(p);
		if (ZhengXie2(p)!=-1) { c = ZhengXie2(p); }
		if (FuXie2(p)!=-1) { c = FuXie2(p); }
		zhuanzhi(p);
		if (Heng2(p)!=-1) { c = (Heng2(p)/15)+(Heng2(p)%15)*15; }
		zhuanzhi(p);
		if (Heng2(p)!=-1) { c = Heng2(p); }
	}
	return c;
}
int Heng2(int* p) {
	int  c = -1;
	for (int m = 0; m < 15; ++m) {
		for (int k = 0; k < 11; ++k) {
			if (((*(p + 15 * m + k))==0)&& ((*(p + 15 * m + k+1))== 1)&& ((*(p + 15 * m + k+2)) == 1)&& ((*(p + 15 * m + k+3)) == 0)) {
				c = 15 * m + k;
			}
		}
	}
	return c;
}
int ZhengXie2(int*p) {
	int  c = -1;
	for (int m = 0; m < 11; ++m) {
		for (int k = 0; k < 11; ++k) {
			if (((*(p + 15 * m + k)) == 0) && ((*(p + 15 * (m+1) + k+1)) == 1)&& ((*(p + 15 *( m+2) + k+2)) == 1)&& ((*(p + 15 * (m+3) + k+3)) == 0)) {
				endTime = clock();
				if ((endTime - beginTime) % 2 == 0) {
					c = 15 * m + k;
				}
				else { c = 15 * m + k + 3; }
			}
		}
	}
	return c;
}
int FuXie2(int*p) {
	int  c =-1;
	for (int m = 0; m < 11; ++m) {
		for (int k = 0; k < 11; ++k) {
			if (((*(p + 15 * m + k)) == 0) && ((*(p + 15 * (m - 1) + k + 1)) == 1) && ((*(p + 15 * (m - 2) + k + 2)) == 1) && ((*(p + 15 * (m - 3) + k + 3)) == 0)) {
				endTime = clock();
				if ((endTime - beginTime) % 2 == 0) {
					c = 15 * m + k;
				}
				else { c = 15 * m + k + 3; }
			}
		}
	}
	return c;
}
int suiji(int* p,bool xianshou) {
	int a=0,b=0;
	int q[15][15] = { {0,}, };
	for (int m = 1; m < 14;++m) {
		for (int k = 1; k < 14;++k) {
			if (*(p+15*m+k)==0) {
				for (int w = -1; w < 2;++w) {
					for (int v = -1; v < 2;++v) {
						if ((*(p + 15 * (m + w) + k + v)!=0)&&(!((w==0)&&(v==0)))) {
							q[m][k] = q[m][k] + 1;
						}
					}
				}
			}
		}
	}
	for (int w = 0; w < 225; ++w) {
		if (q[w/15][w%15]>a) {
			a = q[w / 15][w % 15];
			b = 0;
		}
		if (q[w / 15][w % 15] ==a) {
			++b;
		}
	}
	int w = 0;
	endTime = clock();
	b = ((endTime - beginTime) % b) + 1;
			for (int i = 0; i < 225; ++i) {
				if (q[i / 15][i % 15] == a) {
					--b;
					if (b==0) {w = i;}
				}
			}
	return w;
}
int ZhengXie64(int*p) {
	int  c = -1;
	for (int m = 0; m < 10; ++m) {
		for (int k = 0; k < 10; ++k) {
			if ((*(p + 15 * m + k) == 0) && (*(p + 15 * (m + 1) + k + 1) == 1) && (*(p + 15 * (m + 4) + k + 4) == 1)&& (*(p + 15 * (m + 5) + k + 5) == 0)) {
				if ((*(p + 15 * (m + 2) + k + 2) + *(p + 15 * (m + 3) + k + 3) == 1) && ((*(p + 15 * (m + 2) + k + 2))) * (*(p + 15 * (m + 3) + k + 3)) == 0) {
					endTime = clock();
					if ((endTime - beginTime) % 5 == 0) {
						c = 15 * m + k;
					}
					else if ((endTime - beginTime) % 5 == 1) {
						c = 15 * (m + 5) + k + 5;
					}
					else {
						if ((*(p + 15 * (m + 2) + k + 2)) == 0) { 
							c = 15 * (m + 2) + k + 2;
						}
						else {
							c = 15 * (m + 3) + k + 3;
						}
					}
				}
			}
		}
	}
	return c;
}
int FuXie64(int* p) {
	int  c = -1;
	for (int m = 0; m < 10; ++m) {
		for (int k = 0; k < 10; ++k) {
			if ((*(p + 15 * m + k) == 0) && (*(p + 15 * (m - 1) + k + 1) == 1) && (*(p + 15 * (m - 4) + k + 4) == 1) && (*(p + 15 * (m - 5) + k + 5) == 0)) {
				if ((*(p + 15 * (m - 2) + k + 2) + *(p + 15 * (m - 3) + k + 3) == 1) && ((*(p + 15 * (m - 2) + k + 2))) * (*(p + 15 * (m - 3) + k + 3)) == 0) {
					endTime = clock();
					if ((endTime - beginTime) % 5 == 0) {
						c = 15 * m + k;
					}
					else if ((endTime - beginTime) % 5 == 1) {
						c = 15 * (m - 5) + k + 5;
					}
					else {
						if ((*(p + 15 * (m + 2) + k + 2)) == 0) {
							c = 15 * (m - 2) + k + 2;
						}
						else {
							c = 15 * (m - 3) + k + 3;
						}
					}
				}
			}
		}
	}
	return c;
}
int Heng64(int *p) {
	int  c = -1;
	for (int m = 0; m < 10; ++m) {
		for (int k = 0; k < 10; ++k) {
			if ((*(p + 15 * m + k) == 0) && (*(p + 15 * m  + k + 1) == 1) && (*(p + 15 * m + k + 4) == 1) && (*(p + 15 * m  + k + 5) == 0)) {
				if ((*(p + 15 * m + k + 2) + *(p + 15 *m  + k + 3) == 1) && ((*(p + 15 * m + k + 2))) * (*(p + 15 * m  + k + 3)) == 0) {
					endTime = clock();
					if ((endTime - beginTime) % 5 == 0) {
						c = 15 * m + k;
					}
					else if ((endTime - beginTime) % 5 == 1) {
						c = 15 * m  + k + 5;
					}
					else {
						if ((*(p + 15 * m  + k + 2)) == 0) {
							c = 15 *m + k + 2;
						}
						else {
							c = 15 * m  + k + 3;
						}
					}
				}
			}
		}
	}
	return c;
}