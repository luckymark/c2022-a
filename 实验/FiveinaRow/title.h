#include <stdlib.h>
#include <stdio.h>
#include <graphics.h> 
#include <conio.h>
#include<Mmsystem.h>
#include<Windows.h>
#pragma comment ( lib, "winmm.lib" )
#define offsetx 20        //��߿�
#define offsety 20        //�ұ߿�
#define map_width 15      //����
#define map_height 15     //����
#define piece_size 30	  //����ֱ��
#define white 1
#define black 2
#define tie 3
using namespace std;

extern int map[20][20];
extern int check;
extern int AIx, AIy;
extern int Piece, changePiece;

extern int order[20][20];
extern int num;
extern int jump;

void drawPiece(int x, int y, int color);
void drawBoard();
void drawBoard2();
void clear(int x, int y);
bool pieceSet(int x, int y, int color);
void judge(int x,int y,int color);
void AI(int x,int y);
void regret();


int playerVSplayer();
int playerVSAI();
int AIVSAI();

