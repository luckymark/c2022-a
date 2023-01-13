#pragma once
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE


#define ROW 15 
#define LINE 15//lÉÏÏÂ r×óÓÒ
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

void dfs1(int deepth, int num,int step, int* m, int* n,int turn);

int jud(int monitor[]);