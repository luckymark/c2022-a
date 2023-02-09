#pragma once
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE


#define ROW 15 
#define LINE 15//l…œœ¬ r◊Û”“
#define OROW 0
#define OLINE 0
constexpr auto S = 900/15;




#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<time.h>
#include <conio.h>



void board();


void player(int x,int y);


void chess(int *row ,int *line);

int game();
int menu();
void beginanimation();
int showchoice();
int saving(); 
void reading();



int judge1();
int judge12();
int judge2();
int judge21();



void dfs(int* row, int* line);

void dfs1(int depth, int min_cut, int max_cut, int num, int all_point, int cur_point, int* row, int* line);

int jud(int monitor[]);