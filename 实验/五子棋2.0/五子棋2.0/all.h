#pragma once
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE


#define ROW 15 
#define LINE 15//l上下 r左右
#define OROW 0
#define OLINE 0
#define PTIF 2147483647//正无穷,Beta
#define NGIF -2147483648//负无穷,Alpha
constexpr auto S = 900/15;




#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<time.h>
#include <conio.h>
#include<math.h>



void board();


void player(int x,int y);


void chess(int *row ,int *line);

int game();
int menu();
void beginanimation();
int showchoice();
int saving(); 
void save_file();
void reading();



int judge1();
int judge12();
int judge2();
int judge21();



void dfs(int* row, int* line);

void dfs1(int depth, int min_cut, int max_cut, int num, int all_point, int cur_point, int* row, int* line);

int jud(int monitor[]);

int Minmax(int Chess[ROW][LINE], int Alpha, int Beta, int cur_color, int depth);
int score(int a, int co[ROW][LINE], int n);