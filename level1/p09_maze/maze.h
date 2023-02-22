#pragma once
#include<stdio.h>
#include<graphics.h>
#include<vector>
#include <Windows.h>
#include<math.h>
#include <iostream>
#include<conio.h>
using namespace std;



//��ͼ����
#define kongqi COLORREF RGB(44,47,59)//������ɫ
#define qiangbi COLORREF RGB(249,210,228)//ǽ����ɫ
#define daixuan COLORREF RGB(0,241,187)//��ѡ��ɫ
#define xuanzhong COLORREF RGB(242,230,118)//ѡ����ɫ
#define human COLORREF RGB(255,0,0)//������ɫ
#define door COLORREF RGB(0,255,0)//������ɫ

#define WIDTH 540//�ֱ���
#define HEIGHT 360
#define BLOCK_XY 10//С����߳�
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//С����x������
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//С����y������
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

int map[BLOCK_WIDTH][BLOCK_HEIGHT];//��ͼ����
//vector<vector<int>> map;
vector<specificpos*> WALLlist;//����Ҫ��ת��Ϊ·��ǽ���λ��
vector<specificpos*> ROADlist;//����Ҫ��ѡ�д�ͨ��·���λ��

/*��������*/
void mapinit();//��ʼ����ͼ
void judgewait(specificpos* pos);//���ؿ���ת��Ϊ·��ǽ��
void through(specificpos* pos);//��ͨ����·��
void prime_main();//prime�㷨������
void display();//ˢ����Ļ
void gamedrawpixal(specificpos* pos, COLORREF RGB);//��С����
void gamedrawpixal(int x, int y, COLORREF RGB);
void move();//�����ˣ�С��㣩�߶�
bool checkover();//�ж���Ϸ�Ƿ����