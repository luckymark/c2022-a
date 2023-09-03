/* 题目：推箱子小游戏（基于console）
功能要求：
将p09迷宫游戏改造为“推箱子”游戏；
在地图中增加箱子、箱子目标位置等图形；
当玩家将所有箱子归位，则显示玩家赢得了游戏；
按玩家走动步数记分；
设计多个关卡，每一关的地图从文件中读取，玩家每关的分数记录到文件中；
*/
#include <stdio.h>
#include <graphics.h>
#include <Windows.h>
#define ROL 20//横x
#define LIN 20//竖y
#define xiangzi 1
#define ren 2
#define qiang 3
#define kong 0
#define mubiao 4
#define gaming 1
#define gameEnd -1
#define chooseBattle 0
#define WIN 2
//地图：1=箱子，2=人，3=墙，0=空，4=目标，总共3关
void InitialButton();
//void InitialMap(int map[LIN][ROL]);
void Walk(int map[LIN][ROL], char keyDown,int *step);
void Again(int map[LIN][ROL]);
void EraseAll();
void DrawWall(int m,int k);
void DrawPlayer(int m,int k);
void DrawBox(int m,int k);
void DrawTarget(int m,int k);
void DrawRoad(int m ,int k);
void CopyMap(int map[LIN][ROL],char* filename ,struct pushBoxesFile* p);
void ChangeMap(int map[LIN][ROL], int* best,struct pushBoxesFile* p);
void ShowStep(int times);
void ShowScore(int times);
void ShowBest(int times);
void ShowNum(int ,int ,int );
void WriteBest(int best, char* filename, struct pushBoxesFile* p);
const int GAPY = 720 / (LIN+2);
const int GAPX = 720 / (ROL+2);
const int GAP = (min(GAPX,GAPY)/2)*2;
struct pushBoxesFile { int map[LIN][ROL]; int score; int constantNum; };
struct FileName {
	char filename[4][20] = { {"filename0.txt"},{"filename1.txt"}, {"filename2.txt"}, {"filename3.txt"}, };
};
int main() {
	struct pushBoxesFile p;
	struct FileName PUSHBOXES;
	int page = gaming;
	//initial
	int map[LIN][ROL] = { {0,}, };
	int step = 0;
	int score = 0;
	int best = 0;
	int battle = 1;
	int constantNum = 0;
	initgraph(960, 720, NULL);
	InitialButton();
	CopyMap(map,PUSHBOXES.filename[1],&p);
	ChangeMap(map,&best,&p);
	ShowNum(step, score, best);
	//InitialMap(map);
	Again(map);
	while (page!=gameEnd) {
		ExMessage m;
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			if (page == gaming) {
				if ((m.x > 790) && (m.x < 920)) {
					if ((m.y > 400) && (m.y < 440)) {
						page = chooseBattle; //选关
						cleardevice();
						TCHAR BACK[] = L"back";
						outtextxy(800,640,BACK);
						COLORREF fillcolor = getfillcolor();
						setfillcolor(RGB(127,127,255));
						for (int i = 1; i < 4; ++i) {//只有三关
							solidrectangle(50 * (2 * i - 1), 50 * 1, 50 * 2 * i, 50 * 1 + 50);
						}
						
						TCHAR char1[] = L"1";
						TCHAR char2[] = L"2";
						TCHAR char3[] = L"3";
						COLORREF bkcolor = getbkcolor();
						setbkcolor(getfillcolor());
						outtextxy(60,60,char1);
						outtextxy(60+2*50, 60, char2);
						outtextxy(60+50*4, 60, char3);
						setbkcolor(bkcolor);
						setfillcolor(fillcolor);
					}
					if ((m.y > 480) && (m.y < 520)) {
						CopyMap(map, PUSHBOXES.filename[battle], &p);
						ChangeMap(map,&best, &p);
						InitialButton();
						step = 0;
						score = 0;
						ShowNum(step, score, best);
						Again(map);
					}
					if ((m.y > 560) && (m.y < 600)) {
						page = gameEnd; //退出游戏
					}
					/*if ((m.y > 640) && (m.y < 680)) { //教程关
						InitialButton();
						step = 0;
						score = 0;
						best = 0;
						constantNum = p.constantNum;
						if (step <= 0) { score = 0; }
						else { score = constantNum / step; }
						ShowNum(step, score, best);
						CopyMap(map, PUSHBOXES.filename[0], &p);
						ChangeMap(map,&p);
						Again(map);
					}*/
				}
			}
			if (page == chooseBattle) {
				if ((m.y/50)==1) {
					battle =(1+m.x/50)/2;
					CopyMap(map,PUSHBOXES.filename[battle],&p);
					ChangeMap(map,&best,&p);
					page = gaming;
					InitialButton();
					step = 0;
					score = 0;
					ShowNum(step, score, best);
					Again(map);
				}
				if ((m.x<900)&&(m.x>780)&&(m.y<680)&&(m.y>600)) {
					page = gaming;
					InitialButton();
					step = 0;
					score = 0;
					ShowNum(step,score,best);
					Again(map);
				}
			}
			break;
		case WM_KEYDOWN:
			if (page == gaming) { 
				char keyDown = m.vkcode;
				Walk(map,keyDown,&step);
				Again(map);
				constantNum = p.constantNum;
				if (step <= 0) { score = 0; }
				else {score = constantNum/ step;}
				ShowNum(step,score,best);
				int judgeWin = 0;
				for (int i = 0; i < LIN;++i) {
					for (int j = 0; j < ROL; ++j) {
						if (map[i][j] >= mubiao)  { judgeWin++; }
						if (map[i][j] == mubiao + xiangzi) { judgeWin--; }
					}
				}
				if (judgeWin == 0) { page = WIN; }
			}
			if (page==WIN) {
				WriteBest(max(score,best),PUSHBOXES.filename[battle],&p);
				ShowNum(step,score,best);
				TCHAR YOUWIN[] = L"YOU WIN";
				outtextxy(960/2, 720/2, YOUWIN);
				Sleep(3000);
				page = chooseBattle;
				cleardevice(); 
				TCHAR NEXT[] = L"next";
				outtextxy(800, 640, NEXT);
				COLORREF fillcolor = getfillcolor();
				setfillcolor(RGB(127, 127, 255));
				for (int i = 1; i < 4; ++i) {//只有三关
					solidrectangle(50 * (2 * i - 1), 50 * 1, 50 * 2 * i, 50 * 1 + 50);
				}

				TCHAR char1[] = L"1";
				TCHAR char2[] = L"2";
				TCHAR char3[] = L"3";
				COLORREF bkcolor = getbkcolor();
				setbkcolor(getfillcolor());
				outtextxy(60, 60, char1);
				outtextxy(60 + 2 * 50, 60, char2);
				outtextxy(60 + 50 * 4, 60, char3);
				setbkcolor(bkcolor);
				setfillcolor(fillcolor);
				if (battle<3) {battle++;}
				CopyMap(map, PUSHBOXES.filename[battle], &p);
				ChangeMap(map, &best, &p);
			}
			break;
		default:
			break;
		}
	}
	closegraph();
	return 0;
}
void InitialButton() {
	const int upy = 40;
	const int leftx = 790;
	const int chary = 40;
	const int inty = 50;
	const int gapy = 30;
	const int rightx = 790 + 130;
	setbkcolor(RGB(0, 255,127));
	cleardevice();
	settextstyle(40, 0, ANSI_CHARSET);
	setlinecolor(RGB(0, 0, 0));
	setfillcolor(RGB(0, 0, 127));
	settextcolor(RGB(0,0,0));
	TCHAR MENU[] = L"menu";
	outtextxy(leftx+10, 400, MENU);
	TCHAR RESTART[] = L"restart";
	outtextxy(leftx + 10, 480, RESTART);
	TCHAR EXIT[] = L"exit";
	outtextxy(leftx + 10, 560, EXIT);
	/*TCHAR HELP[] = L"help";
	outtextxy(800, 640, HELP);*/
	TCHAR STEP[] = L"step";
	outtextxy(leftx + 10,upy,STEP);
	TCHAR SCORE[] = L"score";
	outtextxy(leftx + 10,upy+chary+inty+gapy,SCORE);
	TCHAR BEST[] = L"best";
	outtextxy(leftx + 10,upy+chary*2+inty*2+gapy*2,BEST);
	rectangle(leftx, 400, rightx, 440);
	rectangle(leftx, 480, rightx, 520);
	rectangle(leftx, 560,rightx, 600);
	//rectangle(790, 640, 790 + 130, 680);
	rectangle(leftx,upy,rightx,upy+chary+inty);
	rectangle(leftx, upy+chary+inty+gapy, rightx, upy + chary + inty + gapy+chary+inty);
	rectangle(leftx, upy + chary + inty + gapy + chary + inty+gapy,rightx, upy + chary + inty + gapy + chary + inty + gapy+chary+inty);
}
void ShowNum(int step,int score,int best) {
	const int upy = 40;
	const int leftx = 790;
	const int chary = 40;
	const int inty = 50;
	const int gapy = 30;
	const int rightx = 790 + 130;
	//clearrectangle(800,80,880,120);
	ShowStep(step);
	//clearrectangle(800, 160, 880, 200);
	ShowScore(score);
	//clearrectangle(800,240, 880, 280);
	ShowBest(best);
}
void CopyMap(int map[LIN][ROL], char* filename, struct pushBoxesFile* p) {
	FILE* file;
	fopen_s(&file, filename, "r");
	if (file == NULL) { printf("not open file\n"); }
	else {
		//fseek(file, 0, SEEK_SET);
		fread((void*)p, sizeof(struct pushBoxesFile), 1, file);
		fclose(file);
	}
}
void Again(int map[LIN][ROL]){
	EraseAll();
	for (int m = 0; m < LIN; ++m) {
		for (int k = 0; k < ROL; ++k) {
			switch (map[m][k]) {
			case kong:
				DrawRoad(k, m);
				break;
			case ren:
				DrawPlayer(k, m);
				break;
			case xiangzi:
				DrawRoad(k, m);
				DrawBox(k, m);
				break;
			case qiang:
				if ((m==0)||(m==LIN-1)||(k==0)||(k==ROL-1)) {}
				else if ((map[m][k-1]==qiang)&&(map[m][k +1] == qiang)&&(map[m+1][k] == qiang)&&(map[m - 1][k] == qiang)&&
					(map[m+1][k - 1] == qiang) && (map[m-1][k + 1] == qiang) && (map[m + 1][k+1] == qiang) && (map[m - 1][k-1] == qiang)) {}
				else{ DrawRoad(k, m); DrawWall(k, m);}
				break;
			case (xiangzi + mubiao):
				DrawRoad(k, m);
				DrawBox(k, m);
				DrawTarget(k, m);
				break;
			case (ren + mubiao):
				DrawRoad(k,m);
				DrawPlayer(k, m);
				DrawTarget(k, m);
				break;
			case mubiao:
				DrawRoad(k, m);
				DrawTarget(k,m);
				break;
			default:
				//printf("error\n");
				break;
			}
		}
	}
}
void ChooseBattle(short x,short y) {//此处实参为m.x,m.y
	for (int i = 1; i < 4; ++i) {
		if ((x/50)%2) {}
		solidrectangle(50 * (2 * i - 1), 50 * 1, 50 * 2 * i, 50 * 1 + 50);
	}
}
void EraseAll(void) {
	clearrectangle(0,0,720,720);
}

