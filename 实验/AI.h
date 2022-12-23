#pragma once
#ifndef AI_H
#define AI_H
#include <easyx.h>
#include "GameInit.h"

typedef struct st {
	short x;
	short y;
	short color;
	short score;
	struct st* thiscell;
	struct st* nextcell;
}tree;

extern int temp[20][20];

void computerdo(ExMessage mouse, int color, int* win);
tree* treerootbuild(int i,int j);
void treebuild(short cell, int color,tree* root,tree* finder);
void dfs(int cell, tree* root);
short check(int j,int thorizen);
int* genboard(int* a);


#endif