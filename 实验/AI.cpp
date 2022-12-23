#define _CRT_SECURE_NO_WARNINGS
#include "AI.h"
#include "GameInit.h"
#include <easyx.h>
#include "Score.h"
#include<stdio.h>
#include<stdlib.h>

int temp[20][20];

void computerdo(ExMessage mouse, int color, int* win) {
	int i = 0;
	int j = 0;
	int jump = 0;
	LOGFONT f;

	gettextstyle(&f);						// 获取当前字体设置
	settextcolor(BLACK);					// 设置字体颜色黑色
	f.lfHeight = 24;						// 设置字体高度为 12
	_tcscpy(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式


RENEW:
	outtextxy(913, 0, _T("伟大机器人正在推翻人类暴政"));
	while (mouse.lbutton != true) {
		getmessage(&mouse, EX_MOUSE);
	}
	mouse.lbutton = false;
	for (i = 0; i < 15; ++i) {
		for (j = 0; j < 15; ++j) {
			if (mouse.x > X[i] - 16 && mouse.x < X[i] + 16) {
				if (mouse.y > Y[j] - 16 && mouse.y < Y[j] + 16 && Board[i][j] == 0) {
					if (color == 1) {
						setfillcolor(BLACK);
					}
					else {
						setfillcolor(WHITE);
					}
					solidcircle(X[i], Y[j], 28);
					Board[i][j] = color;
					flushmessage();
					jump = 1;
					break;
				}
			}
		}
		if (jump == 1) {
			jump = 0;
			clearrectangle(913, 0, 1500, 30);
			WinWinWin(win);
			break;
		}
		if (i == 14 && j == 15) {
			clearrectangle(913, 0, 1500, 30);
			goto RENEW;
		}
	}
}

tree* treerootbuild(int i, int j) {
	tree* root;
	root = (tree*)malloc(sizeof(tree));
	if(root != NULL)
	{
		root->x = i;
		root->y = j;
		root->color = check(i, j);
		root->score = 0;
		root->thiscell = NULL;
		root->nextcell = NULL;
		return root;
	}
	return NULL;
}

void treebuild(short cell, int color,tree* root,tree* finder) {//请用递归重写
	int a[450];
	for (int i = 0; i < 450; ++i) {
		a[i] = -1;
	}
	if (root->nextcell == NULL) {
		finder = root;
	}
	genboard(a);
	for (int k = 0; k < 900 && a[k] != -1; k += 2) {
		temp[a[k]][a[k+1]] = color;
		tree* next = (tree*)malloc(sizeof(tree));
		next->color = color;
		next->x = a[k];
		next->y = a[k + 1];
		next->score = score(color);
		next->nextcell = NULL;
		next->thiscell = NULL;
		if (finder->nextcell == NULL  && k == 0) {
			finder->nextcell = next;
			finder = finder->nextcell;
		}
		else {
			finder->thiscell = next;
			finder = finder->thiscell;
		}
		if (cell < 7) {//change
			treebuild(cell += 1, color, root, finder);
		}

		temp[a[k]][a[k + 1]] = 0;
	}
	
}

void dfs(int cell,tree *root)
{
	tree* finder = root;
	if (cell == 4) {
		//finder->score = score();
		return;
	}

}

short check(int i,int j)
{
	if (temp[i][j] == 1) {
		return 1;
	}
	else if(temp[i][j] == 2) {
		return 2;
	}
	else {
		return 0;
	}
	return 0;
}

int* genboard(int* a)
{
	int k = 0;
	int flag = 1;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (Board[i][j] == 0) {
				for (int m = i - 2; m <= i+2; ++m) {
					for (int n = j - 2; n <= j + 2; ++n) {
						if (m > 0 && n > 0 && m != n && Board[m][n] != 0) {
							for (int q = 0; q < 450 && a[q] != -1; q = q + 2) {
								if (a[q] == i && a[q + 1] == j) {
									flag = 0;
								}
							}
							if (flag) {
								a[k] = i;
								a[k + 1] = j;
								k = k + 2;
							}
						}
					}
				}
			}
		}
	}
	return a;
}