void DrawRoad(int m, int k) {
	const int xRef = m * GAP + GAP / 2;
	const int yRef = k * GAP + GAP / 2;
	const int xMax = m * GAP + 3 * GAP / 2;
	const int yMax = k * GAP + 3 * GAP / 2;
	const int triLen = 5;
	const int dis = 3;
	COLORREF fillcolor = getfillcolor();
	setfillcolor(RGB(255, 127, 127));
	solidrectangle(m * GAP + GAP / 2, k * GAP + GAP / 2, m * GAP + 3 * GAP / 2, k * GAP + 3 * GAP / 2);
	setfillcolor(fillcolor);
	COLORREF linecolor = getlinecolor();
	setlinecolor(RGB(0,0,0));
	line(xRef,yRef+triLen+dis,xRef,yMax- triLen - dis);
	line(xMax, yRef + triLen + dis, xMax, yMax - triLen - dis);
	line(xRef + triLen + dis, yRef, xMax- triLen - dis, yRef );
	line(xRef + triLen + dis, yMax, xMax - triLen - dis, yMax);
	setlinecolor(linecolor);
}
/*
void DrawRoad(int m,int k) {
	COLORREF fillcolor = getfillcolor();
	setfillcolor(RGB(0, 0,255 ));
	fillrectangle(m*GAP+GAP/2,k*GAP+GAP/2,m*GAP+3*GAP/2,k*GAP+3*GAP/2);
	setfillcolor(fillcolor);
}*/

