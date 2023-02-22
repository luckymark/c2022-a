#pragma once
#include<stdio.h>
#include<graphics.h>
#include<vector>
#include <Windows.h>
#include<math.h>
#include <iostream>
#include<conio.h>
using namespace std;



//绘图设置
#define kongqi COLORREF RGB(44,47,59)//空气颜色
#define qiangbi COLORREF RGB(249,210,228)//墙壁颜色
#define daixuan COLORREF RGB(0,241,187)//待选颜色
#define xuanzhong COLORREF RGB(242,230,118)//选中颜色
#define human COLORREF RGB(255,0,0)//人物颜色
#define door COLORREF RGB(0,255,0)//出口颜色

#define WIDTH 540//分辨率
#define HEIGHT 360
#define BLOCK_XY 10//小方格边长
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//小方格x轴数量
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//小方格y轴数量
#define MAPROW WIDTH / (BLOCK_XY)
#define MAPCOL HEIGHT / (BLOCK_XY)
enum pos {
	WALL = 0,
	ROAD = 1,
	WAIT = 2,
	HUMAN = 3,
	DOOR = 4,

	RIGHT = 11,
	LEFT = 12,
	UP = 13,
	DOWN = 14,
};

typedef struct specificpos {
	int x;
	int y;
	int spr;
	specificpos(int x, int y) {
		this->x = x;
		this->y = y;
	}
}waitpos;

int map[BLOCK_WIDTH][BLOCK_HEIGHT];//地图数组
//vector<vector<int>> map;
vector<specificpos*> WALLlist;//可能要被转化为路的墙点的位置
vector<specificpos*> ROADlist;//可能要被选中打通的路点的位置

/*函数声明*/
void mapinit();//初始化地图
void judgewait(specificpos* pos);//加载可能转化为路的墙点
void through(specificpos* pos);//打通两个路点
void prime_main();//prime算法主函数
void display();//刷新屏幕
void gamedrawpixal(specificpos* pos, COLORREF RGB);//画小方格
void gamedrawpixal(int x, int y, COLORREF RGB);
void move();//控制人（小红点）走动
bool checkover();//判断游戏是否结束