void DrawPlayer(int m,int k) {
	COLORREF fillcolor=getfillcolor();
	setfillcolor(RGB(255,0,0));
	POINT people[] = { {GAP * m + GAP/2,GAP*k+GAP},{GAP*m+GAP,GAP*k+GAP/2},{GAP * m +3* GAP/2,GAP * k+GAP},{GAP * m+GAP,GAP * k + 3*GAP/2} };
	fillpolygon(people, 4);
	setfillcolor(fillcolor);
}
void DrawBox(int m,int k) { 
	const int xRef = m * GAP + GAP / 2;
	const int yRef = k * GAP + GAP / 2;
	const int xMax = m * GAP + 3 * GAP / 2;
	const int yMax = k * GAP + 3 * GAP / 2;
	const int triLen = 3;
	COLORREF fillcolor=getfillcolor();
	setfillcolor(RGB(255,255,0));
	fillrectangle(m * GAP + GAP / 2+2, k * GAP + GAP / 2+2, m * GAP + 3 * GAP / 2-2, k * GAP + 3 * GAP / 2-2);
	setfillcolor(fillcolor);
	COLORREF linecolor=getlinecolor();
	setlinecolor(RGB(0,0,255));
	line(xRef+triLen,yRef+2,xMax-2,yMax-triLen);
	line(xRef +2, yRef+ triLen, xMax - triLen, yMax-2);
	line(xRef + triLen, yMax-2 , xMax-2,yRef+ triLen );
	line(xRef +2, yMax - triLen, xMax- triLen, yRef+2);
	setlinecolor(linecolor);
}
void DrawTarget(int m,int k) {
	COLORREF fillcolor = getfillcolor();
	setfillcolor(RGB(127, 127, 127));
	fillcircle(m * GAP + GAP , k * GAP + GAP ,GAP/2- 10);
	setfillcolor(fillcolor);
}
void DrawWall(int m, int k) {
	int xRef = m * GAP + GAP / 2;
	int yRef = k * GAP + GAP / 2;
	int xMax = m * GAP + 3 * GAP / 2;
	int yMax = k * GAP + 3 * GAP / 2;

	COLORREF fillcolor = getfillcolor();
	COLORREF linecolor = getlinecolor();
	setfillcolor(RGB(200, 200, 200));

	setfillcolor(RGB(197,195,198));//set color background;
	solidrectangle(xRef, yRef, xMax, yMax);//draw background;

	setlinecolor(RGB(251,250,251));//set color light line;
	for (int i = 0; i < 2; i++){
		line(xRef + i, yRef + i, xMax, yRef + i);
		line(xRef + i, yRef, xRef + i, (yRef + yMax) / 2 - i);		
	}

	for (int i = 0; i < 2; i++) {
		line(xRef, (yRef + yMax) / 2  + 1 + i, (xRef + xMax) / 2  -i, (yRef + yMax) / 2 + 1 + i);
		line((xRef + xMax) / 2 + 1, (yRef + yMax) / 2 + 1 + i, xMax - i, (yRef + yMax) / 2 + 1 + i);
		line((xRef + xMax) / 2 + 1 + i, (yRef + yMax) / 2 + 1, (xRef + xMax) / 2 + 1 + i, yMax - i);
		//line(xRef + i, yRef, xRef + i, (yRef + yMax) / 2 - i);
	}

	setlinecolor(RGB(134,134,134));//set color dark line;
	for (int i = 0; i < 2; i++) {
		line(xRef - i, (yRef + yMax) / 2 - i, xMax, (yRef + yMax) / 2 - i);
		line(xMax - i, yRef + i, xMax - i, (yRef + yMax) / 2);

	}
	for (int i = 0; i < 2; i++) {
		line(xRef, yMax - i, xMax, yMax - i);
		line((xRef + xMax)/ 2  - i, (yRef + yMax) / 2 - i, (xRef + xMax) / 2 - i, yMax);

	}
	

	//solidrectangle(m * GAP + GAP / 2, k * GAP + GAP / 2, m * GAP + 3 * GAP / 2, k * GAP + 3 * GAP / 2);
	setfillcolor(fillcolor);
	setlinecolor(linecolor);
}
/*
void DrawWall (int m, int k) {
	COLORREF fillcolor = getfillcolor();
	setfillcolor(RGB(200, 200,200));
	solidrectangle(m * GAP + GAP / 2, k * GAP + GAP / 2, m * GAP + 3 * GAP / 2, k * GAP + 3 * GAP / 2);
	setfillcolor(fillcolor);
}*/
void Walk(int map[LIN][ROL], char keyDown,int*step) {
	int playerPosition = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < LIN; ++i) {
		for (j = 0; j < ROL;++j) {
			if (map[i][j]%mubiao == ren) { 
				playerPosition = i*ROL+j; 
			}
		}
	}
	i = playerPosition / ROL;
	j = playerPosition % ROL;
	switch (keyDown) {
	case 0x41://key a
		if ((map[i][j - 1]%mubiao == xiangzi) && (map[i][j - 2] %mubiao== kong)) { map[i][j] = map[i][j]-ren; map[i][j - 1] = map[i][j-1]-xiangzi+ren; map[i][j - 2] = map[i][j-2]+xiangzi; }
		if (map[i][j - 1]%mubiao == kong) { map[i][j] = map[i][j]-ren; map[i][j - 1] = map[i][j-1]+ren; }
		*step = (*step)+1;
		break;
	case 0x57://key w
		if ((map[i- 1][j ] % mubiao == xiangzi) && (map[i- 2][j ] % mubiao == kong)) { map[i][j] = map[i][j] - ren; map[i- 1][j ] = map[i- 1][j ] - xiangzi + ren; map[i- 2][j ] = map[i- 2][j ] + xiangzi; }
		if (map[i- 1][j ] % mubiao == kong) { map[i][j] = map[i][j] - ren; map[i- 1][j ] = map[i- 1][j ] + ren; }
		*step = (*step) + 1;
		break;
	case 0x53://key s
		if ((map[i+ 1][j ] % mubiao == xiangzi) && (map[i+ 2][j ] % mubiao == kong)) { map[i][j] = map[i][j] - ren; map[i+ 1][j ] = map[i+ 1][j ] - xiangzi + ren; map[i+ 2][j ] = map[i+ 2][j ] + xiangzi; }
		if (map[i+ 1][j ] % mubiao == kong) { map[i][j] = map[i][j] - ren; map[i+ 1][j ] = map[i+ 1][j ] + ren; }
		*step = (*step) + 1;
		break;
	case 0x44://key d
		if ((map[i][j + 1] % mubiao == xiangzi) && (map[i][j + 2] % mubiao == kong)) { map[i][j] = map[i][j] - ren; map[i][j + 1] = map[i][j + 1] - xiangzi + ren; map[i][j + 2] = map[i][j + 2] + xiangzi; }
		if (map[i][j + 1] % mubiao == kong) { map[i][j] = map[i][j] - ren; map[i][j + 1] = map[i][j + 1] + ren; }
		*step = (*step) + 1;
		break;
	default:
		break;
	}
}/*
void InitialMap(int map[LIN][ROL]) {
	for (int i = 0; i < LIN;++i) {
		for (int j = 0; j < 2;++j) {
			map[i][j] = qiang;
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < ROL; ++j) {
			map[i][j] = qiang;
		}
	}
	map[10][10] = ren;
	for (int i = LIN-2; i < LIN; ++i) {
		for (int j = 0; j < ROL; ++j) {
			map[i][j] = qiang;
		}
	}
	for (int i = 0; i < LIN; ++i) {
		for (int j = ROL-2; j < ROL; ++j) {
			map[i][j] = qiang;
		}
	}
	map[7][7] = xiangzi;
	map[15][15] = mubiao;
}*/
void ChangeMap(int map[LIN][ROL],int* best, struct pushBoxesFile* p) {
	for (int i = 0; i < LIN;++i) {
		for (int j = 0; j < ROL;++j) {
			map[i][j] = p->map[i][j];
		}
	}
	*best = p->score;
}
void ShowStep(int times) {
	int a = 0;
	const int upy = 40;
	const int leftx = 790;
	const int chary = 40;
	const int inty = 50;
	const int gapy = 30;
	const int rightx = 790 + 130;
	char strmk[5] = { '0','0','0','0','\0' };
	COLORREF temp = gettextcolor();
	if ((times >= 10000) || (times < 0)) { TCHAR MUCH[] = L"too much"; outtextxy(200, 700, MUCH); }
	else { a = (times) % 10000; }
	strmk[3] = a % 10 + '0';
	a = a / 10;
	strmk[2] = a % 10 + '0';
	a = a / 10;
	strmk[1] = a % 10 + '0';
	a = a / 10;
	strmk[0] = a % 10 + '0';
	strmk[4] = '\0';
	settextcolor(RGB(0, 0, 0));
	for (int i = 0; i < 5; i++) {
		outtextxy(800 + i * 20, upy+chary, *(strmk + i));
	}
	settextcolor(temp);
}
void ShowScore(int times) {
	int a = 0;
	const int upy = 40;
	const int leftx = 790;
	const int chary = 40;
	const int inty = 50;
	const int gapy = 30;
	const int rightx = 790 + 130;
	char strmk[5] = { '0','0','0','0','\0' };
	COLORREF temp = gettextcolor();
	if ((times >= 10000) || (times < 0)) { TCHAR MUCH[] = L"too much"; outtextxy(200, 700, MUCH); }
	else { a = (times) % 10000; }
	strmk[3] = a % 10 + '0';
	a = a / 10;
	strmk[2] = a % 10 + '0';
	a = a / 10;
	strmk[1] = a % 10 + '0';
	a = a / 10;
	strmk[0] = a % 10 + '0';
	strmk[4] = '\0';
	settextcolor(RGB(0, 0, 0));
	for (int i = 0; i < 5; i++) {
		outtextxy(800 + i * 20, upy+chary+inty+gapy+chary, *(strmk + i));
	}
	settextcolor(temp);
}
void ShowBest(int times) {
	int a = 0;
	const int upy = 40;
	const int leftx = 790;
	const int chary = 40;
	const int inty = 50;
	const int gapy = 30;
	const int rightx = 790 + 130;
	char strmk[5] = { '0','0','0','0','\0' };
	COLORREF temp = gettextcolor();
	if ((times >= 10000) || (times < 0)) { TCHAR MUCH[] = L"too much"; outtextxy(200, 700, MUCH); }
	else { a = (times) % 10000; }
	strmk[3] = a % 10 + '0';
	a = a / 10;
	strmk[2] = a % 10 + '0';
	a = a / 10;
	strmk[1] = a % 10 + '0';
	a = a / 10;
	strmk[0] = a % 10 + '0';
	strmk[4] = '\0';
	settextcolor(RGB(0, 0, 0));
	for (int i = 0; i < 5; i++) {
		outtextxy(800 + i * 20, upy+chary+gapy+inty+inty+chary+chary+gapy, *(strmk + i));
	}
	settextcolor(temp);
}
void WriteBest(int best ,char*filename ,struct pushBoxesFile *p) {
	FILE* file;
	fopen_s(&file, filename, "r+");
	p->score = best;
	//printf("p->score=%d\n",p->score);
	fwrite((void*)p, sizeof(struct pushBoxesFile), 1, file);
	fclose(file);
}